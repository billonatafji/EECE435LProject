#ifndef hUITEM_H
#define hUITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "header.h"
#include "grabbable.h"
/**
*\huItem.h
*\brief huItem class
*
* A huItems is an element on screen that moves periodically in a predefined direction.*/
class huItem : public QObject, public Grabbable
{
    Q_OBJECT
public:
    explicit huItem(bool type,Header* header, QString game = "", QObject *parent = nullptr, int strength = 0);
    QTimer *timer; ///< timer attribute that specifies the timer
    bool type;
    QString game;


    ~huItem();

signals:

public slots:
    void update(); ///< update the huItemss location on the screen
};

#endif // HUITEM_H
