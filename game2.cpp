/**
* \file game2.cpp
* \brief Game2 class definition
*
* a Game2 is where the user selects the strength of the game to play
*\author Bilal Natafgi
*\date 22-2-2018
*/
#include "game2.h"
#include "ui_game2.h"
#include "gameview.h"
#include "game2scene.h"

Game2::Game2(QWidget *parent, User* user) :
    QDialog(parent),
    ui(new Ui::Game2)
{
    ui->setupUi(this);
    this->user = user;
    this->gameView = new GameView();

//    int userLevel = User::GetUserLevel(Game2::name,this->user->Username);
//    if(userLevel<2){
//        ui->mediumRadioButton->setEnabled(false);
//    }
//    if(userLevel<3){
//        ui->hardRadioButton->setEnabled(false);
//    }
}

Game2::~Game2()
{
    delete ui;
    delete this->gameView;
}
///close view if back button is clicked.
void Game2::on_backButton_clicked()
{
    this->close();
}
/// setting dificulty based on what is selected by the user.
void Game2::on_playButton_clicked()
{
    if(ui->easyRadioButton->isChecked() ||  ui->mediumRadioButton->isChecked() || ui->hardRadioButton->isChecked()){

        this->close();

        Game::SetDifficulty(ui->easyRadioButton->isChecked(), ui->mediumRadioButton->isChecked(), ui->hardRadioButton->isChecked());

        Game2Scene* scene = new Game2Scene(gameView,Game::New, this->user->Username,this->Difficulty);

        gameView->setScene(scene);

        gameView->setModal(true);
        gameView->exec();
        this->close();
    }
}

QString Game2::name = "Game2";
