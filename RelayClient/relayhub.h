#ifndef RELAYHUB_H
#define RELAYHUB_H

#include "tcpconnthread.h"
#include "tcpworker.h"

#include <QObject>
#include <QTcpServer>
#include <string>
#include <memory>
#include <vector>
#include <map>

Q_DECLARE_METATYPE(qintptr)

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
    void newConnection(qintptr handle);
	void exit();
protected:
    void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;
private slots:
    //void receiveNewConnection();
    void connThreadExited(int sockfd);
private:
    const uint8_t _threadNum = 3;
    const quint16 _serverPort = 22222;
    uint8_t _assignThreadNum = 0;
    quint16 _backendPort = 22222;
    QString _backendIp;
    QTcpSocket _backend;
    QString _statusStr;
    //std::map<int, std::shared_ptr<TcpConnThread>> _connThreadMap;
	std::map<int, std::shared_ptr<QThread>> _threadMap;
    std::map<int, std::shared_ptr<TcpWorker>> _workerMap;
};

#endif // RELAYHUB_H
