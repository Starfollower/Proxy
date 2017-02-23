#include "tcpconnthread.h"
#include "socks5.h"

#include <QTcpSocket>

TcpConnThread::TcpConnThread(qintptr socketDescriptor) :
    _socketfd(socketDescriptor),
    _socket(nullptr)
{
}

void TcpConnThread::run()
{
    _socket = std::make_shared<QTcpSocket>();
    if (!_socket->setSocketDescriptor(_socketfd)) {
        // TODO
        _socket->errorString();
        _socket->close();
        emit threadExiting(this->getSocketfd());
    }

    Socks5 socks5;
    if (!socks5.communication(_socket)) {
        _socket->abort();
        emit threadExiting(this->getSocketfd());
        return;
    }


    connect(_socket.get(), &QTcpSocket::readyRead, this, &TcpConnThread::handleIncomingMessage);
    connect(_socket.get(), &QTcpSocket::disconnected, this, &TcpConnThread::connectionBroken);
}

void TcpConnThread::handleIncomingMessage()
{
    QByteArray byteArry = _socket->readAll();
}

void TcpConnThread::connectionBroken()
{
    _socket->abort();
    emit threadExiting(this->getSocketfd());		// notify relayHub
}

TcpConnThread::~TcpConnThread()
{
    //_socket->deleteLater();
}
