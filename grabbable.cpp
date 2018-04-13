#include "grabbable.h"
#include "huItem.h"
#include "bomb.h"
#include "laser.h"

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
                    this->header->SetImmunity(+1);
                    this->header->SetTime(+10);
                }
                else
                {
                    this->header->SetImmunity(-1);
                    this->header->SetTime(-10);
                }

                delete this;
            }
        }
    }
    this-> setPos(this->x(), this->y()+10);
}

void Grabbable::wasShot(Weapon* by){

    if(dynamic_cast<huItem*>(this)){

        if(dynamic_cast<Bomb*>(by)){
            this->strength = 0;
        }
        else{
            this->strength -= by->strength;
        }

        if (((huItem*)this)->type==0 )
        {
            if(this->strength <= 0){
                this->header->SetScore(+3*this->header->difficulty);
                delete this;
            }
        }
        else
        {
            this->header->SetScore(-3* this->header->difficulty);
            delete this;
        }
    }
}


void Grabbable::reachedBaby(){

    if(dynamic_cast<huItem*>(this)){

        if (((huItem*)this)->type==0)
        {
            this->header->RemoveLife();
        }
        else
        {
            this->header->SetCleanliness(15/this->header->difficulty);
        }

    }


    delete this;
}
