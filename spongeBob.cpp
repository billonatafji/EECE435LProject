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
#include "game1.h"
#include "game2.h"
#include "laser.h"
#include "hook.h"
#include "bomb.h"
#include "game2scene.h"

SpongeBob::SpongeBob(int cleanliness, int immunity, int lives, int score, QPoint pos, QString game,QObject *parent, int bombs, int requiredBombScore) : QObject(parent)
{

    this->cleanliness = cleanliness;
    this->immunity = immunity;
    this->lives = lives;
    this->followme=0;
    this->score = score;
    this->currentPos = pos;
    this->game = game;
    this->translation = 0;
    this->bombs = bombs;
    this->requiredBombScore = requiredBombScore;

    followTimer= new QTimer();
    connect(followTimer,SIGNAL(timeout()),this,SLOT(toggleFollow()));
    setPixmap((QPixmap(":/Project435/images/spongebob.png")).scaledToHeight(100));


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
    if(this->game == Game1::name){
        pressedKeys += ((QKeyEvent*)event)->key();

        if( pressedKeys.contains(Qt::Key_Up) && this->y()>0 )
        {
            this->setPos(this->pos().x(),this->pos().y()-10);
        }
        if( pressedKeys.contains(Qt::Key_Left)&& this->x()>0 )
        {
            this->setPos(this->pos().x()-10,this->pos().y());
        }
        if( pressedKeys.contains(Qt::Key_Down)&& this->y()<500  )
        {
            this->setPos(this->pos().x(),this->pos().y()+10);
        }
        if( pressedKeys.contains(Qt::Key_Right)&& this->x()<920 )
        {
            this->setPos(this->pos().x()+10,this->pos().y());
        }
        this->currentPos = QPoint(this->pos().x(),this->pos().y());

    }else if(this->game == Game2::name){

        pressedKeys += ((QKeyEvent*)event)->key();

        if(pressedKeys.contains(Qt::Key_Left)){
            this->translation += 5;
            this->setTransformOriginPoint(50,50);
            this->setRotation(this->translation);
        }
        if(pressedKeys.contains(Qt::Key_Right)){
            this->translation -= 5;
            this->setTransformOriginPoint(50,50);
            this->setRotation(this->translation);
        }
        if(pressedKeys.contains(Qt::Key_X)){
            if(this->weapon->ready){
                if(dynamic_cast<Bomb*>(this->weapon)){

                    this->weapon->setParentItem(nullptr);
                    this->weapon->setTransformOriginPoint(this->transformOriginPoint());
                    this->weapon->setRotation(this->rotation());
                    this->weapon->setPos(this->pos());
                    this->weapon->thrown = !this->weapon->thrown;
                    this->weapon->throwTimer->start(10/(this->weapon->strength+1));
                    ((Game2Scene*)this->scene())->header->RemoveBomb();
                    int strength = this->weapon->strength;
                    this->weapon = new Hook(strength);
                    this->weapon->setParentItem(this);
                }
                else{
                    this->weapon->thrown = !this->weapon->thrown;
                    this->weapon->throwTimer->start(10/(this->weapon->strength+1));
                }
            }
        }
        if(pressedKeys.contains(Qt::Key_Z)){

            int strength = this->weapon->strength;

            if(dynamic_cast<Hook*>(this->weapon)){
                delete this->weapon;
                this->weapon = new Laser(strength);
            }else if(dynamic_cast<Laser*>(this->weapon)){
                delete this->weapon;
                if(this->score >= this->requiredBombScore && this->bombs > 0){
                    this->weapon = new Bomb(strength);
                    this->weapon->setParentItem(this);
                }else{
                    this->weapon = new Hook(strength);
                }
            }else{
                delete this->weapon;
                this->weapon = new Hook(strength);
            }
            this->weapon->setParentItem(this);
        }
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
