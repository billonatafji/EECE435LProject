#ifndef VIRUS_H
#define VIRUS_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "spongeBob.h"
#include "header.h"

/**
*\virus.h
*\brief virus class
*
* A virus is an element on screen that moves periodically in a predefined direction.*/
class virus : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit virus(int direction,int directionY, int Xvelocity, int Yvelocity, int foobar, int centerline, Header* header,QObject *parent= nullptr);
    QTimer *timer; ///< timer attribute that specifies the timer
    int direction; ///< direction attribute that specifies the direction of movement of the virus
    int directionY;
    int Xvelocity;
    int Yvelocity;
    int foobar;
    int centerline;
    Header* header;
signals:

public slots:
    void update(); ///< update the location on the screen
};

#endif // VIRUS_H
