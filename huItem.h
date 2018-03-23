#ifndef hUITEM_H
#define hUITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "header.h"

/**
*\huItem.h
*\brief huItem class
*
* A huItems is an element on screen that moves periodically in a predefined direction.*/
class huItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit huItem(bool type,Header* header, QObject *parent = nullptr);
    QTimer *timer; ///< timer attribute that specifies the timer
    Header *header;
    bool type;
signals:

public slots:
    void update(); ///< update the huItemss location on the screen
};

#endif // HUITEM_H
