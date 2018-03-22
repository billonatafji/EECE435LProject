/**
* \file huItem.cpp
* \brief huItem class definition
*
* a huItem is an object in the game that gets eaten by the bear when they collide
*\author Abdel Jawad Alami
*\date 22-2-2018
*/
#include "huItem.h"
#include "stdlib.h"

huItem::huItem(Header* header, QObject *parent) : QObject(parent)
{
    this->header = header;
    QTimer *timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(100);

}

void huItem::update()
{

    this-> setPos(this->x(), this->y()+10);

    if (this->pos().y()>500)
    {
        this->scene()->removeItem(this);
        delete this;
    }


    else if(!this->scene()->collidingItems(this).isEmpty())
    {
        {       QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
            foreach(QGraphicsItem * i , collidelist)
            {
                SpongeBob * item= dynamic_cast<SpongeBob *>(i);
                if (item)
                {
                    this->scene()->removeItem(this);
                    this->header->SetCleanliness(+1);
                    delete this;
                }
            }
        }
    }

}
