#ifndef RELAYHUB_H
#define RELAYHUB_H

#include "tcpconnthread.h"

#include <QObject>
#include <QTcpServer>
#include <string>
#include <memory>
#include <vector>
#include <map>


class RelayHub : public QTcpServer
{
   Q_OBJECT

public:
    RelayHub();
    ~RelayHub();
public:
    void start();
    QString status();
signals:
    void statusChanged(QString statusStr);
    void acceptConnection(qintptr handle);
protected:
    void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;
private slots:
    //void receiveNewConnection();
    void connThreadExited(int sockfd);
private:
    const uint8_t _threadNum = 3;
    const quint16 _serverPort = 22222;
    quint16 _backendPort = 22222;
    QString _backendIp;
    QTcpSocket _backend;
    QString _statusStr;
    std::map<int, std::shared_ptr<TcpConnThread>> _connThreadMap;
};

#endif // RELAYHUB_H
