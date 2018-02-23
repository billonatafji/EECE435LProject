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
