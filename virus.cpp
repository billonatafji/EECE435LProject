/**
* \file virus.cpp
* \brief virus class definition
*
* a virus is an object in the game that gets eaten by the bear when they collide
*\author Abdel Jawad Alami
*\date 22-2-2018
*/
#include "virus.h"
#include "stdlib.h"

virus::virus( int direction, int directionY, int Xvelocity, int Yvelocity, int foobar, int centerline, spongeBob* player, QObject *parent) : QObject(parent)
{
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

void virus::update()
{
    this-> setPos(this->x()+ direction * Xvelocity, this->y()+ directionY *Yvelocity);

    if (y() < centerline-foobar)
        directionY=1;
    else if (y() >centerline+foobar)
        directionY=-1;
    if (this->pos().x()<0 ||this->pos().x()>1000 )
    {
        this->scene()->removeItem(this);
        delete this;
    }

    else if(!this->scene()->collidingItems(this).isEmpty())
    {
        {
            QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
            foreach(QGraphicsItem * i , collidelist)
            {
                spongeBob * item= dynamic_cast<spongeBob *>(i);
                if (item)
                {
                    item->followme=true;
                    item->followTimer->start(1000);
                    this->scene()->removeItem(this);
                    delete this;
                }
            }
        }
    }
}

