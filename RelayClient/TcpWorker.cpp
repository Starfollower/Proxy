#include "tcpworker.h"
#include "socks5.h"
#include "tcpconnection.h"
#include <QTextCodec>

using namespace std::placeholders;

TcpWorker::TcpWorker()
{
	_socketsMapSptr = std::make_shared<std::map<qintptr, std::shared_ptr<TcpConnection>>>();
}

//void TcpWorker::run()
//{
//	this->exec();
//}

void TcpWorker::handleNewConnection(qintptr socketfd)
{
	std::shared_ptr<QTcpSocket> curSocketSptr = std::make_shared<QTcpSocket>();
    //QTcpSocket curSocket;
    if (!curSocketSptr->setSocketDescriptor(socketfd)) {     // initialize failed,return
        curSocketSptr->close();
        return;
    }

    Socks5 socks5;
    if (!socks5.communication(curSocketSptr)) {
        curSocketSptr->close();
        return;
    }

    std::shared_ptr<TcpConnection> connectionSptr = std::make_shared<TcpConnection>(curSocketSptr);
	//std::function<void(TcpConnection &)> f = std::bind(&TcpWorker::handleMessage, this, _1);
	//connection.setReadCallback(std::bind(&TcpWorker::hanleMessage, this, _1));
	//connection.setReadCallback(f);
	//connectionSptr->setReadCallback(std::bind(&TcpWorker::handleMessage, _1));
	connectionSptr->setReadCallback(std::bind(handleMessage2, _1));
    _socketsMapSptr->insert(std::make_pair(socketfd, connectionSptr));
	//_testMap.insert(std::make_pair(1, 2));
	//_socketMap.insert(std::make_pair(socketfd, connection));
	//_socketsMapSptr->insert(std::pair<qintptr, TcpConnection>(socketfd, connection));
}

void handleMessage2(std::shared_ptr<TcpConnection> connection)
{
	auto message = connection->readAll();
	QString qs = QTextCodec::codecForName("UTF-8")->toUnicode(message);
	std::string s = qs.toStdString();
}

void TcpWorker::handleClose(qintptr socketfd)
{
    _socketsMapSptr->erase(socketfd);
}

void TcpWorker::handleMessage(std::shared_ptr<TcpConnection> connection)
{
	auto message = connection->readAll();
}

void TcpWorker::closeSockets()
{
	_socketsMapSptr->clear();
}

TcpWorker::~TcpWorker()
{
	closeSockets();
}

//WorkFunc::WorkFunc()
//{
//    _socketMapSptr = std::make_shared<std::map<qintptr,QTcpSocket>>();
//}
//
//void WorkFunc::registSocket(qintptr sockfd)
//{
//    QTcpSocket curSocket = QTcpSocket();
//    if (!curSocket.setSocketDescriptor(sockfd)) {
//        curSocket.close();
//        return;
//    }
//
//    Socks5 socks5;
//    if (!socks5.communication(curSocket)) {
//        curSocket.close();
//        return;
//    }
//
//    _socketMapSptr->insert(std::make_pair(sockfd, curSocket));
//}
//
//void WorkFunc::connection()
//{
//
//}
//
//void WorkFunc::transferMessage()
//{
//
//}
