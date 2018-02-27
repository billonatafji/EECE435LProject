#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>
#include "game1.h"
#include "game2.h"

namespace Ui {
class Welcome;
}

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = 0);
    ~Welcome();

private slots:
    void on_signupButton_clicked();

    void on_signinbutton_clicked();

    void on_userGame1Button_clicked();

    void on_userGame2Button_clicked();

private:
    Ui::Welcome *ui;
};

#endif // WELCOME_H
