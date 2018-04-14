/**
* \file babyspongebob.cpp
* \brief BabySpongeBob class definition
*
* a BabySpongeBob is an object in the game that resides on the side of the scene, and should be fed healthy items to win the game
*\author Bilal Natafgi
*\date 10-4-2018
*/
#include "babyspongebob.h"
#include "grabbable.h"
#include <QGraphicsScene>

BabySpongeBob::BabySpongeBob(int healthyItemsFed, QObject *parent) : QObject(parent)
{
    this->setPixmap(QPixmap(":/Project435/images/baby.png").scaledToHeight(80));///< setting picture of baby
    this->timer = new QTimer();///< starting timer
    this->healthyItemsFed = healthyItemsFed;///< setting number of healthy items already fed (in case of pause)

    connect(this->timer,SIGNAL(timeout()),this,SLOT(update()));

    this->timer->start(100); ///< timer for update
}
/**
 * @brief BabySpongeBob::update, updates the game metrics in case an item reaches the baby
 *
 */
void BabySpongeBob::update(){
    if(this->scene()){
        QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
        foreach(QGraphicsItem * i , collidelist)
        {
            /// if the item is of type grabbable, the function reachedBaby is called to update the metrics
            if (Grabbable* item = dynamic_cast<Grabbable *>(i) )
            {
                item->reachedBaby();
            }
        }
    }

}
