#ifndef SPONGEBOB_H
#define SPONGEBOB_H

#include <QObject>
#include <QGraphicsRectItem>
#include<QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include "weapon.h"

/**
*\spongeBob.h
*\brief spongeBob class
*
* This creates an instance of the spongebob.
*/
class SpongeBob : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SpongeBob(int cleanliness, int immunity, int lives, int score, QPoint pos, QString game,QObject *parent = nullptr);///< constructor
    bool followme;///< followme attribute that specifies if the bacteria should follow spongebob or not
    QTimer *followTimer; ///< timer attribute that specifies the timer
    int cleanliness;     ///< cleanliness of the tank
    int immunity;///< immunity level of spongebob
    int lives;///<number of lives
    int score;///< total score
    QPoint currentPos;///< current position
    Weapon* weapon;
    QString game;
    int translation;


    ~SpongeBob();

    /**
*\brief Detects key strokes pressed
*\param *event first argument, keystroke event
*/
    void keyPressEvent(QKeyEvent *event);
    /**
    *\brief Detects key release events
    *\param *event first argument, key release event
    */
    void keyReleaseEvent(QKeyEvent *event);
    // bool eventFilter(QObject * obj, QEvent * event);
signals:

public slots:
    void toggleFollow();///<change from follow me to dont follow me
};

#endif // spongeBob_H
