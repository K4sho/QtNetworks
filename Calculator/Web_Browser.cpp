#include "Web_Browser.h"
#include <QProgressBar>

Web_Browser::Web_Browser(QWidget *wgt) : QWidget (wgt)
{
    button_back = new QPushButton("<-");
    button_forward = new QPushButton("->");
    w_view = new QWebEngineView();
    txt_edit = new QLineEdit("http://www.bhv.ru");

    button_back->setEnabled(false);
    button_forward->setEnabled(false);

    QProgressBar* progress_bar = new QProgressBar;
    QPushButton* button_go = new QPushButton("&GO");
    QPushButton* button_stop = new QPushButton("&STOP");
    QPushButton* button_refresh = new QPushButton("&REFRESH");

}

void Web_Browser::slotGo() {
    if (!txt_edit->text().startsWith("ftp://")
    && txt_edit->text().startsWith("http://")
    && txt_edit->text().startsWith("gopher: //")) {
        txt_edit->setText("http://" + txt_edit->text());
    }
    w_view->load(QUrl(txt_edit->text()));
}
