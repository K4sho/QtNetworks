#include <udpclient.h>

UdpClient::UdpClient(QWidget *pwgt = 0) : QTextEdit(pwgt) {
    setWindowTitle("UdpClient");

    m_pudp = new QUdpSocket(this);
    m_pudp->bind(2424); // Привязываем сокет к порту 2424
    // Т.к мы не указали IP-адресс порта, сокет по-умолчанию будет использовать локальный хост
    connect(m_pudp,SIGNAL(readyRead()),SLOT(slotProcessDatagrams())); // Для извлечения и отображения полученных дейтаграмм соединяем сигнал сокета со слотом
}

// Реализуем метод получения дэйтаграмм
void UdpClient::slotProcessDatagrams() {
    QByteArray baDatagram;                 // Создаем объект, который будет хранить данные

    do {
        baDatagram.resize(m_pudp->pendingDatagramSize());   // Узнаем размер дэйтаграммы, ждущей обработки и меняем размер буфера под нее
        m_pudp->readDatagram(baDatagram.data(), baDatagram.size()); // Копируем в буфер данные из baDatagram
    } while (m_pudp->hasPendingDatagrams());

    QDateTime dateTime;
    QDataStream in (&baDatagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_5);
    in >> dateTime;
    append("Recevied:" + dateTime.toString());
}
