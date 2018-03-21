/**
* \file spongeBob.cpp
* \brief spongeBob class definition
*
* a spongeBob instance
*\author Abdel Jawad Alami
*\date 22-2-2018
*/

#include "spongeBob.h"

spongeBob::spongeBob(QObject *parent) : QObject(parent)
{
    this->followme=0;
    followTimer= new QTimer();
    connect(followTimer,SIGNAL(timeout()),this,SLOT(toggleFollow()));
    setPixmap((QPixmap("../Project435/images/spongebob.png")).scaled(100,100));

}

/**
 * @brief spongeBob::keyPressEvent
 * @param event
 *
 * the keypress event detects all key strokes on the keyboard.
 * we are only interested in the up,down,left, and right strokes
 * when one of those keys is pressed, the bear moves accoringly when possible
 * if the location of the bear is on the edges of the screen, the position isnt updated if this will result in leaving the screen
 */
QSet<int> pressedKeys;


//void spongeBob:: keyPressEvent(QKeyEvent *event)
//{

//    if ( event->key() == Qt::Key_Left && x()>0)
//    {
//       this->setPos(this->pos().x()-10,this->pos().y());
//    }

//    if ( event->key() == Qt::Key_Right&&x()<900)
//    {
//        this->setPos(this->pos().x()+10,this->pos().y());
//    }

//    if ( event->key() == Qt::Key_Up&&y()>0)
//    {
//        this->setPos(this->pos().x(),this->pos().y()-10);
//    }

//    if ( event->key() == Qt::Key_Down&&y()<400)
//    {
//     this->setPos(this->pos().x(),this->pos().y()+10);
//     }



//    }

void spongeBob::toggleFollow()
{
    if (this->followme==1)
        this->followme=0;

}

void spongeBob::keyPressEvent(QKeyEvent *event)
{

    pressedKeys += ((QKeyEvent*)event)->key();

    if( pressedKeys.contains(Qt::Key_Up) )
    {
        this->setPos(this->pos().x(),this->pos().y()-10);
    }
    if( pressedKeys.contains(Qt::Key_Left) )
    {
        this->setPos(this->pos().x()-10,this->pos().y());
    }
    if( pressedKeys.contains(Qt::Key_Down) )
    {
        this->setPos(this->pos().x(),this->pos().y()+10);
    }
    if( pressedKeys.contains(Qt::Key_Right) )
    {
        this->setPos(this->pos().x()+10,this->pos().y());
    }
}
void spongeBob::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys -= ((QKeyEvent*)event)->key();
}

