/**
* \file signin.cpp
* \brief SignIn class definition
*
* the SignIn class
*\author Bilal natafgi
*\date 20-2-2018
*/
#include "signin.h"
#include "ui_signin.h"
#include "error.h"
/**
 * @brief SignIn::SignIn
 * @param parent
 *
 * constructor
 */
SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
}
///desctructor
SignIn::~SignIn()
{
    delete ui;
}
/// closing on cancle button click
void SignIn::on_cancelButton_clicked()
{
    this->close();
}
/**
 * @brief SignIn::on_signInButton_clicked
 *
 * on signin button click, check if the username and password match any of those in the database
 * if yes, call home. else display error message
 */
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

