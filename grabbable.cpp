#include "grabbable.h"
#include "huItem.h"
#include "bomb.h"
#include "laser.h"

Grabbable::Grabbable()
{

}
/**
 * @brief Grabbable::wasGrabbed
 *        this function is excited when an item is hooked
 *
 *
 */
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

        /// if the item collides with a bomb, it loses all of its strength
        if(dynamic_cast<Bomb*>(by)){
            this->strength = 0;
        }

        /// if the item was shot with a laser, its strength decreases by the strength of the laser
        else{
            this->strength -= by->strength;
        }

        /// if this is a healthy item, increase score.
        if (((huItem*)this)->type==0 )
        {
            if(this->strength <= 0){
                this->header->SetScore(+3*this->header->difficulty);
                delete this;
            }
        }
        /// if this is an unhealthy item, decrease score.
        else
        {
            this->header->SetScore(-3* this->header->difficulty);
            delete this;
        }
    }
}

/**
 * @brief Grabbable::reachedBaby
 *        this is a function that is excited when the baby collides with an item.
 */
void Grabbable::reachedBaby(){

    /// checking if the item collided with is an huitem.
    if(dynamic_cast<huItem*>(this)){
        /// if the huitem is an unhealthy item, the player loses a life.
        if (((huItem*)this)->type==0)
        {
            this->header->RemoveLife();
        }

        /// if the huitem is a healthy item, the cleanliness increases.
        else
        {
            this->header->SetCleanliness(15/this->header->difficulty);
        }

    }

    /// removing the item that collided with the baby.
    delete this;
}
