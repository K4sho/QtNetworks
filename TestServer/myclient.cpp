#include "myclient.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

// Реализация конструктора
MyClient::MyClient(const QString &strHost, int nPort, QWidget *pwgt) : QWidget(pwgt), NextBlockSize(0)
{
    m_sok = new QTcpSocket(this);

    m_sok->connectToHost(strHost, nPort);   // Создается объект сокета и вызывается метод сокета, в который передаем имя компьютера и номер порта
                                            // Устанавливается связь с сервером

    connect(m_sok, SIGNAL(connected()), SLOT(slotConnected())); // Сокет отправляет сигнал connected() как только будет создано соединение
    connect(m_sok,SIGNAL(readyRead()),SLOT(slotReadyRead()));   // Сигнал readyRead - при готовности передавать данные
    connect(m_sok, SIGNAL(error(QAbstractSocket::SocketError)), this , SLOT(slotError(QAbstractSocket::SocketError)));

    /*
     * Далее - создание интерфейса программы
     */
    m_ptxtxinfo = new QTextEdit;
    m_ptxtinput = new QLineEdit;

    m_ptxtxinfo->setReadOnly(true);
    QPushButton* pcmd = new QPushButton("&Send");
    connect(pcmd, SIGNAL(clicked()),SLOT(slotSendToServer()));  // Отправка данных на сервер
    connect(m_ptxtinput, SIGNAL(returnPressed()), this, SLOT(slotSendToServer()));  // Аналогично, просто для того, что бы отправка осуществлялась и по нажатию "Enter"

    // Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel ("<H1>Client</H1>"));  // Добавляем заголовок
    pvbxLayout->addWidget(m_ptxtxinfo);                     // Добавляем поле отображения
    pvbxLayout->addWidget(m_ptxtinput);                     // Добавляем поле ввода
    pvbxLayout->addWidget(pcmd);                            // Добавляем кнопку "Send"
    setLayout(pvbxLayout);
}

// Реализация слота готовности передачи данных. Вызывается при поступлении данных от сервера
void MyClient::slotReadyRead() {
    QDataStream in (m_sok);
    in.setVersion(QDataStream::Qt_5_5);
    for (;;) { // Цикл for нужен, потому что не все данные могут прийти одновременно
        if (!NextBlockSize) {
            if (m_sok->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> NextBlockSize;
        }

        if (m_sok->bytesAvailable() < NextBlockSize) {
            break;
        }
        QTime time;
        QString str;
        in >> time >> str;

        m_ptxtxinfo->append(time.toString() + " " + str);  // Полученная информация добавляется в виджет многострочного текстового поля
        NextBlockSize = 0;                                 // Это значит, что размер очередного блока данных неизвестен
    }
}

// Реализация обработчика ошибки
void MyClient::slotError(QAbstractSocket::SocketError err) {
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ? "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ? "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ? "The connection was refused." :
                         QString(m_sok->errorString()));
    m_ptxtxinfo->append(strError);
}

// Реализация отправки на сервер
void MyClient::slotSendToServer() {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << QTime::currentTime() << m_ptxtinput->text();


    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_sok->write(arrBlock);
    m_ptxtinput->setText("");   // после отсылки данных - стираем текст в поле ввода сообщения
}

// Реализация метода соединения
void MyClient::slotConnected() {
    m_ptxtxinfo->append("Received the connected() signal");
}
