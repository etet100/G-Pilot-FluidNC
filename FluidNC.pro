QT += network

# lib or app
BUILD_TYPE = lib

contains(BUILD_TYPE, app) {
    QT += gui widgets
    TEMPLATE = app
} else {
    TEMPLATE = lib
    TARGET = FluidNC
}

DEFINES += FLUIDNC_LIBRARY
CONFIG += c++17
CONFIG -= debug_and_release

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CFLAGS += -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-missing-field-initializers
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-missing-field-initializers

DEFINES += DEBUG_UCNC_COMMUNICATION=1

SOURCES += \
    FluidNC/capture/AssertionFailed.cpp \
    FluidNC/capture/ExceptionHelper.cpp \
    FluidNC/capture/GPIOCapabilities.cpp \
    FluidNC/capture/Print.cpp \
    FluidNC/capture/PwmPin.cpp \
    FluidNC/capture/StartupLog.cpp \
    FluidNC/capture/Stream.cpp \
    FluidNC/capture/WString.cpp \
    # FluidNC/capture/WinConsole.cpp \
    FluidNC/capture/WinConsole.cpp \
    FluidNC/capture/fnc_uart.cpp \
    FluidNC/capture/freertos/Queue.cpp \
    FluidNC/capture/freertos/Task.cpp \
    FluidNC/capture/gpio.cpp \
    FluidNC/capture/gpio_dump.cpp \
    FluidNC/capture/i2s_out.cpp \
    FluidNC/capture/localfs.cpp \
    # FluidNC/capture/main.cpp \
    FluidNC/capture/nvs.cpp \
    FluidNC/capture/restart.cpp \
    FluidNC/capture/timed_engine.c \
    FluidNC/capture/timing.cpp \
    FluidNC/capture/watchdog.cpp \
    FluidNC/src/Channel.cpp \
    FluidNC/src/Configuration/AfterParse.cpp \
    FluidNC/src/Configuration/Completer.cpp \
    FluidNC/src/Configuration/GCodeParam.cpp \
    FluidNC/src/Configuration/Generator.cpp \
    FluidNC/src/Configuration/JsonGenerator.cpp \
    FluidNC/src/Configuration/LegacySettingRegistry.cpp \
    FluidNC/src/Configuration/Parser.cpp \
    FluidNC/src/Configuration/RuntimeSetting.cpp \
    FluidNC/src/Configuration/Tokenizer.cpp \
    FluidNC/src/Configuration/Validator.cpp \
    FluidNC/src/Control.cpp \
    FluidNC/src/CoolantControl.cpp \
    FluidNC/src/CustomCode.cpp \
    FluidNC/src/Error.cpp \
    FluidNC/src/Expression.cpp \
    FluidNC/src/Extenders/Extenders.cpp \
    FluidNC/src/Extenders/I2CPinExtenderBase.cpp \
    FluidNC/src/Extenders/PCA9535_9555.cpp \
    FluidNC/src/Extenders/PCA9539.cpp \
    FluidNC/src/Extenders/PinExtenderDriver.cpp \
    FluidNC/src/FileCommands.cpp \
    FluidNC/src/FileStream.cpp \
    FluidNC/src/Flowcontrol.cpp \
    FluidNC/src/FluidError.cpp \
    FluidNC/src/FluidPath.cpp \
    FluidNC/src/GCode.cpp \
    FluidNC/src/HashFS.cpp \
    FluidNC/src/InputFile.cpp \
    FluidNC/src/JSONEncoder.cpp \
    FluidNC/src/Job.cpp \
    FluidNC/src/Jog.cpp \
    FluidNC/src/Kinematics/Cartesian.cpp \
    FluidNC/src/Kinematics/CoreXY.cpp \
    FluidNC/src/Kinematics/Kinematics.cpp \
    FluidNC/src/Kinematics/Midtbot.cpp \
    FluidNC/src/Kinematics/ParallelDelta.cpp \
    FluidNC/src/Kinematics/WallPlotter.cpp \
    FluidNC/src/Limit.cpp \
    FluidNC/src/Logging.cpp \
    FluidNC/src/Machine/Axes.cpp \
    FluidNC/src/Machine/Axis.cpp \
    FluidNC/src/Machine/EventPin.cpp \
    FluidNC/src/Machine/Homing.cpp \
    FluidNC/src/Machine/I2CBus.cpp \
    FluidNC/src/Machine/I2SOBus.cpp \
    FluidNC/src/Machine/InputPin.cpp \
    FluidNC/src/Machine/LimitPin.cpp \
    FluidNC/src/Machine/MachineConfig.cpp \
    FluidNC/src/Machine/Macros.cpp \
    FluidNC/src/Machine/Motor.cpp \
    FluidNC/src/Machine/ProbeEventPin.cpp \
    FluidNC/src/Machine/SPIBus.cpp \
    FluidNC/src/Machine/UserInputs.cpp \
    FluidNC/src/Machine/UserOutputs.cpp \
    FluidNC/src/Main.cpp \
    FluidNC/src/MotionControl.cpp \
    FluidNC/src/Motors/MotorDriver.cpp \
    FluidNC/src/Motors/StandardStepper.cpp \
    FluidNC/src/Motors/StepStick.cpp \
    FluidNC/src/NutsBolts.cpp \
    FluidNC/src/Parameters.cpp \
    FluidNC/src/Parking.cpp \
    FluidNC/src/Pin.cpp \
    FluidNC/src/PinMapper.cpp \
    FluidNC/src/Pins/ChannelPinDetail.cpp \
    FluidNC/src/Pins/ErrorPinDetail.cpp \
    FluidNC/src/Pins/ExtPinDetail.cpp \
    FluidNC/src/Pins/GPIOPinDetail.cpp \
    FluidNC/src/Pins/I2SOPinDetail.cpp \
    FluidNC/src/Pins/PinAttributes.cpp \
    FluidNC/src/Pins/PinCapabilities.cpp \
    FluidNC/src/Pins/PinDetail.cpp \
    FluidNC/src/Pins/PinOptionsParser.cpp \
    FluidNC/src/Pins/VoidPinDetail.cpp \
    FluidNC/src/Planner.cpp \
    FluidNC/src/Probe.cpp \
    FluidNC/src/ProcessSettings.cpp \
    FluidNC/src/Protocol.cpp \
    FluidNC/src/RealtimeCmd.cpp \
    FluidNC/src/Regexpr.cpp \
    FluidNC/src/Report.cpp \
    FluidNC/src/Serial.cpp \
    FluidNC/src/Settings.cpp \
    FluidNC/src/SettingsDefinitions.cpp \
    FluidNC/src/Spindles/NullSpindle.cpp \
    FluidNC/src/Spindles/Spindle.cpp \
    FluidNC/src/Stepper.cpp \
    FluidNC/src/Stepping.cpp \
    FluidNC/src/System.cpp \
    FluidNC/src/UTF8.cpp \
    FluidNC/src/Uart.cpp \
    FluidNC/src/UartChannel.cpp \
    FluidNC/src/lineedit.cpp \
    FluidNC/src/string_util.cpp \
    FluidNC/src/version.cpp \
    FluidNC/src/xmodem.cpp

HEADERS += \
    FluidNC/capture/Arduino.h \
    FluidNC/capture/AssertionFailed.h \
    FluidNC/capture/Capture.h \
    FluidNC/capture/IPAddress.h \
    FluidNC/capture/NVSEmulator.h \
    FluidNC/capture/Platform.h \
    FluidNC/capture/Print.h \
    FluidNC/capture/Printable.h \
    FluidNC/capture/Stream.h \
    FluidNC/capture/USBCDCChannel.h \
    FluidNC/capture/WString.h \
    # FluidNC/capture/WinConsole.h \
    FluidNC/capture/WinConsole.h \
    FluidNC/capture/freertos/FreeRTOS.h \
    FluidNC/capture/freertos/FreeRTOSTypes.h \
    FluidNC/capture/freertos/Queue.h \
    FluidNC/capture/freertos/task.h \
    FluidNC/capture/freertos/timers.h \
    FluidNC/src/Channel.h \
    FluidNC/src/Configuration/AfterParse.h \
    FluidNC/src/Configuration/Completer.h \
    FluidNC/src/Configuration/Configurable.h \
    FluidNC/src/Configuration/GCodeParam.h \
    FluidNC/src/Configuration/Generator.h \
    FluidNC/src/Configuration/GenericFactory.h \
    FluidNC/src/Configuration/HandlerBase.h \
    FluidNC/src/Configuration/HandlerType.h \
    FluidNC/src/Configuration/JsonGenerator.h \
    FluidNC/src/Configuration/LegacySettingHandler.h \
    FluidNC/src/Configuration/LegacySettingRegistry.h \
    FluidNC/src/Configuration/Parser.h \
    FluidNC/src/Configuration/ParserHandler.h \
    FluidNC/src/Configuration/RuntimeSetting.h \
    FluidNC/src/Configuration/TokenState.h \
    FluidNC/src/Configuration/Tokenizer.h \
    FluidNC/src/Configuration/Validator.h \
    FluidNC/src/Configuration/parser_logging.h \
    FluidNC/src/Control.h \
    FluidNC/src/CoolantControl.h \
    FluidNC/src/Error.h \
    FluidNC/src/Expression.h \
    FluidNC/src/Extenders/Extenders.h \
    FluidNC/src/Extenders/I2CPinExtenderBase.h \
    FluidNC/src/Extenders/PCA9535_9555.h \
    FluidNC/src/Extenders/PCA9539.h \
    FluidNC/src/Extenders/PinExtender.h \
    FluidNC/src/Extenders/PinExtenderDriver.h \
    FluidNC/src/FileCommands.h \
    FluidNC/src/FileStream.h \
    FluidNC/src/Flowcontrol.h \
    FluidNC/src/FluidError.hpp \
    FluidNC/src/FluidPath.h \
    FluidNC/src/GCode.h \
    FluidNC/src/HashFS.h \
    FluidNC/src/JSONEncoder.h \
    FluidNC/src/Job.h \
    FluidNC/src/Jog.h \
    FluidNC/src/Kinematics/Cartesian.h \
    FluidNC/src/Kinematics/CoreXY.h \
    FluidNC/src/Kinematics/Kinematics.h \
    FluidNC/src/Kinematics/Midtbot.h \
    FluidNC/src/Kinematics/ParallelDelta.h \
    FluidNC/src/Kinematics/WallPlotter.h \
    FluidNC/src/Limit.h \
    FluidNC/src/Logging.h \
    FluidNC/src/Machine/Axes.h \
    FluidNC/src/Machine/Axis.h \
    FluidNC/src/Machine/EventPin.h \
    FluidNC/src/Machine/Homing.h \
    FluidNC/src/Machine/I2CBus.h \
    FluidNC/src/Machine/I2SOBus.h \
    FluidNC/src/Machine/InputPin.h \
    FluidNC/src/Machine/LimitPin.h \
    FluidNC/src/Machine/MachineConfig.h \
    FluidNC/src/Machine/Macros.h \
    FluidNC/src/Machine/Motor.h \
    FluidNC/src/Machine/SPIBus.h \
    FluidNC/src/Machine/UserInputs.h \
    FluidNC/src/Machine/UserOutputs.h \
    FluidNC/src/Main.h \
    FluidNC/src/MotionControl.h \
    FluidNC/src/Motors/MotorDriver.h \
    FluidNC/src/Motors/StandardStepper.h \
    FluidNC/src/Motors/StepStick.h \
    FluidNC/src/NutsBolts.h \
    FluidNC/src/Parameters.h \
    FluidNC/src/Parking.h \
    FluidNC/src/Pin.h \
    FluidNC/src/PinMapper.h \
    FluidNC/src/Pins/ChannelPinDetail.h \
    FluidNC/src/Pins/ErrorPinDetail.h \
    FluidNC/src/Pins/ExtPinDetail.h \
    FluidNC/src/Pins/GPIOPinDetail.h \
    FluidNC/src/Pins/I2SOPinDetail.h \
    FluidNC/src/Pins/PinAttributes.h \
    FluidNC/src/Pins/PinCapabilities.h \
    FluidNC/src/Pins/PinDetail.h \
    FluidNC/src/Pins/PinOptionsParser.h \
    FluidNC/src/Pins/VoidPinDetail.h \
    FluidNC/src/Planner.h \
    FluidNC/src/Probe.h \
    FluidNC/src/Protocol.h \
    FluidNC/src/RealtimeCmd.h \
    FluidNC/src/Regexpr.h \
    FluidNC/src/Report.h \
    FluidNC/src/Serial.h \
    FluidNC/src/Settings.h \
    FluidNC/src/SettingsDefinitions.h \
    FluidNC/src/Spindles/NullSpindle.h \
    FluidNC/src/Spindles/Spindle.h \
    FluidNC/src/Stepper.h \
    FluidNC/src/Stepping.h \
    FluidNC/src/System.h \
    FluidNC/src/UTF8.h \
    FluidNC/src/Uart.h \
    FluidNC/src/UartChannel.h \
    FluidNC/src/lineedit.h \
    FluidNC/src/string_util.h \
    FluidNC/src/xmodem.h \
    FluidNC_global.h

contains(BUILD_TYPE, app) {
    SOURCES += \
        FluidNC/app.cpp \
        FluidNC/connection.cpp \
        FluidNC/virtualucncconnection.cpp \
        FluidNC/mainwindow.cpp \
        fluidnc.cpp

    HEADERS += \
        FluidNC/app.h \
        FluidNC/connection.h \
        FluidNC/virtualucncconnection.h \
        FluidNC/mainwindow.h \
        fluidnc.h

    FORMS += \
        FluidNC/mainwindow.ui
} else {
    SOURCES += \
        FluidNC/library.cpp
}

INCLUDEPATH += FluidNC/capture
INCLUDEPATH += FluidNC/src
INCLUDEPATH += FluidNC/include

LIBS += -lcomdlg32 -limagehlp

win32 {
    TARGET_DEST_DIR = $$clean_path($$OUT_PWD/../../gpilot)
    # Quotes around paths to prevent forward slashes from being interpreted as switches by cmd/copy
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$$shell_path($$OUT_PWD/FluidNC.dll)\" \"$$shell_path($$TARGET_DEST_DIR)\")
}
