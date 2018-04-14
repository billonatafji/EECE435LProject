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
    /// setting attributes
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

    ///starting timer and connecting it
    QTimer *timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(20);

}
/**
 * @brief bacteria::update updated the position of the bacteria.
 * It also checks if theres is a collision with any object and checks its type.
 * additionally, it updates the metrics if there is a collision with the player (spongebob)
 */
void bacteria::update()
{
    ///checks if the item is at the boundary of the screen to remove it
    if (this->pos().x()<0 || this->pos().x()>1000)
    {
        this->scene()->removeItem(this);
        this->header->currentBacteriaCountInScene-=strength;
        delete this;
        return;
    }
    /// checks if there is a collision
    if(!this->scene()->collidingItems(this).isEmpty())
    {
        QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
        foreach(QGraphicsItem * i , collidelist)
        {
            ///checks if the collision is with the player
            SpongeBob * item= dynamic_cast<SpongeBob *>(i);
            if (item)
            {
                int playerstrength=(item->immunity/33)+1;

                if((playerstrength-this->strength)<0 || item->followme==1)///<checking if the player isnt strong enough to kill the bacteria, if true, he should lose a life.
                {

                    ///update lives, deletes item,updates cleanliness, and reset stats
                    this->scene()->removeItem(this);
                    this->header->currentBacteriaCountInScene-=strength;
                    this->header->SetCleanliness(+this->strength);
                    this->header->RemoveLife();
                    delete this;

                }

                else///< player is strong enough to kill  the  bacteria
                {
                     ///deletes item,updates cleanliness, and updates stats
                    this->header->player->score+=strength*2*(this->header->player->immunity/33);
                    this->header->currentBacteriaCountInScene-=strength;
                    this->header->SetCleanliness(+this->strength);
                    this->scene()->removeItem(this);
                    delete this;
                }


            }
        }

    }

    /** \brief updating item position
      * if the player has the followme tag toggled on, this means that the bacteria should follow him.
      * an algorithm is used to calculate the speed and direction at which the item should move to follow the palyer.
      *
      * else, the bacteria moves in a wave motion along a fixed center line form the left to the right or the opposite based on its direction.
      *
      */
    if( this->header->player->followme==true)
    {
        /// algorithm to follow the plater
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

/// destructor
bacteria::~bacteria(){
}

