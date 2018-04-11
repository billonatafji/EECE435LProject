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


Hook::Hook()
{
    this->throwTimer = new QTimer();
    this->thrown = false;
    this->grabbingItem = false;
    this->grabbedItem = NULL;
    this->rope = new QGraphicsLineItem(this->x()+15,this->y()+70,this->x()+15,this->y()+70);
    QPen pen(Qt::black);
    pen.setWidth(3);
    this->rope->setPen(pen);

    this->head = new QGraphicsPixmapItem(QPixmap(":/Project435/images/hook.png").scaledToHeight(40));
    this->head->setPos(this->rope->line().p2().x()-10,this->rope->line().p2().y());

    connect(this->throwTimer,SIGNAL(timeout()),this,SLOT(update()));

    this->addToGroup(this->rope);
    this->addToGroup(this->head);

    this->ready = true;
}


void Hook::update(){
    this->rope->setLine(this->rope->line().x1(),this->rope->line().y1(),this->rope->line().x2(),this->rope->line().y2() + (this->thrown ? +2 : -2));
    this->head->setPos(this->rope->line().p2().x()-10,this->rope->line().p2().y());
    if(this->rope->line().p1() == this->rope->line().p2()){
        this->throwTimer->stop();
        this->grabbingItem = false;
    }
    if(abs(this->rope->line().p2().y() - this->rope->line().p1().y()) > 200){
        this->thrown = false;
    }
    if(!this->grabbingItem){
        QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this->head);
        foreach(QGraphicsItem * i , collidelist)
        {
            if (Grabbable* item = dynamic_cast<Grabbable *>(i) )
            {
                item->grabbed = true;
                item->setParentItem(this);
                item->setPos(this->head->pos());
                this->grabbingItem = true;
                this->grabbedItem = item;
                this->thrown = false;

            }
        }
    }
    if(this->grabbedItem != nullptr){
            this->grabbedItem->setPos(this->head->pos());
    }



}
