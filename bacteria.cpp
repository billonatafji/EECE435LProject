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

bacteria::bacteria(int strength, int direction, int directionY, int Xvelocity, int Yvelocity, int foobar, int centerline, spongeBob* player, QObject *parent) : QObject(parent)
{
    this->strength=strength;
    this->direction=direction;
    this->directionY=directionY;
    this->Xvelocity=Xvelocity;
    this->Yvelocity=Yvelocity;
    this->foobar=foobar;
    this->centerline=centerline;
    this->player=player;
    QTimer *timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(20);

}

void bacteria::update()
{
    if (this->pos().x()<0 || this->pos().x()>1000)
    {
        this->scene()->removeItem(this);
        delete this;
        return;
    }
    if(!this->scene()->collidingItems(this).isEmpty())
    {
        {       QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
            foreach(QGraphicsItem * i , collidelist)
            {
                spongeBob * item= dynamic_cast<spongeBob *>(i);
                if (item)
                {
                    this->scene()->removeItem(this);
                    delete this;
                }
            }


        }

    }
    if( player->followme==true)
    {
        int bearx= player->x();
        int beary= player->y();
        double diry = beary - y();
        double dirx= bearx - x();
        double hyp = sqrt(dirx*dirx + diry*diry);
        dirx /= hyp;
        diry /= hyp;
        centerline=this->y();
        this-> setPos(this->x()+ dirx * Xvelocity, this->y()+ diry *Yvelocity);
    }
    else
    {
        this-> setPos(this->x()+direction * Xvelocity, this->y()+ directionY *Yvelocity);

        if (y() < centerline-foobar)
            directionY=1;
        else if (y() >centerline+foobar)
            directionY=-1;
    }

}


