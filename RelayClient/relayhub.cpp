#include "relayhub.h"

#include <QtNetwork>

RelayHub::RelayHub()
{
	qRegisterMetaType<qintptr>("qintptr");
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

    // create thread pool
    for (int i = 0; i < _threadNum; ++i) {
        std::shared_ptr<QThread> threadSptr = std::make_shared<QThread>();
		threadSptr->setObjectName("Server work thread");
		std::shared_ptr<TcpWorker> workerSptr = std::make_shared<TcpWorker>();
        _workerMap.insert(std::make_pair(i, workerSptr));
		_threadMap.insert(std::make_pair(i, threadSptr));
		workerSptr->moveToThread(threadSptr.get());
		threadSptr->start();
    }
}

void RelayHub::incomingConnection(qintptr socketfd)
{
	if (_workerMap.empty()) return;
	if (_assignThreadNum >= _workerMap.size())
		_assignThreadNum = 0;
	std::shared_ptr<TcpWorker> workerSptr = _workerMap.at(_assignThreadNum);
	connect(this, &RelayHub::newConnection, workerSptr.get(), &TcpWorker::handleNewConnection);
	++_assignThreadNum;
	emit newConnection(socketfd);
    //connect(this, &RelayHub::newConnection, _workThreadMap[_assignThreadNum]->getWorkFuncPtr(), &WorkFunc::registSocket);
    //std::shared_ptr<TcpConnThread> threadSptr = std::make_shared<TcpConnThread>(handle);
    //QThread *threadPtr = threadSptr.get();
    //_connThreadMap.insert(std::make_pair(handle, threadSptr));
    //connect(threadSptr.get(), &TcpConnThread::threadExiting, this, &RelayHub::connThreadExited);
    //threadSptr->start();
}

void RelayHub::connThreadExited(int sockfd)
{
	sockfd = 0;
    //_connThreadMap.erase(sockfd);
}

RelayHub::~RelayHub()
{
    this->close();
    //_connThreadMap.clear();
}
