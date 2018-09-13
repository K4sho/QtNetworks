#-------------------------------------------------
#
# Project created by QtCreator 2018-09-06T11:38:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myclient.cpp

HEADERS  += mainwindow.h \
    myclient.h

FORMS    += mainwindow.ui
