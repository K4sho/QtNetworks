#ifndef WEB_BROWSER_H
#define WEB_BROWSER_H

#include <QWidget>
#include <QWebEngineView>
#include <QPushButton>
#include <QLineEdit>

class Web_Browser : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* txt_edit;
    QPushButton* button_forward;
    QPushButton* button_back;
    QWebEngineView* w_view;
public:
    Web_Browser(QWidget *wgt = 0);
private slots:
    void slotGo ();
    void slotFinished(bool);
};

#endif // WEB_BROWSER_H
