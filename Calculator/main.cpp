#include <QApplication>
#include "Web_Browser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Web_Browser web_browser;
    web_browser.show();
    a.exec();

    return a.exec();
}
