#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = 0);
    ~SignUp();

private slots:
    void on_cancelButton_clicked();

    void on_signUpButton_clicked();


    void on_browseButton_clicked();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
