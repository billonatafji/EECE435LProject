#ifndef SPONGEBOB_H
#define SPONGEBOB_H

#include <QObject>
#include <QGraphicsRectItem>
#include<QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>

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
    explicit SpongeBob(int cleanliness, int immunity, int lives, int score,QObject *parent = nullptr);///< constructor
    bool followme;///< followme attribute that specifies if the bacteria should follow spongebob or not
    QTimer *followTimer; ///< timer attribute that specifies the timer
    int cleanliness;
    int immunity;
    int lives;
    int score;
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
    void toggleFollow();
};

#endif // spongeBob_H
