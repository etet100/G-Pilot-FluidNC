
#include <QtCore>
#include "capture/WinConsole.h"
#include "capture/freertos/task.h"
#include "src/Stepping.h"

extern WinConsole winConsole;
extern void setup(QString serverName);
extern void loop();

QAtomicInt* gpilotStopFlag = nullptr;

extern "C"
{

Q_DECL_EXPORT
void FluidNC(QString serverName, QAtomicInt* stopFlag)
{
    gpilotStopFlag = stopFlag;
    setup(serverName);
    while (1) {
        if (stopFlag && stopFlag->loadRelaxed() == 2) {
            break;
        }
        loop();
    }
    gpilotStopFlag = nullptr;

    // Signal all FreeRTOS task threads to exit via FluidNCShutdown exception
    // thrown from vTaskDelay, then wait for each thread to finish.
    // This must happen before the stepper timer and socket cleanup so that
    // no task code runs after the resources are gone.
    gpilot_shutdown_tasks();

    // Stop the stepper timer thread and disconnect sockets before returning.
    // Without this, background threads keep executing DLL code after
    // FreeLibrary / unload(), causing a crash.
    Machine::Stepping::stopTimer();
    winConsole.disconnect();
}

}
