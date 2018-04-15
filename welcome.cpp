/**
* \file welcome.cpp
* \brief welcome class definition
*
* welcome class with its functions
*\author Bilal Natafgi
*\date 18-3-2018
*/

#include "welcome.h"
#include "ui_welcome.h"
#include "signup.h"
#include "signin.h"

Welcome::Welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);

    QFile file("Users.txt");

    QJsonDocument document;

    if (file.open(QFile::ReadOnly)) {
        document = QJsonDocument().fromJson(file.readAll());
        file.close();
    }
    if(file.open(QFile::WriteOnly)){
        QJsonObject rootObject = document.object();

        QJsonObject gameObject;
        gameObject["HighestScore"] = "";
        gameObject["HighestScoreUser"] = "";

        if(!rootObject.contains("Game1")){
            rootObject["Game1"] = gameObject;
        }
        if(!rootObject.contains("Game2")){
            rootObject["Game2"] = gameObject;
        }
        document.setObject(rootObject);
        file.write(document.toJson());
        file.close();

    }
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

void Welcome::on_userGame1Button_clicked()
{
    Game1 game1;
    game1.setModal(true);
    game1.exec();
}

void Welcome::on_userGame2Button_clicked()
{
    Game2 game2;
    game2.setModal(true);
    game2.exec();
}
