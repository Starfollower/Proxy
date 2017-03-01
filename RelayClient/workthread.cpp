#include "workthread.h"

WorkThread::WorkThread()
{

}

void WorkThread::run()
{
    _socketMapSptr = std::make_shared<std::map<qintptr,QTcpSocket>>();
    _workFuncSptr = std::make_shared<WorkFunc>();
}

void WorkFunc::registSocket(qintptr sockfd)
{

}

void WorkFunc::connection()
{

}

void WorkFunc::transferMessage()
{

}
