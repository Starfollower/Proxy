#include "socks5.h"
#include "logger.h"

#include <algorithm>

Socks5::Socks5()
{

}

bool Socks5::communication(const std::shared_ptr<QTcpSocket> &socketPtr)
{
    if (!socketPtr->waitForReadyRead(1000)) {
        writeLog("out of time!");
        return false;
    }
    QByteArray receiveBuf;
    receiveBuf = socketPtr->readAll();
    if (receiveBuf.size() != 3) {
        writeLog("Receive wrong format data from client!");
        return false;
    }
    char versionCode = 0x05;
    if (receiveBuf[0] != versionCode) {
        writeLog("Version mismatching!");
        return false;
    }
    char nmethodsCode = 0x01;
    char methodsCode = 0x00;
    if (receiveBuf[1] != nmethodsCode || receiveBuf[2] != methodsCode) {
        writeLog("Only support no authentication required model!");
        return false;
    }

    char accepted[2] = {0x05, 0x00};
    if (socketPtr->write(accepted, 2) != 2) {
        return false;
    }

    receiveBuf.clear();

    if (!socketPtr->waitForReadyRead(1000)) {
        writeLog("out of time!");
        return false;
    }
    receiveBuf = socketPtr->readAll();
    if (receiveBuf[0] != versionCode) {
        writeLog("Version mismatching!");
        return false;
    }
    char connectCode = 0x01;
    if (receiveBuf[1] != connectCode) {
        writeLog("Only support connect model!");
        return false;
    }
    const char IPV4Code = 0x01;
    const char domainCode = 0x03;
    const char IPV6Code = 0x04;
    switch (receiveBuf[3]) {
    case IPV4Code: {
        _IPV4[0] = receiveBuf[4];
        _IPV4[1] = receiveBuf[5];
        _IPV4[2] = receiveBuf[6];
        _IPV4[3] = receiveBuf[7];
        std::copy(receiveBuf.data() + 8, receiveBuf.data() + 10, &_dstPort);
        _ATYPType = ADDRTYPE::IPV4;
        break;
    }
    case domainCode: {
        int len = receiveBuf[4];
        _domainAddr = QString::fromLocal8Bit(receiveBuf.data() + 5, len);
        //std::copy(receiveBuf.data() + 5 + len, receiveBuf.data() + 7 + len, &_dstPort);
        _dstPort = receiveBuf[5+len] << 8 | receiveBuf[6+len];
        _ATYPType = ADDRTYPE::DOMAINNAME;
        break;
    }
    case IPV6Code:
        writeLog("Not support IPV6 for now!");
        break;
    default:
        writeLog("ATYP code incorrect!");
        break;
    }
    receiveBuf.clear();

    QByteArray replyBuf;
    replyBuf.resize(10);
    replyBuf[0] = 0x05;
    replyBuf[1] = 0x00;
    replyBuf[2] = 0x00;
    replyBuf[3] = 0x01;
    replyBuf[4] = 0x7f;
    replyBuf[5] = 0x00;
    replyBuf[6] = 0x00;
    replyBuf[7] = 0x01;
    replyBuf[8] = 0xcb;
    replyBuf[9] = 0xfe;
    if (socketPtr->write(replyBuf) != 10) {
        return false;
    }

    return true;
}
