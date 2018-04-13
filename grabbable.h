#ifndef GRABBABLE_H
#define GRABBABLE_H

#include <QGraphicsPixmapItem>
#include "header.h"
#include "weapon.h"

class Grabbable :  public QGraphicsPixmapItem
{
public:
    Grabbable();

    Header* header;///< pointer to the header
    int strength;
    int interval;
    bool grabbed;

    void wasGrabbed();
    void wasShot(Weapon* by);
    void reachedBaby();

};

#endif // GRABBABLE_H
