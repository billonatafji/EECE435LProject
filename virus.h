
#ifndef VIRUS_H
#define VIRUS_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "header.h"
#include "grabbable.h"

/**
*\virus.h
*\brief virus class
*
* A virus is an element on screen that moves periodically in a predefined direction.*/
class virus : public QObject, public Grabbable
{
    Q_OBJECT
public:
    explicit virus(int direction,int directionY, int Xvelocity, int Yvelocity, int deviationLimit, int centerline, Header* header, QString game = "", QObject *parent= nullptr);
    QTimer *timer; ///< timer attribute that specifies the timer
    int direction; ///<  attribute that specifies the X direction of movement of the virus
    int directionY;///<  attribute that specifies the Y direction of movement of the virus
    int Xvelocity;///<  attribute that specifies the X velocity of the virus
    int Yvelocity;///<  attribute that specifies the X velocity of the virus
    int deviationLimit;///< specifies maximum deviation from center line
    int centerline;///< specifies the center of propagation of the virus
    Header* header;///< pointer to the header
    int foobar;
    QString game;
    ~virus();

signals:

public slots:
    void update(); ///< update the location on the screen and detects collision
};

#endif // VIRUS_H
