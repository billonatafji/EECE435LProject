#include "header.h"

Header::Header(SpongeBob* player, int level)
{
    this->player = player;
    this->time = 120;
    this->score = 0;
    this->level = level;
    this->cleanliness=100;

    //SetCleanliness(100);
    AddCleanlMeter(0,5);
    AddTime(450,5);
    AddHeart(550,0,0);
    AddHeart(600,0,0);
    AddHeart(650,0,0);
    AddLevel(725,0);
    AddScore(725,20);
    AddChart(800,0,200,100,0*16,180*16/3,Qt::red);
    AddChart(800,0,200,100,60*16,180*16/3,Qt::yellow);
    AddChart(800,0,200,100,120*16,180*16/3,Qt::green);
    AddNeedle(800+100,0);

}

void Header::SetCleanliness(int val)
{
    if(this->cleanliness + val > 0 && this->cleanliness + val < 100)
    {
        this->cleanliness += val;

    }
    else if(this->cleanliness + val < 0){

    }
    else if(this->cleanliness + val < 100){

    }
    Render();

}
void Header::SetImmunity(int val)
{
    if(this->player->immunity + val >= 0 && this->player->immunity + val <= 100)
    {
        this->player->immunity += val;

    }
    else if(this->player->immunity + val < 0){

    }
    else if(this->player->immunity + val < 100){

    }
    Render();

}
void Header::AddCleanlMeter(int x, int y)
{
    this->cleanlinessMeter = new CleanlinessMeter();
    cleanlinessMeter->setPos(x,y);
    this->addToGroup(cleanlinessMeter);
}

void Header::AddChart(int x, int y, int width, int height, int startAngle, int spanAngle, QColor color)
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(x, y, width, height);
    item->setPen(QPen(color));
    item->setBrush(QBrush(color));
    item->setStartAngle(startAngle);
    item->setSpanAngle(spanAngle);
    this->addToGroup(item);
}

void Header::AddHeart(int x, int y, int number){
    this->hearts[number] = new QGraphicsPixmapItem(QPixmap("../Project435/images/heart.png").scaledToHeight(50));
    this->hearts[number]->setPos(x,y);
    this->addToGroup(this->hearts[number]);
}

void Header::AddTime(int x, int y){
    this->timeLabel = new QGraphicsTextItem();
    timeLabel->setPlainText(QString::number(time/60) + QString(":") + QString::number(time%60));
    timeLabel->setPos(x,y);
    this->addToGroup(this->timeLabel);
}

void Header::AddLevel(int x, int y){
    this->levelLabel = new QGraphicsTextItem();
    this->levelLabel->setPlainText(QString("Level: ").append(QString::number(this->level)));
    this->levelLabel->setPos(x, y);
    this->addToGroup(this->levelLabel);

}

void Header::AddScore(int x, int y){
    this->scoreLabel = new QGraphicsTextItem();
    this->scoreLabel->setPlainText(QString("Score: ").append(QString::number(this->score)));
    this->scoreLabel->setPos(x, y);
    this->addToGroup(this->scoreLabel);
}

void Header::AddNeedle(int x, int y){
    this->needle = new  QGraphicsLineItem(x,y,x,y+50);
    this->needle->setPen(QPen(Qt::blue));
    this->addToGroup(this->needle);

}

void Header::Render(){
    //this->cleanlinessMeter->
}
