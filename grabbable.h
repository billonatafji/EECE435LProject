#ifndef GRABBABLE_H
#define GRABBABLE_H

#include <QGraphicsPixmapItem>

class Grabbable :  public QGraphicsPixmapItem
{
public:
    Grabbable();

    bool grabbed;

};

#endif // GRABBABLE_H
