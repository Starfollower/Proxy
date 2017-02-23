#include "workthread.h"

WorkThread::WorkThread()
{

}

void WorkThread::run()
{
    _socketMapPtr = std::make_shared(std::map<qintptr,QTcpSocket>);
    _workFunc = std::make_shared(WorkFunc);
}
