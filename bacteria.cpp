/**
* \file bacteria.cpp
* \brief bacteria class definition
*
* a bacteria is an object in the game that gets eaten by the bear when they collide
*\author Abdel Jawad Alami
*\date 22-2-2018
*/
#include "bacteria.h"
#include "stdlib.h"
#include "game1.h"
#include "game2.h"
#include "hook.h"
bacteria::bacteria(int strength, int direction, int directionY, double Xvelocity, double Yvelocity, int upperlimit, int centerline, Header* header,QString game,QObject *parent) : QObject(parent)
{
    this->strength=strength;
    this->direction=direction;
    this->directionY=directionY;
    this->Xvelocity=Xvelocity;
    this->Yvelocity=Yvelocity;
    this->upperlimit=upperlimit;
    this->centerline=centerline;
    this->header = header;
    this->game = game;
    this->grabbed = false;
    QTimer *timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(20);

}

void bacteria::update()
{
    if(this->game == Game1::name){

        if (this->pos().x()<0 || this->pos().x()>1000)
        {
            this->scene()->removeItem(this);
            this->header->currentBacteriaCountInScene-=strength;
            delete this;
            return;
        }
        if(!this->scene()->collidingItems(this).isEmpty())
        {
            {       QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
                foreach(QGraphicsItem * i , collidelist)
                {
                    SpongeBob * item= dynamic_cast<SpongeBob *>(i);
                    if (item)
                    {
                        int playerstrength=(item->immunity/33)+1;

                        if((playerstrength-this->strength)<0 || item->followme==1)//player isnt strong enough to kill the bacteria, he should lose a life.
                        {
                            //todo
                            //update life and reset stats
                            this->scene()->removeItem(this);
                            this->header->currentBacteriaCountInScene-=strength;
                            this->header->SetCleanliness(+this->strength);
                            this->header->RemoveLife();
                            if (item->lives==0)
                            {

                            }
                            delete this;

                        }
                        else
                        {
                            this->header->player->score+=strength*2*(this->header->player->immunity/33);
                            this->header->currentBacteriaCountInScene-=strength;
                            this->header->SetCleanliness(+this->strength);
                            this->scene()->removeItem(this);
                            delete this;
                        }


                    }
                }


            }

        }

        if( this->header->player->followme==true)
        {
            int playerx= this->header->player->x();
            int playery= this->header->player->y();
            double diry = playery - y();
            double dirx= playerx - x();
            double hyp = sqrt(dirx*dirx + diry*diry);
            dirx /= hyp;
            diry /= hyp;
            centerline=this->y();
            this-> setPos(this->x()+ dirx * Xvelocity, this->y()+ diry *Yvelocity);
        }
        else
        {
            this-> setPos(this->x()+direction * Xvelocity, this->y()+ directionY *Yvelocity);

            if (y() < centerline-upperlimit)
                directionY=1;
            else if (y() >centerline+upperlimit)
                directionY=-1;
        }
    }
}

bacteria::~bacteria(){
}

