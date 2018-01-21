#include "tcpconnection.h"

TcpConnection::TcpConnection(const std::shared_ptr<QTcpSocket> &socketPtr)
{
	_socket = socketPtr;
	QObject::connect(_socket.get(), &QTcpSocket::readyRead, this, &TcpConnection::handleRead);
	QObject::connect(_socket.get(), QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TcpConnection::handleError);
}

void TcpConnection::handleRead()
{
	if (_readCb != nullptr) {
		_readCb(getSharedPtr());
	}
	else {
		_socket->skip(std::numeric_limits<int64_t>::max());		// discards data
	}
}

void TcpConnection::handleError()
{
		// TODO: add log;
}

//void TcpConnection::handleNewConnection(qintptr socketfd)
//{
//    QTcpSocket curSocket = QTcpSocket(this);
//    if (!curSocket.setSocketDescriptor(socketfd)) {     // initialize failed,return
//        curSocket.close();
//        return;
//    }
//
//    if (_connectionCb != nullptr) {
//        _connectionCb(curSocket);
//    }
//}
