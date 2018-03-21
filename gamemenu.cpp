#include "gamemenu.h"
#include "ui_gamemenu.h"

Gamemenu::Gamemenu(QWidget *parent, QString game, User* user) :
    QDialog(parent),
    ui(new Ui::Gamemenu)
{
    ui->setupUi(this);
    this->Game = game;
    this->user = user;

    ui->highestScoreLabel->setText(QString("<h4>Highest Score <br /><br /> %1</h4>").arg(Scores::GetHighestScore(this->Game)));
    ui->gameLabel->setText(QString("<h1>%1</h1>").arg(this->Game));
}

Gamemenu::~Gamemenu()
{
    delete ui;
}

void Gamemenu::on_descriptionButton_clicked()
{
    Description description(NULL,this->Game);
    description.setModal(true);
    description.exec();
}

void Gamemenu::on_resumeGameButton_clicked()
{
    Scores::AddScore(this->user->Username,QString::number(rand() % 10), this->Game);
}

void Gamemenu::on_newGameButton_clicked()
{
    if(this->Game == Game1::name){
        Game1 game1(NULL,this->user);
        game1.setModal(true);
        game1.exec();
    }else{
        Game2 game2(NULL,this->user);
        game2.setModal(true);
        game2.exec();
    }

}

void Gamemenu::on_backButton_clicked()
{
    this->close();
}
