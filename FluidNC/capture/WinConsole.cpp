#include <conio.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "Serial.h"  // allChannels
#include "Driver/Console.h"
#include "WinConsole.h"

// @GPILOT
#include <QDebug>
#include <QtCore>
#include <QCoreApplication>

void gpilotLockProbeAtCurrentPosition(void);
void gpilotResetProbePosition(void);
void gpilotSetHome(bool abs, double x, double y, double z);
void gpilotSetSingleLimit(int axis, double pos);
void gpilotEstop();
// @GPILOT

extern void cleanupThreads();

static void deinit() {
    // editModeOn();
    // SetConsoleMode(hStdout, fdwOldOutMode);
    // SetConsoleMode(hStdin, fdwOldInMode);
    // SetConsoleTextAttribute(hStdout, wOldColorAttrs);
    // cleanupThreads();
}

WinConsole::WinConsole(bool addCR) : Channel("WindowsConsole", addCR) {}

size_t WinConsole::write(uint8_t ch) {
    char c = (char)ch;
    socket->write(&c, 1);

    return 1;
}

// Stream methods (Channel inherits from Stream)
int WinConsole::available(void) {
    return socket->bytesAvailable();
}

int WinConsole::read() {
    static uint32_t tick = 0;
    if (tick++ > 1000) {
        tick = 0;
        QCoreApplication::processEvents();
    }

    if (!socket->isOpen()) {
        qDebug() << "[IO][FluidNC][DLL] read - Socket not open";
    }
    if (!socket->isReadable()) {
        qDebug() << "[IO][FluidNC][DLL] read - socket not readable";
    }
    if (!controlSocket->isOpen()) {
        qDebug() << "[IO][FluidNC][DLL] read - Control socket not open";
    }
    if (!controlSocket->isReadable()) {
        qDebug() << "[IO][FluidNC][DLL] read - Control socket not readable";
    }

    // @GPilot
    static QString ctrlBuffer = "";
    controlSocket->waitForReadyRead(0);
    if (controlSocket->bytesAvailable()) {
        ctrlBuffer += controlSocket->readAll();

        int pos;
        while ((pos = ctrlBuffer.indexOf("\n")) != -1) {
            QString line = ctrlBuffer.left(pos).trimmed();
            ctrlBuffer = ctrlBuffer.mid(pos + 1);

            qDebug() << "[uCNC] Received:" << line;

            // Process control commands here
            QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
            if (!doc.isNull() && doc.isObject()) {
                QJsonObject obj = doc.object();
                QString cmd = obj["cmd"].toString();

                if (cmd == "probe_at_current") {
                    gpilotLockProbeAtCurrentPosition();
                } else if (cmd == "reset_probe") {
                    gpilotResetProbePosition();
                } else if (cmd == "set_home") {
                    gpilotSetHome(
                        obj["abs"].toBool(),
                        obj["x"].toDouble(),
                        obj["y"].toDouble(),
                        obj["z"].toDouble()
                    );
                } else if (cmd == "set_single_limit") {
                    //{\"axis\":2,\"cmd\":\"set_single_limit\",\"pos\":25}"
                    gpilotSetSingleLimit(
                        obj["axis"].toInt(),
                        obj["pos"].toDouble()
                    );
                } else if (cmd == "estop") {
                    gpilotEstop();
                }
            }
        }
    }
    // @GPilot

    socket->waitForReadyRead(0);
    if (!socket->bytesAvailable()) {
        return -1;
    }

    char c;
    socket->read(&c, 1);

    return (unsigned char) c;
}

void WinConsole::init() {
    _lineedit = new Lineedit(this, _line, Channel::maxLine - 1);
    allChannels.registration(this);
    log_info("WinConsole created");
}

int WinConsole::rx_buffer_available() {
    return 128 - available();
}

bool WinConsole::realtimeOkay(char c) {
    return _lineedit->realtime(c);
}

bool WinConsole::lineComplete(char* line, char c) {
    if (_lineedit->step(c)) {
        _linelen        = _lineedit->finish();
        _line[_linelen] = '\0';
        strcpy(line, _line);
        _linelen = 0;
        return true;
    }
    return false;
}

WinConsole winConsole(true);
Channel&   Console = winConsole;
