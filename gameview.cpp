#include "gameview.h"
#include "ui_gameview.h"

GameView::GameView(QWidget *parent, QGraphicsScene *gameScene) :
    QDialog(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(gameScene);
    ui->graphicsView->setFixedSize(1000,600);
    ui->graphicsView->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    ui->graphicsView->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    ui->graphicsView->show();
    ui->graphicsView->setFocus();
}

GameView::~GameView()
{
    delete ui;
}
