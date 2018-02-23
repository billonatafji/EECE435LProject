#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include "user.h"
#include "home.h"

namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = 0);
    ~SignIn();

private slots:
    void on_cancelButton_clicked();

    void on_signInButton_clicked();

private:
    Ui::SignIn *ui;
};

#endif // SIGNIN_H
