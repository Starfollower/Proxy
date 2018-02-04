#include "tunnelclient.h"
using namespace std;

TunnelClient::TunnelClient(const QString &hostName, quint16 port)
	: _hostName(hostName),
	  _port(port)
{
}

void TunnelClient::start()
{
        _socketSptr = std::make_shared<QTcpSocket>();
		connect(_socketSptr.get(), &QTcpSocket::connected, this, &TunnelClient::connected);
		connect(_socketSptr.get(), &QTcpSocket::disconnected, this, &TunnelClient::disconnected);
		connect(_socketSptr.get(), &QTcpSocket::readyRead, this, &TunnelClient::replyFromHost);
		_socketSptr->connectToHost(_hostName, _port);
}

//void TunnelClient::socketConnected()
//{
//	emit connected();
//}

//void TunnelClient::socketDisconnected()
//{
//	emit disconnected();
//}

void TunnelClient::replyFromHost()
{
	char buffer[12];
	int32_t dataLen;
	int32_t socketFd;

	if (_socketSptr->read(buffer, sizeof(buffer)) <= 0) {		// 数据头接收错误
		return;
	}
	if (!(buffer[0] & 0x02				// 校验失败
		  && buffer[1] & 0x02
		  && buffer[2] & 0x02
		  && buffer[3] & 0x02))
		return;

	dataLen = reinterpret_cast<int32_t>(buffer + 4);
	socketFd = reinterpret_cast<int32_t>(buffer + 8);
	//std::shared_ptr<char[]> dataBuffer(new char[dataLen]);
	auto dataSptr = std::make_shared<vector<char>>();
	dataSptr->resize(dataLen);
	int recvLen;
	int index = 0;
	int allRecvLen;
	while (_socketSptr->waitForReadyRead(3000)) {
		recvLen = _socketSptr->read(dataSptr->data() + index, dataLen - allRecvLen);
		if (recvLen == dataLen - allRecvLen) {
			break;
		}
		index += recvLen;
		dataLen -= recvLen;
		allRecvLen += recvLen;
	}
	//> 连接超时，抛弃数据
	//if (allRecvLen < dataLen) {

	//}
	emit readyRead(socketFd, dataSptr);
}
