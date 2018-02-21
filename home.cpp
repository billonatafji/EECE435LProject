#include "home.h"
#include "ui_home.h"
#include <QDateTime>

Home::Home(QWidget *parent, QString username) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    QDate today = QDateTime::currentDateTime().date();
    //qDebug( );

    ui->welcomeLabel->setText(QString("<h1>%1 %2!</h1>").arg(today.toString("M/d/yy").toLatin1() == today.toString("M/d/yy").toLatin1()?"Happy Birthday": "Welcome",username));
    ui->profilePictureLabel->setPixmap(QPixmap("/home/eece435l/build-Lab2-Desktop_Qt_5_9_1_GCC_64bit-Debug/Images/bee_1.png"));

}

Home::~Home()
{
    delete ui;
}
