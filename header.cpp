#include "header.h"
#include "user.h"
#include "game1scene.h"
#include "game2scene.h"
#include <QApplication>
#include "game1.h"
#include "game2.h"

Header::Header(SpongeBob* player, int difficulty, QString username, QString game, bool paused, int time)
{
    this->player = player;
    this->difficulty = difficulty;
    this->username = username;
    this->game = game;
    this->paused = paused;
    this->time = time;
    this->currentBacteriaCountInScene=0;

    if(this->game == Game1::name){

        AddCleanlMeter(0,10);
        AddHearts(750,10);
        AddChart(875,0,100,100,0*16,180*16/3,Qt::green);
        AddChart(875,0,100,100,60*16,180*16/3,Qt::yellow);
        AddChart(875,0,100,100,120*16,180*16/3,Qt::red);
        AddNeedle(925,50);

    }else{

        AddChart(40,0,100,100,0*16,180*16/3,Qt::green);
        AddChart(40,0,100,100,60*16,180*16/3,Qt::yellow);
        AddChart(40,0,100,100,120*16,180*16/3,Qt::red);
        AddNeedle(90,50);
        AddBombs(250,10);

        AddHearts(680,10);
        AddCleanlMeter(750,10);
        AddBaby(700,70);

    }

    AddLevel(380,10);
    AddPause(450,0);
    AddTime(452,40);
    AddScore(510,10);

    this->timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(CountDown()));
    timer->start(1000);

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
    if(!this->paused){
        if(this->game == Game1::name){
            if(this->player->cleanliness + val >= 0 && this->player->cleanliness + val < 100)
            {
                this->player->cleanliness += val;
            }
            else if(this->player->cleanliness + val < 0){
                this->player->cleanliness = 0;
            }
            else if(this->player->cleanliness + val >= 100){
                this->player->cleanliness = 100;
            }
            Render();
            if(this->player->cleanliness == 100){
                this->paused = true;
                ((game1scene*)this->scene())->WonGame();

            }
        }else if(this->game == Game2::name){
            if(this->baby->healthyItemsFed + val > 100){
                this->baby->healthyItemsFed = 100;
            }else{
                this->baby->healthyItemsFed += val;

            }
            Render();

            if(this->baby->healthyItemsFed == 100){
                this->paused = true;
                ((Game2Scene*)this->scene())->WonGame();
            }
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
    if(!this->paused){
        if(this->game == Game1::name){
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
        }else if(this->game == Game2::name){
            if(this->player->weapon->strength + val < 0){
                this->player->weapon->strength = 0;
            }else if(this->player->weapon->strength + val > 3){
                this->player->weapon->strength = 3;
            }else{
                this->player->weapon->strength += val;
            }
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
    cleanlinessLabel->setPlainText(QString(this->game == Game1::name ? "Cleanliness" : "Baby's Health"));
    cleanlinessLabel->setPos(x+50,y+30);
    this->addToGroup(cleanlinessLabel);
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

void Header::AddHearts(int x, int y){
    for(int i= 0; i<this->player->lives;i++){
        this->hearts[i] = new QGraphicsPixmapItem(QPixmap(":/Project435/images/heart.png").scaledToHeight(40));
        this->hearts[i]->setPos(x-i*40,y);
        this->addToGroup(this->hearts[i]);
    }
}

void Header::AddBombs(int x, int y){
    for(int i= 0; i<this->player->bombs;i++){
        this->bombs[i] = new QGraphicsPixmapItem(QPixmap(":/Project435/images/bomb.png").scaledToHeight(40));
        this->bombs[i]->setPos(x-i*40,y);
        this->addToGroup(this->bombs[i]);
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

    QGraphicsTextItem* immunityLabel = new QGraphicsTextItem();
    immunityLabel->setPlainText(QString(this->game == Game1::name ? "Immunity Level" : "Weapon Strength"));
    immunityLabel->setPos(x-70, y);
    this->addToGroup(immunityLabel);

}

void Header::AddPause(int x, int y){
    this->pause = new Pause();
    this->pause->setPixmap(QPixmap(":/Project435/images/pause.png").scaledToHeight(40));
    this->pause->setPos(x,y);
    this->addToGroup(this->pause);
}

void Header::AddBaby(int x, int y){
    this->baby = new BabySpongeBob();
    this->baby->setPos(x,y);
    this->baby->setParentItem(this);
    this->addToGroup(this->baby);
}

void Header::Render(){

    this->cleanlinessMeter->ProgressBar->setValue(this->game == Game1::name ? this->player->cleanliness : this->baby->healthyItemsFed);
    this->scoreLabel->setPlainText(QString("Score: ").append(QString::number(this->player->score)));
    this->timeLabel->setPlainText(QString::number(time/60) + QString(":") + QString::number(time%60));

    int immunity= 0;
    if(this->game == Game1::name){
        if(player->followme==0)
            immunity=this->player->immunity;
    }else{
        immunity = this->player->weapon->strength;
    }

    int x2 = this->needle->line().x1() - 30*cos(immunity*M_PI/(this->game == Game1::name ? 100.0 : 3)) ;
    int y2 = this->needle->line().y1() - 30*sin(immunity*M_PI/(this->game == Game1::name ? 100.0 : 3)) ;

    this->needle->setLine(this->needle->line().x1(),this->needle->line().y1(),x2,y2);

}

void Header::RemoveLife(){
    if(!this->paused){
        if(this->player->lives>0){
            this->scene()->removeItem(this->hearts[--this->player->lives]);
            delete this->hearts[this->player->lives];
            this->SetScore(-pow(this->difficulty,2)*5);
        }else{
            if(dynamic_cast<game1scene *>(this->scene())){
                dynamic_cast<game1scene *>(this->scene())->GameOver();
            }else if(dynamic_cast<Game2Scene *>(this->scene())){
                dynamic_cast<Game2Scene *>(this->scene())->GameOver();
            }

        }
    }
}
void Header::RemoveBomb(){
    this->scene()->removeItem(this->bombs[--this->player->bombs]);
    delete this->bombs[this->player->bombs];
}

void Header::CountDown(){
    if(!this->paused){
        if(this->time>0){
            this->time--;        
            Render();
        }
        else{
            if(dynamic_cast<game1scene *>(this->scene())){
                dynamic_cast<game1scene *>(this->scene())->GameOver();
            }else if(dynamic_cast<Game2Scene *>(this->scene())){
                dynamic_cast<Game2Scene *>(this->scene())->GameOver();
            }
        }
    }
}

void Header::SetTime(int val){
    this->time += val;
    Render();
}
void Header::SetScore(int val){
    if(this->player->score + val < 0){
        this->player->score = 0;
    }else{
        this->player->score += val;
    }
    Render();
}


