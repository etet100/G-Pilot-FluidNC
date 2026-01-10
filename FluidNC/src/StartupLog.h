// Copyright (c) 2021 -  Mitch Bradley
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include "Config.h"
#include "Channel.h"
#include <QLocalSocket>

class StartupLog : public Channel {
public:
    StartupLog();
    virtual ~StartupLog();

    void setSocket(QLocalSocket* socket_) { socket = socket_; }

    size_t write(uint8_t data) override;

    static void dump(Channel& channel);

private:
    QLocalSocket* socket;
};

extern StartupLog startupLog;
