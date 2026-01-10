#ifndef APP_H
#define APP_H

#include <QObject>

class VirtualUCNCConnection;

class App : public QObject
{
    Q_OBJECT

public:
    App(QObject *parent = nullptr);
    void send(QString command);

signals:
    void lineReceived(QString msg);

private:
    VirtualUCNCConnection* conn;
};

#endif // APP_H
