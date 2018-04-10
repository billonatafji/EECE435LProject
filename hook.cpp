#include "hook.h"
#include <QPen>

Hook::Hook()
{
    this->throwTimer = new QTimer();
    this->rope = new QGraphicsLineItem(this->x()+15,this->y()+70,this->x()+15,this->y()+70);
    QPen pen(Qt::black);
    pen.setWidth(3);
    this->rope->setPen(pen);

    this->head = new QGraphicsPixmapItem(QPixmap("../Project435/images/hook.png").scaledToHeight(40));
    this->head->setPos(this->rope->line().p2().x()-10,this->rope->line().p2().y());

    connect(this->throwTimer,SIGNAL(timeout()),this,SLOT(update()));

    this->addToGroup(this->rope);
    this->addToGroup(this->head);


}

void Weapon::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_X){
        this->throwTimer->start(10);
    }else if(event->key() == Qt::Key_Z){

    }
}

void Weapon::update(){
    this->rope->setLine(this->rope->line().x1(),this->rope->line().y1(),this->rope->line().x2(),this->rope->line().y2()+2);
    this->head->setPos(this->rope->line().p2().x()-10,this->rope->line().p2().y());
}
