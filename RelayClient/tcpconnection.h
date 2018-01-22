#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "CallBacks.h"

#include <QTcpSocket>
#include <memory>

//using ConnectionCallback = std::function<void (const QTcpSocket &)>;

class TcpConnection : public QObject, public std::enable_shared_from_this<TcpConnection>
{
    Q_OBJECT

public:
	//using WriteCallback = std::function<void(TcpConnection &)>;
public:
    TcpConnection(const std::shared_ptr<QTcpSocket> &);
	~TcpConnection();
    void setReadCallback(std::function<void(std::shared_ptr<TcpConnection>)> cb) { _readCb = cb; }
	QByteArray readAll() { return _socket->readAll(); }
	std::shared_ptr<TcpConnection> getSharedPtr() { return shared_from_this(); }
private slots:
    //void handleNewConnection(qintptr socket);
    void handleRead();
    //void handleWrite();
    void handleError();
    //void handleClose();

private:
    int _socketfd;
    std::shared_ptr<QTcpSocket> _socket;
    //ConnectionCallback _connectionCb;
	//std::function<void(TcpConnection &)> _readCb;
	ReadCallback _readCb;
};

#endif // TCPCONNECTION_H
