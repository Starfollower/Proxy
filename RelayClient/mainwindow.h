#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class RelayHub;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void changeStatus(QString);
private:
    Ui::MainWindow *ui;
    std::shared_ptr<RelayHub> _relayHubPtr;
    std::shared_ptr<QLabel> _statusLabelPtr;
};

#endif // MAINWINDOW_H
