#include "fluidnc.h"
#include <QApplication>
#include <QThread>
#include <QLocalSocket>
#include <QLocalServer>
#include <QUuid>
#include "FluidNC/virtualucncconnection.h"
#include "FluidNC/app.h"
#include "FluidNC/mainwindow.h"

extern void setup();
extern void loop();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    App a2;
    a2.connect(&a2, &App::lineReceived, &w, &MainWindow::addToHistory);
    w.connect(&w, &MainWindow::command, &a2, &App::send);

    a.exec();

    return 0;
}
