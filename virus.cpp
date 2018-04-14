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
#include "game1.h"
#include "game2.h"
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
virus::virus( int direction, int directionY, int Xvelocity, int Yvelocity, int foobar, int centerline,  Header* header, QString game, QObject *parent) : QObject(parent)
{
    this->grabbed = false;
    this->direction=direction;
    this->directionY=directionY;
    this->Xvelocity=Xvelocity;
    this->Yvelocity=Yvelocity;
    this->foobar=foobar;
    this->centerline=centerline;
    this->header = header;
    this->game = game;
    QTimer *timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));/// for periodic update of the position
    timer->start(20);

}

void virus::update()
{
    if(this->game == Game1::name){
        /// wave movement
        this->setPos(this->x()+ direction * Xvelocity, this->y()+ directionY *Yvelocity);

        if (y() < centerline-foobar)
            directionY=1;
        else if (y() >centerline+foobar)
            directionY=-1;
        //// if the virus gets out of the screen
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
                    SpongeBob * item= dynamic_cast<SpongeBob *>(i);
                    if (item)
                    {
                        item->followme=true; ///< toggling the follow me button
                        item->followTimer->start(5000); ///< starting the follow timer
                        this->scene()->removeItem(this);///< removing the virus from the scene
                        delete this;
                    }
                }
            }
        }
    }
}

virus::~virus(){
}

