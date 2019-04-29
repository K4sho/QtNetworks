#include "mainwindow.h"
#include <QApplication>
#include "myclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyClient client("localhost", 2323);
    client.show();
    return a.exec();
}
