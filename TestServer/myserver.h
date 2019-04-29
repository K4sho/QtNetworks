#pragma once
#include <QtWidgets>
#include <QTime>
#include <QString>

class QTcpServer;
class QTextEdit;
class QTcpSocket;

// =======================================

class MyServer : public QWidget {
    Q_OBJECT
private:
    QTcpServer* m_ptcpServer;   // Основа управления сервером
    QTextEdit* m_ptxt;          // Информация о происходящих соединениях
    quint16 m_nNextBlockSize;   // Служит для хранения длины следующего полученного от сокета блока
    void sendToClient(QTcpSocket* pSocket, const QString& srt);
public:
    MyServer(int nPort, QWidget* pwgt = 0);
public slots:
    virtual void slotNewConnection();
    void slotReadClient();
};

