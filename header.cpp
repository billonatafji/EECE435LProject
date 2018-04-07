#include "header.h"
#include "user.h"
#include "game1scene.h"
#include <QApplication>

Header::Header(SpongeBob* player, int difficulty, QString username, QString game, bool completed, int time)
{
    this->player = player;
    this->difficulty = difficulty;
    this->username = username;
    this->game = game;
    this->completed = completed;
    this->time = time;
    this->currentBacteriaCountInScene=0;

    AddCleanlMeter(0,5);
    AddPause(450,0);
    AddTime(500,10);
    AddHearts(725,0);
    AddLevel(800,0);
    AddScore(800,20);
    AddChart(875,0,100,100,0*16,180*16/3,Qt::green);
    AddChart(875,0,100,100,60*16,180*16/3,Qt::yellow);
    AddChart(875,0,100,100,120*16,180*16/3,Qt::red);
    AddNeedle(925,50);
    SetCleanliness(80);
    this->timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(CountDown()));
    timer->start(1000);

    Render();

}
/**
 * @brief Header::SetCleanliness
 * @param val
 *
 * the val is added(or subtracted if negative) from the total cleanliness level
 * if the level is less than 0 or greater than 100, the value is reseted to zero or 100
 */
void Header::SetCleanliness(int val)
{
    if(!this->completed){
        if(this->player->cleanliness + val >= 0 && this->player->cleanliness + val < 100)
        {
            this->player->cleanliness += val;
        }
        else if(this->player->cleanliness + val < 0){
            this->player->cleanliness += 0;
        }
        else if(this->player->cleanliness + val >= 100){
            this->player->cleanliness = 100;

        }
        Render();

        if(this->player->cleanliness == 100){
            this->completed = true;
            ((game1scene*)this->scene())->WonGame();
        }
    }

}
/**
 * @brief Header::SetImmunity
 * @param val
 *
 * this sets the immunity by adding(or subtracting) the value of val from the current immmunity level
 *
 */
void Header::SetImmunity(int val)
{
    if(!this->completed){
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
}
/**
 * @brief Header::AddCleanlMeter
 * @param x
 * @param y
 *
 * adds the cleanliness meter to the scene,
 * the position of the meter is set by the x and y coordinates
 */
void Header::AddCleanlMeter(int x, int y)
{
    QGraphicsTextItem* cleanlinessLabel = new QGraphicsTextItem();
    cleanlinessLabel->setPlainText(QString("Cleanliness"));
    cleanlinessLabel->setPos(x,y);
    this->addToGroup(cleanlinessLabel);
    this->cleanlinessMeter = new CleanlinessMeter();
    cleanlinessMeter->setPos(x+90,y);
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

void Header::AddHearts(int x, int y){
    for(int i= 0; i<this->player->lives;i++){
        this->hearts[i] = new QGraphicsPixmapItem(QPixmap("../Project435/images/heart.png").scaledToHeight(50));
        this->hearts[i]->setPos(x-i*50,y);
        this->addToGroup(this->hearts[i]);
    }
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

    int immunity=0;
    if(player->followme==0)
    immunity=this->player->immunity;

    int x2 = this->needle->line().x1() - 30*cos(immunity*M_PI/100.0) ;
    int y2 = this->needle->line().y1() - 30*sin(immunity*M_PI/100.0) ;

    this->needle->setLine(this->needle->line().x1(),this->needle->line().y1(),x2,y2);

}

void Header::RemoveLife(){
    if(!this->completed){
        if(this->player->lives>0){
            this->scene()->removeItem(this->hearts[--this->player->lives]);
            delete this->hearts[this->player->lives];
        }else{
            ((game1scene*)this->scene())->GameOver();
        }
    }
}

void Header::CountDown(){
    if(!this->completed){
        if(this->time>0){
            this->time--;
        }
        Render();
        if(this->time<=0){
    //todo game lost

        }
    }
}


