#ifndef BACTERIA_H
#define BACTERIA_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "header.h"

/**
*\bacteria.h
*\brief bacteria class
*
* A bacteria is an element on screen that moves periodically in a predefined direction.*/
class bacteria : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit bacteria(int strength,int direction,int directionY, int Xvelocity, int Yvelocity, int upperlimit, int centerline, Header* header = NULL, QObject *parent= nullptr);


    QTimer *timer; ///< timer attribute that specifies the timer
    int strength;
    int direction; ///< direction attribute that specifies the direction of movement of the bacteria
    int directionY;
    int Xvelocity;
    int Yvelocity;
    int upperlimit;
    int centerline;
    Header *header;

    ~bacteria();

signals:

public slots:
    void update(); ///< update the location on the screen
};

#endif // BACTERIA_H
