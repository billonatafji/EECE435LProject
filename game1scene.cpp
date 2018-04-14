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

    this->setBackgroundBrush(QBrush(QImage(":/Project435/images/background.jpg")
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

        closeWindowTimer->start(4000);

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

        SpongeBob* player = new SpongeBob(0,50,3,0,QPoint(300,0), Game1::name);
        this->header = new Header(player, difficulty, username, Game1::name, false, 120);


    }else if(gameMode == Game::Resume){

        this->header = header;

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
    addhuItemstimer->start(800);
    connect(addbacteriatimer,SIGNAL(timeout()),this,SLOT(addbacteria()));
    addbacteriatimer->start(1000);

    if (difficulty==2)
    {
        this->addvirustimer= new QTimer();
        connect(addvirustimer,SIGNAL(timeout()),this,SLOT(addvirus()));
        addvirustimer->start(20000);
    }
    if (difficulty==3)
    {
        this->addfungustimer= new QTimer();
        connect(addfungustimer,SIGNAL(timeout()),this,SLOT(addfungus()));
        addfungustimer->start(20000);
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
    std::string path = ":/Project435/images/huItem"+std::to_string(randType)+ std::to_string(randPic)+".png";//first number (0 or1) is for type of item (1 is healthy and 0 is unhealthy) the second is for the picture to display

    huItem1= new huItem(randType,this->header, Game1::name);
    huItem1->setPixmap((QPixmap(path.c_str())).scaledToHeight(45));
    huItem1->setPos(5+(randXPos)*45,0);

    this->addItem(huItem1);

}

/**
 * @brief game1scene::addbacteria
 *
 * first we check if the cleanness is less than 100
 * if true, we continue with the procedure of adding a bacteria to the scene
 * a random number is first choosen between 0 and 3
 * a bacteria is created
 * if the random number is less than 2, the direction is set from left to right
 * else it is set from right to left
 *
 * the position is calculated by the following equation : 50 + randomnumber *100
 * so the results can be: 50, 150, 250, 350
 *
 * the strength of the bacteria is also generated randomly
 *
 * velocity is generated randomly with an influance of the difficulty of the game
 * the harder the game, the faster the bacteria
 *
 */
void game1scene::addbacteria()
{

    int addableAmmount=(100- this->header->player->cleanliness) - this->header->currentBacteriaCountInScene;
    if (addableAmmount>0)
    {
        int direction=(rand() % 2);
        int startx=direction*990;
        int starty =50+(rand() % 4)*100;
        int strength=(rand() % 3)+1;
        double xvelocity=(rand() % 6)/3+(this->header->difficulty);
        double yvelocity=(rand() % 6)/3+(this->header->difficulty/2.0);
        if (addableAmmount==2 || addableAmmount==1)
            strength=addableAmmount;
        std::string path = "../Project435/images/bacteria"+ std::to_string(strength)+".png";

        bacteria *bacteria1;
        bacteria1= new bacteria(strength,1-2*direction,1,xvelocity,yvelocity,20,starty, this->header, Game1::name);
        bacteria1->setPixmap((QPixmap(path.c_str())).scaledToHeight(45 + strength*45/2));
        bacteria1->setPos(startx,starty);

        this->header->currentBacteriaCountInScene +=strength;
        this->addItem(bacteria1);
    }
}

/**
 * @brief game1scene::addvirus
 *
 * this is a function to add a virus to the screen
 * a random number is first choosen between 0 and 1 to set direction
 * the starting y posiion is then chosen randomly
 * a virus is created
 */
void game1scene::addvirus()
{

    int direction=(rand() % 2);
    int startx=direction*980+5;
    int starty =50+(rand() % 4)*100;

    virus *virus1;
    virus1= new virus(1-2*direction,1,3,2,20,starty, this->header, Game1::name);
    virus1->setPixmap((QPixmap(":/Project435/images/virus.png")).scaledToHeight(70));
    virus1->setPos(startx,starty);


    this->addItem(virus1);

}

/**
 * @brief game1scene::addfungus
 *
 *
 * a random number is first choosen for the x and y positions
 * then the distance to the player is calculated
 * if the distance is less than 250, the position is randomly generated again
 *
 * when the distance criteria is met, an instance of the fungus is created with the generated coordinates
 *
 */
void game1scene::addfungus()
{

positionselection:
    int startx=(rand() % 960);
    int starty =(rand() % 550);
    int playerx= this->header->player->x();
    int playery= this->header->player->y();
    double diry = playery - starty;
    double dirx= playerx - startx;
    double hyp = sqrt(dirx*dirx + diry*diry);
    if(hyp<250)
        goto positionselection;

    fungus *fungus1;
    fungus1= new fungus(this->header, Game1::name);
    fungus1->setPixmap((QPixmap(":/Project435/images/fungus.png")).scaledToHeight(70));
    fungus1->setPos(startx,starty);

    this->addItem(fungus1);

}
/**
 * @brief game1scene::GameOver
 *
 * if user loses, the game is over.
 */
void game1scene::GameOver(){
    this->header->paused = true;
    User::PauseGameForUser(this->header,true);
    SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos, Game1::name);
    Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->paused,this->header->time);
    game1scene* newScene = new game1scene(this->gameView,Game::Over,newheader->username,newheader->difficulty,newheader);
    this->gameView->setScene(newScene);
    this->deleteLater();
}

/**
 * @brief game1scene::CloseView
 *
 * this function is exited closing the window.
 */
void game1scene::CloseView(){
    this->gameView->close();
    this->deleteLater();
}

/**
 * @brief game1scene::WonGame
 *
 * this function is exited when a player wins the game.
 * their score is saved, and the scene is closed.
 */
void game1scene::WonGame(){
    this->header->paused = true;
    if(this->header->username != ""){
        if(User::GetUserLevel(Game1::name,this->header->username) == this->header->difficulty && this->header->difficulty != 3){
            User::UpgradeUserToLevel(Game1::name,this->header->username,this->header->difficulty+1);
        }
        Scores::AddScore(this->header->username,QString::number(this->header->player->score),Game1::name);
        User::PauseGameForUser(this->header,true);
    }
    SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos, Game1::name);
    Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->paused,this->header->time);
    game1scene* newScene = new game1scene(this->gameView,Game::Win,newheader->username,newheader->difficulty,newheader);
    this->gameView->setScene(newScene);
    this->deleteLater();
}

/**
 * @brief game1scene::PauseGame
 *
 * this function is called when pausing the game is needed.
 * the header and player stats are saved in the files.
 */
void game1scene::PauseGame(){
    if(!this->paused){
        this->header->paused = true;
        if(this->header->username != ""){
            User::PauseGameForUser(this->header, false);
        }
        SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos, Game1::name);
        Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->paused,this->header->time);
        game1scene* newScene = new game1scene(this->gameView,Game::Pause,newheader->username,newheader->difficulty,newheader, true);
        this->gameView->setScene(newScene);
        this->deleteLater();
    }else{

        SpongeBob* newPlayer = new SpongeBob(this->header->player->cleanliness,this->header->player->immunity,this->header->player->lives,this->header->player->score,this->header->player->currentPos, Game1::name);
        Header* newheader = new Header(newPlayer,this->header->difficulty,this->header->username,this->header->game,this->header->paused,this->header->time);
        game1scene* newScene = new game1scene(this->gameView,Game::Resume,newheader->username,newheader->difficulty,newheader, false);
        this->gameView->setScene(newScene);
        newScene->header->paused = false;
        this->deleteLater();
    }

}

void game1scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && !this->completed){
        this->PauseGame();
    }else if(!this->completed){
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
    if(!this->completed){
        this->header->player->keyReleaseEvent(event);
    }
}

void game1scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    if(!this->completed){
        PauseGame();
    }

}

game1scene::~game1scene(){
    this->clear();
}
