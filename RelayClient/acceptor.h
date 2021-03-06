#ifndef TCPWORKER_H
#define TCPWORKER_H

#include "CallBacks.h"

#include <QThread>
#include <QTcpSocket>
#include <vector>
#include <memory>
#include <functional>

//class WorkFunc : public QObject
//{
//    Q_OBJECT
//public:
//    WorkFunc();
//public slots:
//    void registSocket(qintptr sockfd);
//    void connection();
//    void transferMessage();
//private:
//    std::shared_ptr<std::map<qintptr, QTcpSocket>> _socketMapSptr;
//};

class TcpConnection;
void handleMessage2(std::shared_ptr<TcpConnection> connection);

class Acceptor : public QObject 
{
    Q_OBJECT

public:
    Acceptor();
	~Acceptor();
    //void run() Q_DECL_OVERRIDE;
	//void setName(const char *str) { this->setObjectName(str); }
    void setReadCallback(std::function<void(std::shared_ptr<TcpConnection>)> cb) { _readCb = cb; }
public slots:
    void handleNewConnection(qintptr socket);
	void handleClose(qintptr);
	void closeSockets();
private:
	void handleMessage(std::shared_ptr<TcpConnection>);
private:
	ReadCallback _readCb;
    std::shared_ptr<std::map<qintptr, std::shared_ptr<TcpConnection>>> _socketsMapSptr;
	//std::map<qintptr, TcpConnection> _socketMap;
};

#endif // TCPWORKER_H
