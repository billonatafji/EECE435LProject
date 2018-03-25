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
    explicit bacteria(int strength,int direction,int directionY, double Xvelocity, double Yvelocity, int deviationLimit, int centerline, Header* header = NULL, QObject *parent= nullptr);


    QTimer *timer; ///< timer attribute that specifies the timer
    int strength;
    int direction; ///< direction attribute that specifies the direction of movement of the bacteria
    int directionY;///<  attribute that specifies the Y direction of movement of the virus
    int Xvelocity;///<  attribute that specifies the X velocity of the virus
    int Yvelocity;///<  attribute that specifies the X velocity of the virus
    int deviationLimit;///< specifies maximum deviation from center line
    int centerline;///< specifies the center of propagation of the virus
    Header* header;///< pointer to the header

    ~bacteria();

signals:

public slots:
    void update(); ///< update the location on the screen and detects collisions
};

#endif // BACTERIA_H
