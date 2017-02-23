#include "relayhub.h"

#include <QtNetwork>

RelayHub::RelayHub()
{

}

void RelayHub::start()
{
    //! [0] get the IP
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    //! [0]

    if (this->listen(QHostAddress::Any,_serverPort)) {
        _statusStr = QString("Server is running on IP: %1, Port: %2").arg(ipAddress).arg(_serverPort);
    } else {
        _statusStr = QString("Failed to start server: %1").arg(this->errorString());
    }
    emit statusChanged(_statusStr);

    //connect(this, &QTcpServer::newConnection, this, &RelayHub::receiveNewConnection);
}

void RelayHub::incomingConnection(qintptr handle)
{
    //std::shared_ptr<TcpConnThread> threadSptr = std::make_shared<TcpConnThread>(handle);
    //QThread *threadPtr = threadSptr.get();
    //_connThreadMap.insert(std::make_pair(handle, threadSptr));
    //connect(threadSptr.get(), &TcpConnThread::threadExiting, this, &RelayHub::connThreadExited);
    //threadSptr->start();
}

void RelayHub::connThreadExited(int sockfd)
{
    _connThreadMap.erase(sockfd);
}

RelayHub::~RelayHub()
{
    this->close();
    _connThreadMap.clear();
}
