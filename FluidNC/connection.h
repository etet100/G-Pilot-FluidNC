// This file is a part of "G-Pilot GCode Sender" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2024 BTS

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

enum class ConnectionState
{
    NoConnectionDevice,
    Initialization,
    Connecting,
    Connected,
    Disconnecting,
    Disconnected,
    InvalidConfiguration,
};

class Connection : public QObject
{
    Q_OBJECT

    public:
        Connection(QObject *parent);
        virtual ~Connection() {}

        // true = waiting for connection, false = already connected or failed to connect
        virtual bool open() = 0;
        virtual void sendChar(QChar);
        virtual void sendChar(char);
        virtual void sendByteArray(QByteArray) = 0;
        virtual void sendLine(QString) = 0;
        virtual void close() = 0;
        virtual QString name() = 0;

        ConnectionState state() const { return m_state; }
        bool isConnected() const { return m_state == ConnectionState::Connected; }

    protected:
        ConnectionState m_state;
        void setState(ConnectionState state);

    signals:
        void lineReceived(const QString &line);
        void error(const QString &text);
        void stateChanged(ConnectionState state);
};

#endif
