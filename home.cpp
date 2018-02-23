#include "home.h"
#include "ui_home.h"
#include "stdlib.h"

Home::Home(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    this->user = user;
    ui->welcomeLabel->setText(QString("<h2>%1 %2 %3 !</h2>").arg(this->user->DateOfBirth == QDateTime::currentDateTime().date().toString("M/d/yy").toLatin1()?"Happy Birthday": "Welcome", user->FirstName, user->LastName));
    ui->profilePictureLabel->setPixmap(QPixmap::fromImage(this->user->ProfilePicture));

    LoadScores();

}

Home::~Home()
{
    delete ui;
}

void Home::on_pushButton_clicked()
{
    Scores::AddScore(this->user->Username,QString::number(rand() % 10), "Game1");
    LoadScores();

}

void Home::LoadScores(){
    ui->scoresList->clear();
    QStringList scores = Scores::GetUserScores(this->user->Username,"Game1");
    qSort(scores.begin(),scores.end(), qGreater<QString>());
    ui->scoresList->addItems(scores);
    ui->highestScoreLabel->setText(QString("<h4>Highest Score <br /><br /> %1</h4>").arg(Scores::GetHighestScore("Game1")));
}
