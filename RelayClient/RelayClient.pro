#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T09:27:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RelayClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    relayhub.cpp \
    tcpconnthread.cpp \
    socks5.cpp \
    logger.cpp \
    workthread.cpp \
    tcpconnection.cpp \

HEADERS  += mainwindow.h \
    relayhub.h \
    tcpconnthread.h \
    socks5.h \
    logger.h \
    workthread.h \
    tcpconnection.h \
    tunnelclient.h

FORMS    += mainwindow.ui
