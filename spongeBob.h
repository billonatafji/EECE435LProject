#ifndef SPONGEBOB_H
#define SPONGEBOB_H

#include <QObject>
#include <QGraphicsRectItem>
#include<QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include "huItem.h"

/**
*\spongeBob.h
*\brief spongeBob class
*
* This creates an instance of the bear.
*/
class spongeBob : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit spongeBob(QObject *parent = nullptr);///< constructor
    bool followme;
    QTimer *followTimer; ///< timer attribute that specifies the timer

    /**
*\brief Detects key strokes pressed
*\param *event first argument, keystroke event
*/
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    // bool eventFilter(QObject * obj, QEvent * event);
signals:

public slots:
    void toggleFollow();
};

#endif // spongeBob_H
