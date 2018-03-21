#ifndef hUITEM_H
#define hUITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include"spongeBob.h"

/**
*\huItem.h
*\brief huItem class
*
* A huItems is an element on screen that moves periodically in a predefined direction.*/
class huItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit huItem( QObject *parent = nullptr);
    QTimer *timer; ///< timer attribute that specifies the timer
signals:

public slots:
    void update(); ///< update the huItemss location on the screen
};

#endif // HUITEM_H
