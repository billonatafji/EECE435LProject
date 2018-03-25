/**
* \file spongeBob.cpp
* \brief spongeBob class definition
*
* a spongeBob instance
*\author Abdel Jawad Alami
*\date 18-3-2018
*/

#include "spongeBob.h"
#include "game1scene.h"

SpongeBob::SpongeBob(int cleanliness, int immunity, int lives, int score, QPoint pos, QObject *parent) : QObject(parent)
{

    this->cleanliness = cleanliness;
    this->immunity = immunity;
    this->lives = lives;
    this->followme=0;
    this->score = score;
    this->currentPos = pos;

    followTimer= new QTimer();
    connect(followTimer,SIGNAL(timeout()),this,SLOT(toggleFollow()));
    setPixmap((QPixmap("../Project435/images/spongebob.png")).scaledToHeight(100));

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

/**
 * @brief spongeBob::toggleFollow
 * toggles the follow me to false when the timer ends
 */
void SpongeBob::toggleFollow()
{
    if (this->followme==1)
        this->followme=0;

}



/**
 * @brief spongeBob::keyPressEvent
 * @param event
 *
 * the keypress event detects all key strokes on the keyboard.
 * we are only interested in the up,down,left, and right strokes
 * when one of those keys is pressed, spongebob moves accoringly when possible.
 * it also moves diagonally if multiple of these keys are pressed at the same time.
 * Sponge bob moves diagonally faster than horizontally and vertically
 * if the location of spongebob is on the edges of the screen, the position isnt updated if this will result in leaving the screen
 */
void SpongeBob::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Escape){

        ((game1scene*)this->scene())->header->PauseGame();

    }else{
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
        this->currentPos = QPoint(this->pos().x(),this->pos().y());
    }


}

/**
 * @brief spongeBob::keyReleaseEvent
 * @param event
 *
 * this collects key release events and removes them from the set of pressed keys
 */
void SpongeBob::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys -= ((QKeyEvent*)event)->key();
}

SpongeBob::~SpongeBob(){
}
