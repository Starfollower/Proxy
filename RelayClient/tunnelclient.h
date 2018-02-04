#ifndef TUNNELCLIENT_H
#define TUNNELCLIENT_H

#include <QTcpSocket>
#include <memory>

//struct DeliverData 
//{
//	int32_t userCount;
//	std::shared_ptr<std::vector<char>> dataSptr;
//};

class TunnelClient : public QObject 
{
	Q_OBJECT

public:
	TunnelClient(const QString &, quint16);
public signals:
	void connected();			// 连接已建立
	void readyRead(int, std::shared_ptr<std::vector<char>>);		// 通知Acceptor可读
	void disconnected();		// tunnel 连接中断
public slots:
	void start();
	void sendToHost();			// 向服务端发送数据
private slots:
	void replyFromHost();		// 接收来自服务端的数据
	//void socketConnected();
	//void socketDisconnected();
private:
	QString _hostName;		// 服务端名称
	quint16 _port;			// 服务端端口
	std::shared_ptr<QTcpSocket> _socketSptr;
}

#endif // TUNNELCLIENT_H
