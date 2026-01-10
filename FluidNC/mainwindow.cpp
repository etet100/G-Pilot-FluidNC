#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->send, &QPushButton::clicked, this, [this]() {
        QString cmd = ui->command->text().trimmed();
        if (!cmd.length()) {
            return;
        }
        emit command(cmd);
        ui->command->clear();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addToHistory(QString msg)
{
    ui->history->append(msg);
}
