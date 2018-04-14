/**
* \file bomb.cpp
* \brief Bomb class definition
*
* a Bomb is an object in the game that can be shot if a specific score  is reached. it cleares the area it hits
*\author Bilal Natafgi
*\date 12-4-2018
*/
#include "bomb.h"
#include <QPen>
#include "spongeBob.h"
#include <game2scene.h>
#include "huItem.h"
#include <QPointer>
#include "grabbable.h"

/**
 * @brief Bomb::Bomb constructor
 * @param strength the strength of the bomb ( how fast it goes)
 *
 */
Bomb::Bomb(int strength)
{
    /// setting attributes
    this->strength = strength;
    this->name = "bomb";
    this->ready = false;
    this->step = 0;
    this->prepareTimer = new QTimer();
    this->grabbingItem = false;
    this->throwTimer = new QTimer();
    this->head = new QGraphicsPixmapItem();
    this->head->setPos(this->x()-15,this->y()+70);
    connect(this->prepareTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(this->throwTimer,SIGNAL(timeout()),this,SLOT(update()));
    this->addToGroup(this->head);

    this->prepareTimer->start(500*(4-this->strength));
}
/**
 * @brief Bomb::update
 *         updates the position of the bomb and checks for collision
 */
void Bomb::update(){

    /// if not ready to throw the bomb, setting it.
    if(!this->ready){
        this->prepareTimer->stop();
        this->head->setPixmap(QPixmap(":/Project435/images/bomb.png").scaledToHeight(60));
        this->ready = true;
    }else{

        this->step++; ///< adding number of steps passed.
        if(this->thrown){
            this->head->setPos(this->head->pos().x(), this->head->pos().y()+1);
        }
        QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this->head);
        foreach(QGraphicsItem * i , collidelist)
        {
            if (Grabbable* item = dynamic_cast<Grabbable *>(i))
            {
                /// there is a collision with an item that is grabbable,there are items to delete.
                if(!(dynamic_cast<Weapon*>(item->header->player->weapon) && ((Weapon*)item->header->player->weapon)->grabbedItem == item)){
                    this->head->setPixmap(QPixmap(":/Project435/images/explosion.png").scaledToHeight(170));
                    if(!this->grabbingItem){
                        this->head->setPos(this->head->pos().x()-50, this->head->pos().y()-30);
                    }
                    this->grabbingItem = true;
                    item->wasShot(this);
                    this->thrown = false;
                    this->step -=100*this->strength;
                }

            }
        }
        /// number of teps exceeds limit. bomb is deleted
        if(this->step > 350){
            delete this;
        }
    }


}
