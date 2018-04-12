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
}

Game2::~Game2()
{
    delete ui;
    delete this->gameView;
}

void Game2::on_backButton_clicked()
{
    this->close();
}

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
