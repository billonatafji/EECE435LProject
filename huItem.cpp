/**
* \file huItem.cpp
* \brief huItem class definition
*
* a huItem is an object in the game that gets eaten by the spongebob when they collide, or by baby spongebob
*\author Abdel Jawad Alami
*\date 22-2-2018
*/
#include "huItem.h"
#include "stdlib.h"
#include "game1.h"
#include "game2.h"
#include <QtMath>
#include <QtMath>


huItem::huItem(bool type,Header *header, QString game, QObject *parent, int strength, int interval) : QObject(parent)
{
    this->grabbed = false;
    this->header = header;
    this->type = type;
    this->game = game;
    this->strength = strength;
    this->interval = interval;
    QTimer *timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(this->interval);

}

/**
 * @brief huItem::update
 *
 * constantly updates the movement of the item in a downwards motion for game 1, and in an ellipse motion for game 2.
 * for game 1:
 * If the item collides with spongebob, his health is updated and the item is removed from the scene.
 * If it collides with other items, it is not affected.
 * additionally, when the item reaches the boundary of the scene, it is deleted.
 *
 * for game 2:
 * the item can be hooked or fired.
 * if the item reaches the baby, based on its type, it might affect the babies health positivly or negatively.
 *
 */
void huItem::update()
{
    /// game 1
    if(this->game == Game1::name){
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
                        {
                            this->header->SetImmunity(+6/this->header->difficulty);
                            this->header->SetTime(+10);
                        }

                        else
                        {
                            this->header->SetImmunity(-6/this->header->difficulty);
                            this->header->SetTime(-10);
                        }

                        delete this;
                    }
                }


            }
        }
        this-> setPos(this->x(), this->y()+1);

    }
    /// game 2
    else if(this->game == Game2::name){
        /// item is not grabbed yet
        if(!this->grabbed){
        ///moves along a straigth downwards path first
            if(this->x() >= 710){
                int y = this->y();
                this->setPos(this->x(), this->y()-2);
            }
            /// then through an ellipse
            else if(this->y() > 385){
                int A = 265;
                int B = 225;
                int newX = this->x()+1;
                qreal newY = sqrt(pow(B,2)*(1-pow(newX-470,2)/pow(A,2))) + 300;
                this->setPos(newX, newY);
            }
            /// then through a straight upwards path
            else {
                this->setPos(this->x(), this->y()+2);
            }
            /// removed from the scene if it has exceeded the defined path
            if (this->pos().y()<30)
            {
                this->scene()->removeItem(this);
                delete this;
                return;
            }
        }

    }

}
/// destructor
huItem::~huItem(){
}
