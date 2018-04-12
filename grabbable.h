#ifndef GRABBABLE_H
#define GRABBABLE_H

#include <QGraphicsPixmapItem>
#include "header.h"

class Grabbable :  public QGraphicsPixmapItem
{
public:
    Grabbable();

    Header* header;///< pointer to the header


    bool grabbed;

    void wasShot();

    void reachedBaby();

};

#endif // GRABBABLE_H
