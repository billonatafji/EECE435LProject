/**
* \file game1scene.cpp
* \brief game1scene class definition
*
* a game1scene contains all the interactions in the game
*\author Abdel Jawad Alami
*\date 22-2-2018
*/
#include "game1scene.h"
#include"stdlib.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QGraphicsLinearLayout>
#include <QColorDialog>

/**
 * @brief game1scene::game1scene
 * constructs the game1scene and all of its attributes, starts the timers, and connects the signal with its slot
 */

game1scene::game1scene(int difficulty)
{
    this->Difficulty = difficulty;

    this->setBackgroundBrush(QBrush(QImage("../Project435/images/background.png")
                                    .scaledToHeight(600)
                                    .scaledToWidth(1000)));
    this->setSceneRect(0,0,1000,600);

//    this->cleanlinessMeter = new CleanlinessMeter();
//    cleanlinessMeter->setPos(10,20);
//    this->addItem(cleanlinessMeter);

    this->spongeBobInstance = new SpongeBob();
    this->spongeBobInstance->setFlag(QGraphicsItem::ItemIsFocusable);
    this->spongeBobInstance->setFocus();
    this->spongeBobInstance->setPos(300,0);
    this->spongeBobInstance->installEventFilter(this);
    this->addItem(spongeBobInstance);

    this->header = new Header(this->spongeBobInstance,this->Difficulty);
    this->header->setPos(5,5);
    this->addItem(this->header);

    this->addhuItemstimer= new QTimer();
    this->addbacteriatimer= new QTimer();
    connect(addhuItemstimer,SIGNAL(timeout()),this,SLOT(addhuItems()));
    addhuItemstimer->start(200);
    connect(addbacteriatimer,SIGNAL(timeout()),this,SLOT(addbacteria()));
    addbacteriatimer->start(1000);

    this->addvirustimer= new QTimer();
    connect(addvirustimer,SIGNAL(timeout()),this,SLOT(addvirus()));
    addvirustimer->start(50000);

    //connect(this->spongeBobInstance, SIGNAL(v));


}
/**
 * @brief game1scene::addhuItems
 *
 * creates new huItems with a random direction and starting position
 */
void game1scene::addhuItems()
{
    /**
     * a random number is first choosen between 0 and 20
     * a huItem instance is created
     * if the random number is less than 2, the direction is set from left to right
     * else it is set from right to left
     *
     * the position is calculated by tho following equation : 50 + randomnumber *100
     * so the results can be: 50, 150, 250, 350
     */
    int randXPos =(rand() % 20);
    int randType =(rand() % 2);
    int randPic =(rand() % 4)+1;
    huItem *huItem1;
    std::string path = "../Project435/images/huItem"+std::to_string(randType)+ std::to_string(randPic)+".png";

    huItem1= new huItem(randType,this->header);
    huItem1->setPixmap((QPixmap(path.c_str())).scaledToHeight(45));
    huItem1->setPos(5+(randXPos)*45,0);

    this->addItem(huItem1);

}


void game1scene::addbacteria()
{
    /**
     * a random number is first choosen between 0 and 3
     * a bacteria is created
     * if the random number is less than 2, the direction is set from left to right
     * else it is set from right to left
     *
     * the position is calculated by the following equation : 50 + randomnumber *100
     * so the results can be: 50, 150, 250, 350
     */
    int direction=(rand() % 2);
    int startx=direction*990;
    int starty =50+(rand() % 4)*100;
    int strength=(rand() % 3)+1;
    std::string path = "../Project435/images/bacteria"+ std::to_string(strength)+".png";

    bacteria *bacteria1;

    bacteria1= new bacteria(strength,1-2*direction,1,3,2,20,starty, this->header);
    bacteria1->setPixmap((QPixmap(path.c_str())).scaledToHeight(45 + strength*45/2));
    bacteria1->setPos(startx,starty);

    this->addItem(bacteria1);

}

void game1scene::addvirus()
{
    /**
     * a random number is first choosen between 0 and 3
     * a virus is created
     * if the random number is less than 2, the direction is set from left to right
     * else it is set from right to left
     *
     * the position is calculated by the following equation : 50 + randomnumber *100
     * so the results can be: 50, 150, 250, 350
     */
    int direction=(rand() % 2);
    int startx=direction*980+5;
    int starty =50+(rand() % 4)*100;

    virus *virus1;

    virus1= new virus(1-2*direction,1,3,2,20,starty, this->header);
    virus1->setPixmap((QPixmap("../Project435/images/virus.png")).scaledToHeight(70));
    virus1->setPos(startx,starty);

    this->addItem(virus1);

}

