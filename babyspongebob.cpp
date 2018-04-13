#include "babyspongebob.h"
#include "grabbable.h"
#include <QGraphicsScene>

BabySpongeBob::BabySpongeBob(int healthyItemsFed, QObject *parent) : QObject(parent)
{
    this->setPixmap(QPixmap(":/Project435/images/baby.png").scaledToHeight(80));
    this->timer = new QTimer();
    this->healthyItemsFed = healthyItemsFed;

    connect(this->timer,SIGNAL(timeout()),this,SLOT(update()));

    this->timer->start(100);
}

void BabySpongeBob::update(){
    if(this->scene()){
        QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
        foreach(QGraphicsItem * i , collidelist)
        {
            if (Grabbable* item = dynamic_cast<Grabbable *>(i) )
            {
                item->reachedBaby();
            }
        }
    }

}
