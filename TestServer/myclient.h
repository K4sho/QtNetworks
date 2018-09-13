#pragma once

#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
#include <QTime>

class QTextEdit;
class QLineEdit;

// =============================================

class MyClient : public QWidget {
    Q_OBJECT
private:
    QTcpSocket* m_sok;      // собственно сам сокет
    QTextEdit* m_ptxtxinfo;  // Отображение информации (текста)
    QLineEdit* m_ptxtinput; // Ввод информации(текста)
    quint16 NextBlockSize;  // Размер блока данных
public:
    MyClient (const QString& strHost, int nPort, QWidget* pwgt = 0) ;
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotConnected();
    void slotSendToServer();
};
