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
#include "game1.h"
#include "scores.h"
/**
 * @brief game1scene::game1scene
 * constructs the game1scene and all of its attributes, starts the timers, and connects the signal with its slot
 */

game1scene::game1scene(GameView* gameView,int gameMode, QString username ,int difficulty, Header* header, bool paused)
{

    this->gameView = gameView;
    this->paused = paused;

    this->setBackgroundBrush(QBrush(QImage("../Project435/images/background.png")
                                    .scaledToHeight(600)
                                    .scaledToWidth(1000)));
    this->setSceneRect(0,0,1000,600);

    if(gameMode == Game::Over){
        QTimer* closeWindowTimer = new QTimer();
        connect(closeWindowTimer,SIGNAL(timeout()),this,SLOT(CloseView()));

        QGraphicsTextItem* gameOverLabel = new QGraphicsTextItem();

        gameOverLabel->setHtml("<h1>GAME OVER</h1>");
        gameOverLabel->setPos(400,200);

        this->addItem(gameOverLabel);

        closeWindowTimer->start(5000);

        return;

    }
    else if(gameMode == Game::Win){

        this->header = header;

        QTimer* closeWindowTimer = new QTimer();
        connect(closeWindowTimer,SIGNAL(timeout()),this,SLOT(CloseView()));

        QGraphicsTextItem* winLabel = new QGraphicsTextItem();
        QGraphicsTextItem* scoreLabel = new QGraphicsTextItem();

        winLabel->setHtml("<h1>Congratulations, You Won!</h1>");
        scoreLabel->setHtml("<h2>Score: "+ QString::number(this->header->player->score) + "</h2>");

        winLabel->setPos(300,200);
        scoreLabel->setPos(430,250);

        this->addItem(winLabel);
        this->addItem(scoreLabel);

        closeWindowTimer->start(5000);

        return;
    }

    else if(gameMode == Game::Pause){

        this->header = header;
        this->header->timer->stop();

        QGraphicsTextItem* pauseLabel = new QGraphicsTextItem();

        pauseLabel->setHtml("<h1>Paused</h1>");
        pauseLabel->setPos(450,200);

        this->addItem(pauseLabel);
        return;

    }

    else if(gameMode == Game::New){

        this->header->player = new SpongeBob(0,50,3,0,QPoint(300,0));
        this->header = new Header(this->header->player, difficulty, username, Game1::name, false, 120);


    }else if(gameMode == Game::Resume){

        this->header = header;
        //this->spongeBobInstance = this->header->player;

    }

    this->header->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->header->player->setFocus();
    this->header->player->setPos(this->header->player->currentPos);
    this->header->player->installEventFilter(this);
    this->addItem(this->header->player);

    this->header->setPos(5,5);
    this->header->pause->installEventFilter(this);
    this->addItem(this->header);

    this->addhuItemstimer= new QTimer();
    this->addbacteriatimer= new QTimer();
    connect(addhuItemstimer,SIGNAL(timeout()),this,SLOT(addhuItems()));
    addhuItemstimer->start(200);
    connect(addbacteriatimer,SIGNAL(timeout()),this,SLOT(addbacteria()));
    addbacteriatimer->start(1000);

if (difficulty>1)
{
    this->addvirustimer= new QTimer();
    connect(addvirustimer,SIGNAL(timeout()),this,SLOT(addvirus()));
    addvirustimer->start(50000);
}

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
    bool randType =(rand() % 100)>(this->header->difficulty)*25;
    int randPic =(rand() % 4)+1;
    huItem *huItem1;
    std::string path = "../Project435/images/huItem"+std::to_string(randType)+ std::to_string(randPic)+".png";//first number (0 or1) is for type of item (1 is healthy and 0 is unhealthy) the second is for the picture to display

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

    this->header->SetCleanliness(-strength);

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
    this->header->SetCleanliness(-5);

    this->addItem(virus1);

}

game1scene::~game1scene(){
    this->clear();
}

void game1scene::GameOver(){

   User::PauseGameForUser(this->header,true);
   game1scene* newScene = new game1scene(this->gameView,Game::Over,this->header->username);
   this->gameView->setScene(newScene);
   this->deleteLater();
}

void game1scene::CloseView(){
    this->gameView->close();
    this->deleteLater();
}

void game1scene::WonGame(){
    if(User::GetUserLevel(Game1::name,this->header->username) == this->header->difficulty && this->header->difficulty != 3){
        User::UpgradeUserToLevel(Game1::name,this->header->username,this->header->difficulty+1);
    }
    Scores::AddScore(this->header->username,QString::number(this->header->player->score),Game1::name);
    User::PauseGameForUser(this->header,true);
    SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos);
    Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->completed,this->header->time);
    game1scene* newScene = new game1scene(this->gameView,Game::Win,newheader->username,newheader->difficulty,newheader);
    this->gameView->setScene(newScene);
    this->deleteLater();
}

void game1scene::PauseGame(){
    if(!this->paused){
        if(this->header->username != ""){
            User::PauseGameForUser(this->header, false);
        }
        SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos);
        Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->completed,this->header->time);
        game1scene* newScene = new game1scene(this->gameView,Game::Pause,newheader->username,newheader->difficulty,newheader, true);
        this->gameView->setScene(newScene);
        this->deleteLater();
    }else{
        SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos);
        Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->completed,this->header->time);
        game1scene* newScene = new game1scene(this->gameView,Game::Resume,newheader->username,newheader->difficulty,newheader, false);
        this->gameView->setScene(newScene);
        this->deleteLater();
    }

}

void game1scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        this->PauseGame();
    }else if(!this->paused){
        this->header->player->keyPressEvent(event);
    }
}

/**
 * @brief game1scene::keyReleaseEvent
 * @param event
 *
 * this collects key release events and removes them from the set of pressed keys
 */
void game1scene::keyReleaseEvent(QKeyEvent *event)
{
    if(!this->paused){
        this->header->player->keyReleaseEvent(event);
    }
}

void game1scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    PauseGame();
}
