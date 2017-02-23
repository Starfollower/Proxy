#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "relayhub.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _relayHubPtr(std::make_shared<RelayHub> ()),
    _statusLabelPtr(std::make_shared<QLabel> ())
{
    ui->setupUi(this);
    connect(_relayHubPtr.get(), &RelayHub::statusChanged, this, &MainWindow::changeStatus);
    this->statusBar()->setStyleSheet(QString("QStatusBar::item{border:0px}"));		// 清除任务栏的竖线
    this->statusBar()->addWidget(_statusLabelPtr.get());
    _relayHubPtr->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStatus(QString statusStr)
{
    _statusLabelPtr->setText(statusStr);
}
