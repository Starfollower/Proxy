#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <vector>
#include <memory>

class WorkFunc
{
    Q_OBJECT
public slots:
    void registSocket();
    void connection();
    void transferMessage();
};

class WorkThread : public QThread
{
public:
    WorkThread();
    void run() Q_DECL_OVERRIDE;
    WorkFunc *getWorkFuncPtr() const {return _workFunc.get();}
private:
    std::shared_ptr<std::map<qintptr, QTcpSocket>> _socketMapPtr;
    std::shared_ptr<WorkFunc> _workFunc;
};

#endif // WORKTHREAD_H
