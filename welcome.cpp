#include "welcome.h"
#include "ui_welcome.h"
#include "signup.h"
#include "signin.h"

Welcome::Welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;

}

void Welcome::on_signupButton_clicked()
{
    SignUp signUp;
    signUp.setModal(true);
    signUp.exec();
}

void Welcome::on_signinbutton_clicked()
{
    SignIn signIn;
    signIn.setModal(true);
    signIn.exec();
}
