#ifndef TCPCONNTHREAD_H
#define TCPCONNTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <memory>

class QTcpSocket;

class TcpConnThread : public QThread
{
    Q_OBJECT

public:
    TcpConnThread(qintptr socketDescriptor);
    ~TcpConnThread();
    void run() Q_DECL_OVERRIDE;
    inline int getSocketfd() { return _socketfd; }
signals:
    void threadExiting(int sockfd);
private slots:
    void handleIncomingMessage();
    void connectionBroken();
private:
    int _socketfd;
    std::shared_ptr<QTcpSocket> _socket;
    //QTcpSocket _socket;
};

#endif // TCPCONNTHREAD_H
