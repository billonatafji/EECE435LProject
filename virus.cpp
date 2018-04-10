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
        this->setPos(this->x()+ direction * Xvelocity, this->y()+ directionY *Yvelocity);

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
                    SpongeBob * item= dynamic_cast<SpongeBob *>(i);
                    if (item)
                    {
                        item->followme=true;
                        item->followTimer->start(5000);
                        this->scene()->removeItem(this);
                        delete this;
                    }
                }
            }
        }
    }
    else if(this->game == Game2::name){

        if (this->grabbed)
        {
            if(!this->scene()->collidingItems(this).isEmpty())
            {
                {
                    QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
                    foreach(QGraphicsItem * i , collidelist)
                    {
                        SpongeBob * item= dynamic_cast<SpongeBob *>(i);
                        if (item)
                        {
                            item->weapon->grabbedItem = nullptr;
                            item->followme=true;
                            item->followTimer->start(5000);
                            this->scene()->removeItem(this);
                            delete this;
                        }
                    }
                }
            }
        }else{

            double A = 300;
            double B = 450;
            qreal newX = this->x()+1;
            qreal newY = sqrt(pow(B,2)*(1-pow(newX-450,2)/pow(A,2))) + 0;
            this->setPos(newX, newY);
            if (this->pos().y()<30)
            {
                this->scene()->removeItem(this);
                delete this;
                return;

            }

        }

    }

}

virus::~virus(){
}

