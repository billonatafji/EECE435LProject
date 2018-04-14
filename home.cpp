/**
* \file home.cpp
* \brief home class definition
*
* the home page is where the user is redirected after signing in.
*
*\author Bilal Natafgi
*\date 23-2-2018
*/
#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    this->user = user;
    ui->welcomeLabel->setText(QString("<h2>%1 %2 %3 !</h2>").arg(this->user->DateOfBirth == QDateTime::currentDateTime().date().toString("M/d/yy").toLatin1()?"Happy Birthday": "Welcome", user->FirstName, user->LastName));///< happy birthday if his birthday is today
    ui->profilePictureLabel->setPixmap(QPixmap::fromImage(this->user->ProfilePicture));
}
/// destructor
Home::~Home()
{
    delete ui;
}

/// cehck history
void Home::on_historyButton_clicked()
{
    History history(NULL,this->user);
    history.setModal(true);
    history.exec();
}
/// play game 1
void Home::on_game1Button_clicked()
{
    Gamemenu gamemenu(NULL,Game1::name, this->user);
    gamemenu.setModal(true);
    gamemenu.exec();
}

/// play game 2
void Home::on_game2Button_clicked()
{
    Gamemenu gamemenu(NULL,Game2::name, this->user);
    gamemenu.setModal(true);
    gamemenu.exec();
}

void Home::on_backButton_clicked()
{
    this->close();
}
