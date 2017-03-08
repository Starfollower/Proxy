#include "workthread.h"
#include "socks5.h"

WorkThread::WorkThread()
{

}

void WorkThread::run()
{
    _workFuncSptr = std::make_shared<WorkFunc>();
}

WorkFunc::WorkFunc()
{
    _socketMapSptr = std::make_shared<std::map<qintptr,QTcpSocket>>();
}

void WorkFunc::registSocket(qintptr sockfd)
{
    QTcpSocket curSocket = QTcpSocket();
    if (!curSocket.setSocketDescriptor(sockfd)) {
        curSocket.close();
        return;
    }

    Socks5 socks5;
    if (!socks5.communication(curSocket)) {
        curSocket.close();
        return;
    }

    _socketMapSptr->insert(std::make_pair(sockfd, curSocket));
}

void WorkFunc::connection()
{

}

void WorkFunc::transferMessage()
{

}
