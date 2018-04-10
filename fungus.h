
#ifndef FUNGUS_H
#define FUNGUS_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "header.h"

/**
*\fungus.h
*\brief fungus class
*
* A fungus is an element on screen that moves periodically following spongebob.*/
class fungus : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit fungus(Header* header,QString name = "", QObject *parent= nullptr);
    QTimer *timer; ///< timer attribute that specifies the timer
    int Xvelocity;///< y velocity of fungus
    int Yvelocity;///< x velocity of fungus
    Header* header;///< pointer to header
    int timetolive;///< specifies time left to die
    QString game;


    ~fungus();

signals:

public slots:
    void update(); ///< update the location on the screen and detects collisions
};

#endif // FUNGUS_H
