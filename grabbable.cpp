#include "grabbable.h"
#include "huItem.h"

Grabbable::Grabbable()
{

}

void Grabbable::wasGrabbed(){
    this->grabbed = true;
    if(!this->scene()->collidingItems(this).isEmpty())
    {
        QList<QGraphicsItem *> collidelist = this->scene()->collidingItems(this);
        foreach(QGraphicsItem * i , collidelist)
        {
            SpongeBob * item= dynamic_cast<SpongeBob *>(i);
            if (item)
            {
                item->weapon->grabbedItem = nullptr;
                this->scene()->removeItem(this);
                if (((huItem*)this)->type==1)
                {
                    this->header->SetImmunity(+6/this->header->difficulty);
                    this->header->SetTime(+10);
                }
                else
                {
                    this->header->SetImmunity(-6/this->header->difficulty);
                    this->header->SetTime(-10);
                }

                delete this;
            }
        }
    }
    this-> setPos(this->x(), this->y()+10);
}

void Grabbable::wasShot(){


    if(dynamic_cast<huItem*>(this)){

        if (((huItem*)this)->type==0)
        {
            this->header->SetScore(+3);
        }
        else
        {
            this->header->SetScore(-3);
        }

    }

    delete this;
}

void Grabbable::reachedBaby(){
    if(dynamic_cast<huItem*>(this)){
        if(dynamic_cast<huItem*>(this)){

            if (((huItem*)this)->type==0)
            {
                this->header->RemoveLife();
            }
            else
            {
                this->header->SetCleanliness(10);
            }

        }
    }

    delete this;
}
