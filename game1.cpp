/**
* \file game1.cpp
* \brief game1 class definition
*
*  the class game1 is used to select the difficulty of the game, add the score and create the scene of game1
*\author Bilal Natafgi
*\date 21-2-2018
*/

#include "game1.h"
#include "ui_game1.h"

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "game1scene.h"
#include "gameview.h"

Game1::Game1(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::Game1)
{
    ui->setupUi(this);
    this->user = user;
    int userLevel = User::GetUserLevel(Game1::name,this->user->Username);
    if(userLevel<2){
        ui->mediumRadioButton->setEnabled(false);
    }
    if(userLevel<3){
        ui->hardRadioButton->setEnabled(false);
    }
}

Game1::~Game1()
{
    delete ui;
    delete this->gameView;
}

void Game1::on_backButton_clicked()
{
    this->close();
}

void Game1::on_playButton_clicked()
{
    if(ui->easyRadioButton->isChecked() ||  ui->mediumRadioButton->isChecked() || ui->hardRadioButton->isChecked()){
        if(this->user->Username != ""){
            Scores::AddScore(user->Username,QString::number(rand() % 10),Game1::name);
        }
        this->close();

        Game::SetDifficulty(ui->easyRadioButton->isChecked(), ui->mediumRadioButton->isChecked(), ui->hardRadioButton->isChecked());

        this->gameView = new GameView();

        game1scene* scene1 = new game1scene(this->gameView,Game::New, this->user->Username,this->Difficulty);

        gameView->setScene(scene1);

        gameView->setModal(true);
        gameView->exec();

    }
}

QString Game1::name = "Game1";
