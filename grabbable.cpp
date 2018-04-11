#include "grabbable.h"
#include "bacteria.h"
#include "huItem.h"
#include "virus.h"
#include "fungus.h"

Grabbable::Grabbable()
{

}
void Grabbable::wasShot(){

    if(dynamic_cast<bacteria*>(this)){

    }else if(dynamic_cast<huItem*>(this)){

    }else if(dynamic_cast<virus*>(this)){

    }else if(dynamic_cast<fungus*>(this)){

    }

    delete this;
}

void Grabbable::reachedBaby(){
    if(dynamic_cast<bacteria*>(this)){

    }else if(dynamic_cast<huItem*>(this)){

    }else if(dynamic_cast<virus*>(this)){

    }else if(dynamic_cast<fungus*>(this)){

    }

    delete this;
}
