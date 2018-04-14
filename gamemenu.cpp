/**
* \file gamemenu.cpp
* \brief Gamemenu class definition
*
* a Gamemenu is where the user can enter the games, or check his highscore and game descriptiond
*\author Bilal Natafgi
*\date 20-2-2018
*/
#include "gamemenu.h"
#include "ui_gamemenu.h"
#include "game1scene.h"
#include "game2scene.h"
#include "gameview.h"
#include "game.h"
#include "error.h"

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
/// destructor
Gamemenu::~Gamemenu()
{
    delete ui;
}
/// display description of the game
void Gamemenu::on_descriptionButton_clicked()
{
    Description description(NULL,this->Game);
    description.setModal(true);
    description.exec();
}

/// trying to resume a previously saved game
void Gamemenu::on_resumeGameButton_clicked()
{
    if(this->Game == Game1::name){

        Header* header = User::ResumeGameForUser(this->Game,this->user->Username);
        if(!header->paused){
            GameView* gameView = new GameView();
            game1scene* scene1 = new game1scene(gameView, Game::Resume,this->user->Username, 0, header, false);///< creating a new game scene with the metrics of the paused game
            gameView->setScene(scene1);
            gameView->setModal(true);
            gameView->exec();
            this->close();
        }else{
            Error err(QString("No Resumable Game Available"));
            err.setModal(true);
            err.exec();
        }
    }else if(this->Game == Game2::name){

        Header* header = User::ResumeGameForUser(this->Game,this->user->Username);
        if(!header->paused){
            GameView* gameView = new GameView();
            Game2Scene* scene1 = new Game2Scene(gameView, Game::Resume,this->user->Username, 0, header, false);///< creating a new game scene with the metrics of the paused game
            gameView->setScene(scene1);
            gameView->setModal(true);
            gameView->exec();
            this->close();
        }else{
            Error err(QString("No Resumable Game Available"));
            err.setModal(true);
            err.exec();
        }
    }

}
/// new game
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
/// return to previous page
void Gamemenu::on_backButton_clicked()
{
    this->close();
}
