// Copyright (c) 2024 -  Mitch Bradley
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

// Stepping engine that uses direct GPIO accesses timed by spin loops.

#include "Driver/step_engine.h"
#include "Driver/fluidnc_gpio.h"
#include "Driver/delay_usecs.h"
#include "Driver/StepTimer.h"
// #include <esp32-hal-gpio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define IRAM_ATTR

#ifdef _WIN32
#include <process.h>

static HANDLE timerThread = NULL;
static volatile bool timerRunning = false;
static uint32_t timerTicks = 0;
static uint32_t timerFrequency = 0;
static bool (*timer_callback)(void) = NULL;
static LARGE_INTEGER perfFrequency;
static int64_t ticksPerCallback = 0;

static unsigned int __stdcall timerThreadFunc(void* arg) {
    LARGE_INTEGER nextTick, currentTick;
    QueryPerformanceCounter(&nextTick);
    nextTick.QuadPart += ticksPerCallback;

    while (timerRunning) {
        // Hybrid approach - sleep for most of the time, then wait for precision
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        int64_t ticksRemaining = nextTick.QuadPart - now.QuadPart;

        // For sleep calculation
        int64_t usRemaining = (ticksRemaining * 1000000LL) / perfFrequency.QuadPart;

        // More than 2ms remaining? sleep for part of it
        if (usRemaining > 2000) {
            Sleep((DWORD)((usRemaining - 1000) / 1000));
        }

        // Busy-wait for the last part for precision
        do {
            QueryPerformanceCounter(&currentTick);
        } while (currentTick.QuadPart < nextTick.QuadPart && timerRunning);

        if (timerRunning && timer_callback) {
            if (timer_callback()) {
                nextTick.QuadPart += ticksPerCallback;
            } else {
                timerRunning = false;
            }
        }
    }

    return 0;
}

void stepTimerInit(uint32_t frequency, bool (*fn)(void)) {
    timer_callback = fn;
    timerFrequency = frequency;

    QueryPerformanceFrequency(&perfFrequency);

    // Performance counter ticks per callback
    ticksPerCallback = perfFrequency.QuadPart / frequency;
    if (ticksPerCallback == 0) ticksPerCallback = 1;

    // Set default ticks (will be updated by stepTimerSetTicks)
    timerTicks = (uint32_t)ticksPerCallback;

    // 1ms timer resolution
    timeBeginPeriod(1);
}

void stepTimerStop() {
    if (timerRunning) {
        timerRunning = false;
    }

    if (timerThread != NULL) {
        WaitForSingleObject(timerThread, 1000);
        CloseHandle(timerThread);
        timerThread = NULL;
    }
}

void stepTimerSetTicks(uint32_t ticks) {
    timerTicks = ticks;

    // Update callback interval based on ticks
    // ticks represents the alarm value in timer frequency units
    if (timerFrequency > 0) {
        ticksPerCallback = (perfFrequency.QuadPart * (int64_t)ticks) / (int64_t)timerFrequency;
        if (ticksPerCallback == 0) {
            ticksPerCallback = 1;
        }
    }
}

void stepTimerStart() {
    // Make sure previous thread is cleaned up
    stepTimerStop();

    if (!timerRunning && timerThread == NULL) {
        timerRunning = true;

        // Create high-priority thread for timer
        timerThread = (HANDLE)_beginthreadex(NULL, 0, timerThreadFunc, NULL, 0, NULL);
    }
}

#else
// Empty implementations for non-Windows platforms
void stepTimerInit(uint32_t frequency, bool (*fn)(void)) {}
void stepTimerStop() {}
void stepTimerSetTicks(uint32_t ticks) {}
void stepTimerStart() {}
#endif

static uint32_t _pulse_delay_us;
static uint32_t _dir_delay_us;

static uint32_t init_engine(uint32_t dir_delay_us, uint32_t pulse_delay_us, uint32_t frequency, bool (*callback)(void)) {
    stepTimerInit(frequency, callback);
    _dir_delay_us   = dir_delay_us;
    _pulse_delay_us = pulse_delay_us;
    return _pulse_delay_us;
}

static uint32_t init_step_pin(pinnum_t step_pin, bool step_invert) {
    return step_pin;
}

static int32_t        _stepPulseEndTime;
static void IRAM_ATTR set_pin(pinnum_t pin, bool level) {
    gpio_write(pin, level);
}

static void IRAM_ATTR finish_dir() {
    delay_us(_dir_delay_us);
}

static void IRAM_ATTR start_step() {}

// Instead of waiting here for the step end time, we mark when the
// step pulse should end, then return.  The stepper code can then do
// some work that is overlapped with the pulse time.  The spin loop
// will happen in start_unstep()
static void IRAM_ATTR finish_step() {
    _stepPulseEndTime = usToEndTicks(_pulse_delay_us);
}

static bool IRAM_ATTR start_unstep() {
    spinUntil(_stepPulseEndTime);
    return false;
}

// This is a noop because each gpio_write() takes effect immediately,
// so there is no need to commit multiple GPIO changes.
static void IRAM_ATTR finish_unstep() {}

static uint32_t max_pulses_per_sec() {
    return 1000000 / (2 * _pulse_delay_us);
}

static void IRAM_ATTR set_timer_ticks(uint32_t ticks) {
    stepTimerSetTicks(ticks);
}

static void IRAM_ATTR start_timer() {
    stepTimerStart();
}

static void IRAM_ATTR stop_timer() {
    stepTimerStop();
}

// clang-format off
static step_engine_t engine = {
    "Timed",
    init_engine,
    init_step_pin,
    set_pin,
    finish_dir,
    start_step,
    set_pin,
    finish_step,
    start_unstep,
    finish_unstep,
    max_pulses_per_sec,
    set_timer_ticks,
    start_timer,
    stop_timer
};

REGISTER_STEP_ENGINE(Timed, &engine);
