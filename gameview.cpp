#include "gameview.h"
#include "ui_gameview.h"

GameView::GameView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    this->gameScene = new QGraphicsScene();

}

GameView::~GameView()
{
    delete ui;
    //delete this->gameScene;
}

void GameView::setScene(QGraphicsScene* gameScene){
    this->gameScene = gameScene;
    ui->graphicsView->setScene(this->gameScene);
    ui->graphicsView->setFixedSize(1000,600);
    ui->graphicsView->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    ui->graphicsView->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    ui->graphicsView->show();
    ui->graphicsView->setFocus();

}


