#-------------------------------------------------
#
# Project created by QtCreator 2018-09-06T14:31:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestServerReal
TEMPLATE = app


SOURCES += main.cpp\
    myserver.cpp \
    udpserver.cpp \
    udpclient.cpp

HEADERS  += \
    myserver.h \
    myudpserver.h \
    udpclient.h

FORMS    += mainwindow.ui
