#include "immunitymeter.h"

ImmunityMeter::ImmunityMeter()
{
    this->time = 120;
    this->score = 0;
    this->level = 0;

    SetProgress(0);
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

void ImmunityMeter::SetProgress(int val)
{
    this->Progress = (double)val/100;
}
void ImmunityMeter::AddCleanlMeter(int x, int y)
{
    this->cleanlinessMeter = new CleanlinessMeter();
    cleanlinessMeter->setPos(x,y);
    this->addToGroup(cleanlinessMeter);
}

void ImmunityMeter::AddChart(int x, int y, int width, int height, int startAngle, int spanAngle, QColor color)
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(x, y, width, height);
    item->setPen(QPen(color));
    item->setBrush(QBrush(color));
    item->setStartAngle(startAngle);
    item->setSpanAngle(spanAngle);
    this->addToGroup(item);
}

void ImmunityMeter::AddHeart(int x, int y, int number){
    this->hearts[number] = new QGraphicsPixmapItem(QPixmap("../Project435/images/heart.png").scaledToHeight(50));
    this->hearts[number]->setPos(x,y);
    this->addToGroup(this->hearts[number]);
}

void ImmunityMeter::AddTime(int x, int y){
    this->timeLabel = new QGraphicsTextItem();
    timeLabel->setPlainText(QString::number(time/60) + QString(":") + QString::number(time%60));
    timeLabel->setPos(x,y);
    this->addToGroup(this->timeLabel);
}

void ImmunityMeter::AddLevel(int x, int y){
    this->levelLabel = new QGraphicsTextItem();
    this->levelLabel->setPlainText(QString("Level: ").append(QString::number(this->level)));
    this->levelLabel->setPos(x, y);
    this->addToGroup(this->levelLabel);

}

void ImmunityMeter::AddScore(int x, int y){
    this->scoreLabel = new QGraphicsTextItem();
    this->scoreLabel->setPlainText(QString("Score: ").append(QString::number(this->score)));
    this->scoreLabel->setPos(x, y);
    this->addToGroup(this->scoreLabel);
}

void ImmunityMeter::AddNeedle(int x, int y){
    this->needle = new  QGraphicsLineItem(x,y,x,y+50);
    this->needle->setPen(QPen(Qt::black));
    this->addToGroup(this->needle);

}
