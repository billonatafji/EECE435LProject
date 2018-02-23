#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_cancelButton_clicked()
{
    this->close();
}

void SignIn::on_signInButton_clicked()
{
    User* user = User::GetUser("billo","Abcd1234");
    if(user->Username == ui->userNameEdit->text() && ui->userNameEdit->text() != ""){
        this->close();
        Home home(NULL, user);
        home.exec();
    }
}

