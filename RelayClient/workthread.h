#ifndef WORKTHREAD_H
#define WORKTHREAD_H

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

class WorkThread : public QThread
{
    Q_OBJECT

public:
    WorkThread();
    void run() Q_DECL_OVERRIDE;
	void setName(const char *str) { this->setObjectName(str); }
public slots:
    void handleNewConnection(qintptr socket);
	void handleClose(qintptr);
private:
	void handleMessage(std::shared_ptr<TcpConnection>);
private:
    std::shared_ptr<std::map<qintptr, std::shared_ptr<TcpConnection>>> _socketsMapSptr;
	std::map<qintptr, int> _testMap;
	//std::map<qintptr, TcpConnection> _socketMap;
};

#endif // WORKTHREAD_H
