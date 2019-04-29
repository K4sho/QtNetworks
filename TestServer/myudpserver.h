#pragma once
#include "QUdpSocket"
#include <QTextEdit>

class UdpServer : public QTextEdit {
    Q_OBJECT
private:
    QUdpSocket* m_pudp; //  Объект сокета, указатель на него
public:
    UdpServer (QWidget* pwgt = 0);
private slots:
    void slotSendDatagram();    // Слот для пересылки дэйтаграммы
};

