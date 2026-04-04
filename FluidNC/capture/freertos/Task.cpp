#include "Task.h"

#include "Capture.h"
#include "Arduino.h"

// This code is based on std::thread, which is actually incorrect. A closer representation would be to
// use thread fibers like MS ConvertThreadToFiber and CreateFiber. That way, we can have 2 threads (one for
// each CPU) and then allocate multiple cooperative (non-preemptive) fibers on it.

#include <thread>
#include <vector>
#include <memory>
#include <atomic>
#include <stdexcept>

std::vector<std::unique_ptr<std::thread>> threads;

// Set to true before joining threads to make vTaskDelay throw and unwind each task.
std::atomic<bool> gpilot_shutdown { false };

struct GpilotShutdown {};

void gpilot_check_shutdown() {
    if (gpilot_shutdown.load()) {
        throw GpilotShutdown {};
    }
}

BaseType_t xTaskCreatePinnedToCore(TaskFunction_t      pvTaskCode,
                                   const char* const   pcName,
                                   const uint32_t      usStackDepth,
                                   void* const         pvParameters,
                                   UBaseType_t         uxPriority,
                                   TaskHandle_t* const pvCreatedTask,
                                   const BaseType_t    xCoreID) {
    // Wrap the task so FluidNCShutdown unwinds it cleanly without crashing.
    auto wrapper = [pvTaskCode, pvParameters]() {
        try {
            pvTaskCode(pvParameters);
        } catch (const GpilotShutdown&) {
            // Normal shutdown path — exit thread silently.
        } catch (...) {
            // Unexpected exception — swallow to avoid terminate().
        }
    };
    std::unique_ptr<std::thread> thread = std::make_unique<std::thread>(wrapper);
    threads.emplace_back(std::move(thread));
    return pdTRUE;
}

void vTaskDelay(const TickType_t xTicksToDelay) {
    if (gpilot_shutdown.load()) { throw GpilotShutdown {}; }
    Capture::instance().wait(xTicksToDelay);
    if (gpilot_shutdown.load()) { throw GpilotShutdown {}; }
}

void vTaskDelayUntil(TickType_t* const pxPreviousWakeTime, const TickType_t xTimeIncrement) {
    if (gpilot_shutdown.load()) { throw GpilotShutdown {}; }
    Capture::instance().waitUntil((*pxPreviousWakeTime + xTimeIncrement));
    if (gpilot_shutdown.load()) { throw GpilotShutdown {}; }
}

TickType_t xTaskGetTickCount(void) {
    if (gpilot_shutdown.load()) { throw GpilotShutdown {}; }
    auto& inst = Capture::instance();
    inst.wait(1);
    return inst.current();
}

unsigned long millis() {
    return xTaskGetTickCount() / portTICK_PERIOD_MS;
}

unsigned long micros() {
    return 1000 * millis();
}

void delay(uint32_t value) {
    vTaskDelay(value * portTICK_PERIOD_MS);  // delay a while
}

void delayMicroseconds(uint32_t us) {
    vTaskDelay(us * (portTICK_PERIOD_MS / 1000));  // delay a while
}

void gpilot_shutdown_tasks() {
    gpilot_shutdown.store(true);
    for (auto& thread : threads) {
        if (thread && thread->joinable()) {
            thread->join();
        }
    }
    threads.clear();
    gpilot_shutdown.store(false);
}

void cleanupThreads() {
    for (auto const& thread : threads) {
        // This lets the OS destroy the thread silently on exit
        thread->detach();
    }
}
