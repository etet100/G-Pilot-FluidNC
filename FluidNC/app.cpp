#include "app.h"
#include "virtualucncconnection.h"
#include <QTimer>

App::App(QObject *parent) : QObject(parent)
{
    conn = new VirtualUCNCConnection(this);
    connect(conn, &VirtualUCNCConnection::lineReceived, this, [this](QString line) {
        qDebug() << "[FluidNC] << " << line;
        emit lineReceived(line);
    });

    QTimer::singleShot(100, [this]() {
        conn->open();
    });
}

void App::send(QString command)
{
    qDebug() << "[FluidNC] >> " << command;
    conn->sendLine(command);
}
