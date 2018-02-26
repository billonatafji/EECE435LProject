#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    this->user = user;
    ui->welcomeLabel->setText(QString("<h2>%1 %2 %3 !</h2>").arg(this->user->DateOfBirth == QDateTime::currentDateTime().date().toString("M/d/yy").toLatin1()?"Happy Birthday": "Welcome", user->FirstName, user->LastName));
    ui->profilePictureLabel->setPixmap(QPixmap::fromImage(this->user->ProfilePicture));

    LoadScores(Game1::name);
    LoadScores(Game2::name);
}

Home::~Home()
{
    delete ui;
}



void Home::LoadScores(QString game){
    QStringList scores = Scores::GetUserScores(this->user->Username,game);
    qSort(scores.begin(),scores.end(), qGreater<QString>());
    if(game == Game1::name){
        ui->game1ScoresList->clear();
        ui->game1ScoresList->addItems(scores);
        ui->game1HighestScoreLabel->setText(QString("<h4>Highest Score <br /><br /> %1</h4>").arg(Scores::GetHighestScore(game)));
    }else{
        ui->game2ScoresList->clear();
        ui->game2ScoresList->addItems(scores);
        ui->game2HighestScoreLabel->setText(QString("<h4>Highest Score <br /><br /> %1</h4>").arg(Scores::GetHighestScore(game)));
    }
}


void Home::on_newGame1Button_clicked()
{
    Game1 game1(NULL,this->user);
    game1.setModal(true);
    game1.exec();
}

void Home::on_resumeGame1Button_clicked()
{
    Scores::AddScore(this->user->Username,QString::number(rand() % 10), Game1::name);
    LoadScores(Game1::name);
}

void Home::on_newGameButton_2_clicked()
{
    Game2 game2(NULL,this->user);
    game2.setModal(true);
    game2.exec();
}

void Home::on_resumeGame2Button_clicked()
{
    Scores::AddScore(this->user->Username,QString::number(rand() % 10), Game2::name);
    LoadScores(Game2::name);
}
