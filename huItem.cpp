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

huItem::huItem(bool type,Header *header, QObject *parent) : QObject(parent)
{
    this->header = header;
    this->type = type;
    QTimer *timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(100);

}

/**
 * @brief huItem::update
 *
 * constantly updates the movement of the item in a downwards motion.
 * If the item collides with spongebob, his health is updated and the item is removed from the scene.
 * If it collides with other items, it is not affected.
 * additionally, when the item reaches the boundary of the scene, it is deleted.
 */
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
                    if (this->type==1)
                        this->header->SetImmunity(+6/this->header->difficulty);
                    else
                        this->header->SetImmunity(-6/this->header->difficulty);
                    delete this;
                }
            }


        }



    }

}

huItem::~huItem(){
}
