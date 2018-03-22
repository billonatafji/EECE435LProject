#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "spongeBob.h"
#include "huItem.h"
#include "bacteria.h"
#include "virus.h"
#include <QTimer>
#include "cleanlinessmeter.h"
#include "header.h"

/**
*\game1scene.h
*\brief game1scene class
*
* This creates an instance of game1scene which includes a bear and huItems.*/
class game1scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit game1scene(int difficulty);///< constructor
    SpongeBob *spongeBobInstance; //!< Brief description after the member

    Header* header;
    QTimer *addhuItemstimer;//!< QTimer attribute,
    QTimer *addbacteriatimer;//!< QTimer attribute,
    QTimer *addvirustimer;//!< QTimer attribute,
    QTimer *followtimer;//!< QTimer attribute,

    int Difficulty;



signals:

public slots:
    void addhuItems();///< add huItems on the screen
    void addbacteria();
    void addvirus();
};

#endif // GAME1SCENE_H
