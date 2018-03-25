#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "huItem.h"
#include "bacteria.h"
#include "virus.h"
#include <QTimer>
#include "header.h"
#include "game.h"
#include "fungus.h"

/**
*\game1scene.h
*\brief game1scene class
*
* This creates an instance of game1scene which includes a spongebob and other items.*/
class game1scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit game1scene(int gameMode, QString username, int difficulty = 1, Header* header = nullptr);///< constructor

    SpongeBob *spongeBobInstance; //!< Brief description after the member
    Header* header;///< pointer to header
    QTimer *addhuItemstimer;//!< QTimer attribute,
    QTimer *addbacteriatimer;//!< QTimer attribute,
    QTimer *addvirustimer;//!< QTimer attribute,
    QTimer *followtimer;//!< QTimer attribute,
     QTimer *addfungustimer;//!< QTimer attribute,

    ~game1scene();


signals:

public slots:
    void addhuItems();///< add huItems on the screen
    void addbacteria();///< add bacteria on the screen
    void addvirus();///< add viruses on the screen
    void addfungus();///< add fungii on the screen
};

#endif // GAME1SCENE_H
