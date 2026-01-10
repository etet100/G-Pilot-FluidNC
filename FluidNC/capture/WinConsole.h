#pragma once

#include <QString>
#include "Channel.h"
#include "lineedit.h"
#include <QLocalSocket>

class WinConsole : public Channel {
private:
    Lineedit* _lineedit;
    QLocalSocket *socket;

public:
    WinConsole(bool addCR = false);

    void init() override;
    void setSocket(QLocalSocket* socket_) { socket = socket_; }

    // Print methods (Stream inherits from Print)
    size_t write(uint8_t c) override;

    // Stream methods (Channel inherits from Stream)
    int available(void) override;
    int read() override;

    // Channel methods
    int  rx_buffer_available() override;
    bool realtimeOkay(char c) override;
    bool lineComplete(char* line, char c) override;
};
