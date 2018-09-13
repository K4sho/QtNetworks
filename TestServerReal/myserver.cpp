#include "myserver.h"
#include <QTcpServer>
#include <QTcpSocket>

MyServer::MyServer(int nPort, QWidget *pwgt) : QWidget(pwgt), m_nNextBlockSize(0) {
    m_ptcpServer = new QTcpServer(this);
    // Что бы включить сервер - вызывается метод listen() и передается номер порта
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0, "Server Error", "Unable to start the server:" + m_ptcpServer->errorString());
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true); // Текстовое поле, созданное только для чтения информации

    // Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}

// Метод вызывается каждый раз при соединении с новым клиентом.
/*virtual*/ void MyServer::slotNewConnection() {
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();                  // Возвращает сокет, посредством которого можно осуществлять дальнейшую связь с клиентом
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater())); // Уничтожение сокета при отключении
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));          // При поступлении запросов от клиентов отправляется сигнал readyToRead
    sendToClient(pClientSocket, "Server Response: Connected!");
}

//
void MyServer::slotReadClient() {
    QTcpSocket* pClientSocket = (QTcpSocket*)sender(); // Преобразование указателя, возвращаемого sender() к типу QTcpSocket
    QDataStream in (pClientSocket);
    in.setVersion(QDataStream::Qt_5_5);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime time;
        QString str;
        in >> time >> str; // Если размер доступных для чтения данных больше или равен размеру блока, тогда данные считываются из потока в переменные time и str

        QString strMessage =
                time.toString() + " " + "Client has sent - " + str;
        m_ptxt->append(strMessage);

        m_nNextBlockSize = 0;

        sendToClient(pClientSocket, "Server Response: Received \"" + str + "\""); // Сообщаем клиенту о том, что нам успешно получилось прочитать данные
    }
}

void MyServer::sendToClient(QTcpSocket *pSocket, const QString &str) {
    QByteArray arrBlock;
    QDataStream out (&arrBlock, QIODevice::WriteOnly); // записываем все данные блока
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);  // Перемещение указателя на начало блока
    out << quint16(arrBlock.size() - sizeof(quint16)); // Записываем в поток

    pSocket->write(arrBlock); // Созданный блок записывается в сокет
}
