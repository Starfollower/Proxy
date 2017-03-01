#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <vector>
#include <memory>

class WorkFunc : public QObject
{
    Q_OBJECT
public slots:
    void registSocket(qintptr sockfd);
    void connection();
    void transferMessage();
};

class WorkThread : public QThread
{
public:
    WorkThread();
    void run() Q_DECL_OVERRIDE;
    WorkFunc *getWorkFuncPtr() const {return _workFuncSptr.get();}
private:
    std::shared_ptr<std::map<qintptr, QTcpSocket>> _socketMapSptr;
    std::shared_ptr<WorkFunc> _workFuncSptr;
};

#endif // WORKTHREAD_H
