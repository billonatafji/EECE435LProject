/**
* \file Laser.cpp
* \brief Laser class definition
*
* a Laser is an object in the game that is fired on the huitems
*\author Bilal natafgi
*\date 12-4-2018
*/

#include "laser.h"
#include <QPen>
#include "spongeBob.h"
#include <QGraphicsScene>
#include "bacteria.h"
#include "huItem.h"
#include "virus.h"
#include "fungus.h"
#include <QPointer>
#include "grabbable.h"
///constructor
Laser::Laser(int strength)
{
    this->strength = strength;
    this->name = "laser";
    this->throwTimer = new QTimer();
    this->thrown = false;
    this->grabbingItem = false;
    this->grabbedItem = NULL;
    this->head = new QGraphicsPixmapItem(QPixmap(":/Project435/images/laser.png").scaledToHeight(60));
    this->head->setPos(this->x()+10,this->y()+60);

    this->head->setRotation(50);

    this->rope = new QGraphicsLineItem();
    QPen pen(Qt::red);
    pen.setWidth(3);
    this->rope->setPen(pen);
    this->rope->setParentItem(this->head);
    this->rope->setPos(this->head->pos().x(),this->head->pos().y());


    connect(this->throwTimer,SIGNAL(timeout()),this,SLOT(update()));

    this->addToGroup(this->rope);
    this->addToGroup(this->head);
    this->ready = true;

}
/**
 * @brief Laser::update
 * this function updates the length of the laser while shooting for a better user experience.
 * It also checks for collisions and acts accordingly by calling other functions.
 */
void Laser::update(){
    this->rope->setLine(this->rope->line().x1(),this->rope->line().y1(),this->rope->line().x2(),this->rope->line().y2() + (this->thrown ? +4 : -4));
    if(this->rope->line().p1() == this->rope->line().p2()){
        this->throwTimer->stop();
    }
    if(abs(this->rope->line().p2().y() - this->rope->line().p1().y()) > 100 + 50*this->strength){
        this->thrown = false;
    }
    QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this->rope);
    foreach(QGraphicsItem * i , collidelist)
    {
        /// check if there is a collison with a grabbable item (huitem)
        if (Grabbable* item = dynamic_cast<Grabbable *>(i) )
        {

            this->throwTimer->stop();///< stop elongating the laser
            this->rope->setLine(QLineF( this->rope->line().p1(),this->rope->line().p1()));
            this->thrown = false;
            item->wasShot(this);///< calling the wasshot function for updating metrics and removing the item from the scene
        }
    }
}

