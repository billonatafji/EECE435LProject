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
}

Game1::~Game1()
{
    delete ui;
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
        Game::SetDifficulty(ui->easyRadioButton->isChecked(), ui->mediumRadioButton->isChecked(), ui->hardRadioButton->isChecked());

        game1scene* scene1 = new game1scene(this->Difficulty);
        GameView gameView(NULL, scene1);
        gameView.setModal(true);
        gameView.exec();
        this->close();
    }
}

QString Game1::name = "Game1";
