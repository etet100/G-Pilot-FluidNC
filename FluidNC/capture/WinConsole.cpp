#include <conio.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "Serial.h"  // allChannels
#include "Driver/Console.h"
#include "WinConsole.h"

#include <QDebug>
#include <QCoreApplication>

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
    if (tick++ > 10000) {
        tick = 0;
        QCoreApplication::processEvents();
    }

    if (!socket->isOpen()) {
        qDebug() << "WinConsole::read(): socket not open";
    }
    if (!socket->isReadable()) {
        qDebug() << "WinConsole::read(): socket not readable";
    }
    // socket->write("ab\n");  // Trigger read
    // delay_ms(400);

    socket->waitForReadyRead(0);
    if (!socket->bytesAvailable()) {
        return -1;
    }

    char c;
    socket->read(&c, 1);
    qDebug() << c;

    return c;
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
