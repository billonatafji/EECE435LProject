/**
* \file hook.cpp
* \brief hook class definition
*
* the hookis a type of weapons by which the player grabs items
*
*\author Bilal Natafgi
*\date 13-4-2018
*/
#include "hook.h"
#include <QPen>
#include "spongeBob.h"
#include <QGraphicsScene>
#include "bacteria.h"
#include "huItem.h"
#include "virus.h"
#include "fungus.h"
#include <QPointer>
#include "grabbable.h"

/**
 * constructor
 * @brief Hook::Hook
 * @param strength used to specify the speed of movement of the hook. as the player gets stronger, the hook is faster
 */
Hook::Hook(int strength)
{
    /// initializing
    this->strength = strength;
    this->name = "hook";
    this->throwTimer = new QTimer();
    this->thrown = false;
    this->grabbingItem = false;
    this->grabbedItem = NULL;

    /// drawing the rope
    QPen pen(Qt::black);
    pen.setWidth(3);
    this->rope = new QGraphicsLineItem(this->x()+15,this->y()+70,this->x()+15,this->y()+70);
    this->rope->setPen(pen);
    /// drawing the head of the hook
    this->head = new QGraphicsPixmapItem(QPixmap(":/Project435/images/hook.png").scaledToHeight(40));
    this->head->setPos(this->rope->line().p2().x()-10,this->rope->line().p2().y());

    connect(this->throwTimer,SIGNAL(timeout()),this,SLOT(update()));///< connecting the timer to an update function that updates the length of the hook

    this->addToGroup(this->rope);
    this->addToGroup(this->head);

    this->ready = true;
}

/**
 * @brief Hook::update
 *  the update function updates the length of the rope of the hook for a better graphical experience
 */
void Hook::update(){
    this->rope->setLine(this->rope->line().x1(),this->rope->line().y1(),this->rope->line().x2(),this->rope->line().y2() + (this->thrown ? +2 : -2));///< adding length to the rope
    this->head->setPos(this->rope->line().p2().x()-10,this->rope->line().p2().y());///< updating the position of the head
    /// if the rope has reached its minimum length
    if(this->rope->line().p1() == this->rope->line().p2()){
        this->throwTimer->stop();
        this->grabbingItem = false;
    }
    /// if the rope has reached its maximum length
    if(abs(this->rope->line().p2().y() - this->rope->line().p1().y()) > 200){
        this->thrown = false;
    }
    /// if it hasnt caught any item yet
    if(!this->grabbingItem){
        /// checking for collisions
        QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this->head);
        foreach(QGraphicsItem * i , collidelist)
        {   /// checking if the collision is with a grabbable item
            if (Grabbable* item = dynamic_cast<Grabbable *>(i) )
            {
                /// updating attributes
                item->grabbed = true;
                item->setParentItem(this);
                item->setPos(this->head->pos());
                this->grabbingItem = true;
                this->grabbedItem = item;
                this->thrown = false;

            }
        }
    }
    /// in case it caught an item
    if(this->grabbedItem){
            this->grabbedItem->setPos(this->head->pos());///< positioning the item on the head of the hook
            ((Grabbable*)this->grabbedItem)->wasGrabbed();
    }
}
