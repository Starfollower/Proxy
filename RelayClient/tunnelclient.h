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
	void connected();			// �����ѽ���
	void readyRead(int, std::shared_ptr<std::vector<char>>);		// ֪ͨAcceptor�ɶ�
	void disconnected();		// tunnel �����ж�
public slots:
	void start();
	void sendToHost();			// �����˷�������
private slots:
	void replyFromHost();		// �������Է���˵�����
	//void socketConnected();
	//void socketDisconnected();
private:
	QString _hostName;		// ���������
	quint16 _port;			// ����˶˿�
	std::shared_ptr<QTcpSocket> _socketSptr;
}

#endif // TUNNELCLIENT_H
