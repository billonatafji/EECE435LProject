/**
* \file fungus.cpp
* \brief bacteria class definition
*
* a fungus is an object in the game that if eaten by the spongebob, spongebob would loose a life, total strength, and aquariom cleanlines would decrease by half
*\author Abdel Jawad Alami
*\date 25-3-2018
*/
#include "fungus.h"
#include "stdlib.h"
#include "game1.h"
#include "game2.h"
#include <QtMath>

/**
 * @brief fungus::fungus
 * @param header
 * @param parent
 *
 * constructor of a fungus, creates an instance and provides is with a velocity, time to live, and a pointer to the header
 *
 */
fungus::fungus(Header* header,QString game, QObject *parent) : QObject(parent)
{
    this->grabbed = false;
    this->Xvelocity = 2;
    this->Yvelocity=2;
    this->header = header;
    this->timetolive=this->header->time-4;
    this->game = game;
    QTimer *timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(20);

}
/**
 * @brief fungus::update
 *
 * updates the position, detects collision, and in case of collision with the player, it penalises him
 *it also deletes the fungus if its time is over
 */
void fungus::update()
{
    if(this->game == Game1::name){

        if (this->pos().x()<0 || this->pos().x()>1000 || this->header->time < this->timetolive)
        {
            this->scene()->removeItem(this);
            delete this;
            return;
        }
        if(!this->scene()->collidingItems(this).isEmpty())
        {   ///
            /// \brief collidelist
            ///this creates a list of all colliding items.
            /// it then dynamically casts each detected item to an instance of spongebob
            /// if any item returns true which means that it exists, this means that a collision with spongebob has occured
            /// this leads to some procedures
            QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
            foreach(QGraphicsItem * i , collidelist)
            {
                SpongeBob * item= dynamic_cast<SpongeBob *>(i);
                if (item)
                {
                    this->header->SetImmunity(-item->immunity/2);/// immunity is halved
                    this->header->SetCleanliness(-item->cleanliness/2);/// cleanliness is halved
                    item->followme=1;/// instructs batceria to follow him
                    item->followTimer->start(5000);/// timer for following starts

                    this->scene()->removeItem(this);
                    delete this;
                }
            }




        }
        //////////////////////////////////////////////////////
        /// this is an algorithm to detect the position of spongebob and follow him
        int playerx= this->header->player->x();
        int playery= this->header->player->y();
        double diry = playery - y();
        double dirx= playerx - x();
        double hyp = sqrt(dirx*dirx + diry*diry);
        dirx /= hyp;
        diry /= hyp;
        this-> setPos(this->x()+ dirx * Xvelocity, this->y()+ diry *Yvelocity);
        /////////////////////////////////////////////////////////

    }

}

fungus::~fungus(){
}

