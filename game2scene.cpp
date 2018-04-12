/**
* \file Game2Scene.cpp
* \brief Game2Scene class definition
*
* a Game2Scene contains all the interactions in the game
*\author Abdel Jawad Alami
*\date 22-2-2018
*/
#include "game2scene.h"
#include"stdlib.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QGraphicsLinearLayout>
#include <QColorDialog>
#include "game2.h"
#include "scores.h"
#include "hook.h"
#include "laser.h"
/**
 * @brief Game2Scene::Game2Scene
 * constructs the Game2Scene and all of its attributes, starts the timers, and connects the signal with its slot
 */

Game2Scene::Game2Scene(GameView* gameView,int gameMode, QString username ,int difficulty, Header* header, bool paused)
{

    this->gameView = gameView;
    this->paused = paused;

    this->setBackgroundBrush(QBrush(QImage(":/Project435/images/background2.jpg")
                                    .scaledToHeight(600)
                                    .scaledToWidth(1000)));
    this->setSceneRect(0,0,1000,600);

    if(gameMode == Game::Over){
        this->completed = true;
        this->header = header;
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
        this->completed = true;
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

        closeWindowTimer->start(3500);

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

        SpongeBob* player = new SpongeBob(0,50,3,0,QPoint(500-50,300-50), Game2::name, nullptr, ceil(3/difficulty));
        this->header = new Header(player, difficulty, username, Game2::name, false, 120);


    }else if(gameMode == Game::Resume){

        this->header = header;

    }

    this->header->player->setFlag(QGraphicsItem::ItemIsFocusable);
    this->header->player->setFocus();
    this->header->player->setPos(this->header->player->currentPos);
    this->header->player->installEventFilter(this);
    this->addItem(this->header->player);

    Laser* weapon = new Laser();
    weapon->setParentItem(this->header->player);

    this->addItem(weapon);
    this->header->player->weapon = weapon;

    this->header->setPos(5,5);
    this->header->pause->installEventFilter(this);
    this->addItem(this->header);

    this->addItemToQueueTimer = new QTimer();
    connect(this->addItemToQueueTimer,SIGNAL(timeout()),this,SLOT(addhuItems()));
    this->addItemToQueueTimer->start(3000);

}


/**
 * @brief Game2Scene::addhuItems
 *
 * creates new huItems with a random direction and starting position
 */
void Game2Scene::addhuItems()
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
    std::string path = ":/Project435/images/huItem"+std::to_string(randType)+ std::to_string(randPic)+".png";//first number (0 or1) is for type of item (1 is healthy and 0 is unhealthy) the second is for the picture to display

    huItem1= new huItem(randType,this->header, Game2::name);
    huItem1->setPixmap((QPixmap(path.c_str())).scaledToHeight(45));
    huItem1->setPos(150,50);

    this->addItem(huItem1);

}

void Game2Scene::GameOver(){
    this->header->paused = true;
    User::PauseGameForUser(this->header,true);
    SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos, Game2::name);
    Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->paused,this->header->time);
    Game2Scene* newScene = new Game2Scene(this->gameView,Game::Over,newheader->username,newheader->difficulty,newheader);
    this->gameView->setScene(newScene);
    this->deleteLater();
}

void Game2Scene::CloseView(){
    this->gameView->close();
    this->deleteLater();
}

void Game2Scene::WonGame(){
    this->header->paused = true;
    if(this->header->username != ""){
        if(User::GetUserLevel(Game2::name,this->header->username) == this->header->difficulty && this->header->difficulty != 3){
            User::UpgradeUserToLevel(Game2::name,this->header->username,this->header->difficulty+1);
        }
        Scores::AddScore(this->header->username,QString::number(this->header->player->score),Game2::name);
        User::PauseGameForUser(this->header,true);
    }
    SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos, Game2::name);
    Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->paused,this->header->time);
    Game2Scene* newScene = new Game2Scene(this->gameView,Game::Win,newheader->username,newheader->difficulty,newheader);
    this->gameView->setScene(newScene);
    this->deleteLater();
}

void Game2Scene::PauseGame(){
    if(!this->paused){
        this->header->paused = true;
        if(this->header->username != ""){
            User::PauseGameForUser(this->header, false);
        }
        SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos, Game2::name);
        Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->paused,this->header->time);
        Game2Scene* newScene = new Game2Scene(this->gameView,Game::Pause,newheader->username,newheader->difficulty,newheader, true);
        this->gameView->setScene(newScene);
        this->deleteLater();
    }else{

        SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos, Game2::name);
        Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->paused,this->header->time);
        Game2Scene* newScene = new Game2Scene(this->gameView,Game::Resume,newheader->username,newheader->difficulty,newheader, false);
        this->gameView->setScene(newScene);
        newScene->header->paused = false;
        this->deleteLater();
    }

}

void Game2Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && !this->completed){
        this->PauseGame();
    }else if(!this->completed){
        this->header->player->keyPressEvent(event);
    }
}

/**
 * @brief Game2Scene::keyReleaseEvent
 * @param event
 *
 * this collects key release events and removes them from the set of pressed keys
 */
void Game2Scene::keyReleaseEvent(QKeyEvent *event)
{
    if(!this->completed){
        this->header->player->keyReleaseEvent(event);
    }
}

void Game2Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    if(!this->completed){
        PauseGame();
    }

}

Game2Scene::~Game2Scene(){
    this->clear();
}
