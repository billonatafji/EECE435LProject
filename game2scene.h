#ifndef Game2Scene_H
#define Game2Scene_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "huItem.h"
#include "bacteria.h"
#include "virus.h"
#include <QTimer>
#include "header.h"
#include "game.h"
#include "fungus.h"
#include "gameview.h"

/**
*\Game2Scene.h
*\brief Game2Scene class
*
* This creates an instance of Game2Scene which includes a spongebob and other items.*/
class Game2Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game2Scene(GameView* gameView, int gameMode, QString username, int difficulty = 1, Header* header = nullptr, bool paused = false);///< constructor

    Header* header;///< pointer to header
    QTimer *addItemToQueueTimer;//!< QTimer attribute,

    GameView* gameView;
    bool paused;
    bool completed;

    void GameOver();
    void WonGame();
    void PauseGame();

    void addhuItems();///< add huItems on the screen
    void addbacteria();///< add bacteria on the screen
    void addvirus();///< add viruses on the screen
    void addfungus();///< add fungii on the screen

    void keyPressEvent(QKeyEvent *event);
    /**
    *\brief Detects key release events
    *\param *event first argument, key release event
    */
    void keyReleaseEvent(QKeyEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    ~Game2Scene();


signals:

public slots:
    void addItemToQueue();

    void CloseView();
};

#endif // Game2Scene_H
