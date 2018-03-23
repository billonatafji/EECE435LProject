/**
* \file virus.cpp
* \brief virus class definition
*
* a virus is an object in the game that if eaten by spongebob, makes the bacteria follow him.
*\author Abdel Jawad Alami
*\date 18-3-2018
*/
#include "virus.h"
#include "stdlib.h"
/**
 * @brief virus::virus
 * @param direction
 * @param directionY
 * @param Xvelocity
 * @param Yvelocity
 * @param foobar
 * @param centerline
 * @param player
 * @param parent
 *
 * constructor
 */
virus::virus( int direction, int directionY, int Xvelocity, int Yvelocity, int foobar, int centerline,  Header* header,QObject *parent) : QObject(parent)
{
    this->direction=direction;
    this->directionY=directionY;
    this->Xvelocity=Xvelocity;
    this->Yvelocity=Yvelocity;
    this->foobar=foobar;
    this->centerline=centerline;
    this->header = header;
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
        this->header->SetCleanliness(+5);
    }

    else if(!this->scene()->collidingItems(this).isEmpty())
    {
        {
            QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
            foreach(QGraphicsItem * i , collidelist)
            {
                SpongeBob * item= dynamic_cast<SpongeBob *>(i);
                if (item)
                {
                    item->followme=true;
                    item->followTimer->start(5000);
                    this->scene()->removeItem(this);
                    this->header->SetCleanliness(+5);
                    delete this;
                }
            }
        }
    }
}

