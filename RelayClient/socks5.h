#ifndef SOCKS5_H
#define SOCKS5_H

#include <QTcpSocket>
#include <memory>

class Socks5
{
    enum ADDRTYPE {IPV4, DOMAINNAME, IPV6};
public:
    Socks5();
    bool communication(const std::shared_ptr<QTcpSocket> &socketPtr);
    bool communication(QTcpSocket &socket);
    inline ADDRTYPE dstAddrType() { return _ATYPType; }
private:
    char _IPV4[4];
    quint16 _dstPort;
    QString _domainAddr;
    enum ADDRTYPE _ATYPType;
};

#endif // SOCKS5_H
