#include "game2.h"
#include "ui_game2.h"

Game2::Game2(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::Game2)
{
    ui->setupUi(this);
    this->user = user;
}

Game2::~Game2()
{
    delete ui;
}

void Game2::on_backButton_clicked()
{
    this->close();
}

void Game2::on_playButton_clicked()
{
    if(ui->easyRadioButton->isChecked() ||  ui->mediumRadioButton->isChecked() || ui->hardRadioButton->isChecked()){
        if(this->user->Username != ""){
            Scores::AddScore(user->Username,QString::number(rand() % 10),Game2::name);
        }
        Game::SetDifficulty(ui->easyRadioButton->isChecked(), ui->mediumRadioButton->isChecked(), ui->hardRadioButton->isChecked());
        this->close();
    }
}

QString Game2::name = "Game2";
