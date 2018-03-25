#include "header.h"

Header::Header(SpongeBob* player, int difficulty)
{
    this->player = player;
    this->time = 120;
    this->difficulty = difficulty;

    AddCleanlMeter(0,5);
    AddPause(450,0);
    AddTime(500,10);
    AddHeart(625,0,2);
    AddHeart(675,0,1);
    AddHeart(725,0,0);
    AddLevel(800,0);
    AddScore(800,20);
    AddChart(875,0,100,100,0*16,180*16/3,Qt::green);
    AddChart(875,0,100,100,60*16,180*16/3,Qt::yellow);
    AddChart(875,0,100,100,120*16,180*16/3,Qt::red);
    AddNeedle(925,50);

    QTimer *timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(CountDown()));
    //QObject::connect(this->pause,SIGNAL(QGraphicsItem::mouseReleaseEvent()),this,SLOT(PauseGame()));
    timer->start(1000);

    Render();

}

void Header::SetCleanliness(int val)
{
    if(this->player->cleanliness + val > 0 && this->player->cleanliness + val < 100)
    {
        this->player->cleanliness += val;

    }
    else if(this->player->cleanliness + val <= 0){
        this->player->cleanliness += 0;
    }
    else if(this->player->cleanliness + val >= 100){
        this->player->cleanliness = 100;
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
        this->player->immunity = 0;
    }
    else if(this->player->immunity + val > 100){
        this->player->immunity = 100;
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
    QBrush brush(color);
    brush.setStyle(Qt::Dense4Pattern);

    item->setBrush(brush);
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
    this->timeLabel->setPlainText(QString::number(time/60) + QString(":") + QString::number(time%60));
    this->timeLabel->setPos(x,y);
    this->addToGroup(this->timeLabel);
}

void Header::AddLevel(int x, int y){
    this->levelLabel = new QGraphicsTextItem();
    this->levelLabel->setPlainText(QString("Level: ").append(QString::number(this->difficulty)));
    this->levelLabel->setPos(x, y);
    this->addToGroup(this->levelLabel);

}

void Header::AddScore(int x, int y){
    this->scoreLabel = new QGraphicsTextItem();
    this->scoreLabel->setPlainText(QString("Score: ").append(QString::number(this->player->score)));
    this->scoreLabel->setPos(x, y);
    this->addToGroup(this->scoreLabel);
}

void Header::AddNeedle(int x, int y){
    this->needle = new  QGraphicsLineItem(x,y,x,y);
    QPen pen(Qt::black);
    pen.setWidth(3);
    this->needle->setPen(pen);
    this->addToGroup(this->needle);

}

void Header::AddPause(int x, int y){
    this->pause = new Pause();
    this->pause->setPixmap(QPixmap("../Project435/images/pause.png").scaledToHeight(50));
    this->pause->setPos(x,y);
    this->addToGroup(this->pause);
}

void Header::Render(){

    this->cleanlinessMeter->ProgressBar->setValue(this->player->cleanliness);
    this->scoreLabel->setPlainText(QString("Score: ").append(QString::number(this->player->score)));
    this->timeLabel->setPlainText(QString::number(time/60) + QString(":") + QString::number(time%60));
    int x2 = this->needle->line().x1() - 30*cos(this->player->immunity*M_PI/100.0) ;
    int y2 = this->needle->line().y1() - 30*sin(this->player->immunity*M_PI/100.0) ;

    this->needle->setLine(this->needle->line().x1(),this->needle->line().y1(),x2,y2);

}

void Header::RemoveLife(){
    if(this->player->lives>0){
        this->scene()->removeItem(this->hearts[--this->player->lives]);
        delete this->hearts[this->player->lives];
    }
}

void Header::CountDown(){
    this->time--;
    Render();
    if(this->time<=0){

    }
}

void Header::PauseGame(){
    int i = 0;
}

