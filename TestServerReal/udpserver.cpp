#include "myudpserver.h"
#include <QTimer>
#include <QDataStream>
#include <QDateTime>

// Конструктор класса UdpServer
UdpServer::UdpServer(QWidget *pwgt = 0) : QTextEdit(pwgt) {
    setWindowTitle("UdpServer");

    m_pudp = new QUdpSocket(this);

    QTimer* ptimer = new QTimer(this); // Создаем таймер
    ptimer->setInterval(500);          // Задаем в таймере интервал 0,5 сек (500 мск)
    ptimer->start();                   // Запускаем таймер
    // Соединяем таймер со слотом пересылки дэйтаграмм
    connect(ptimer, SIGNAL(timeout()), SLOT(slotSendDatagram()));   // Пересылка дайтаграмм осуществляется через интервал времени при помощи таймера
}

// Реализация функции отправки дэйтаграмм
void UdpServer::slotSendDatagram() {
    QByteArray baDatagram;                      // Класс потока QDataStream для помещения данных в объект baDatagram
    QDataStream out(&baDatagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    QDateTime dt = QDateTime::currentDateTime();
    append("Sent:" + dt.toString());
    out << dt;
    // QHostAdress::LocalHost содержит строковую константу 127.0.0.1
    m_pudp->writeDatagram(baDatagram, QHostAddress::LocalHost, 2424);   // Пересылаем дэйтаграмму
}
