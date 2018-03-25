#include "signin.h"
#include "ui_signin.h"
#include "error.h"

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
    User* user = User::GetUser(ui->userNameEdit->text(),ui->passwordEdit->text());
    if(user->Username == ui->userNameEdit->text() && ui->userNameEdit->text() != ""){
        this->close();
        Home home(NULL, user);
        home.exec();
    }
    else{
        Error error(QString("The Username or Password You Entered  is Incorrect"));
        error.setModal(true);
        error.exec();
    }
}

