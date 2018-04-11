#ifndef BOMB_H
#define BOMB_H
#include "weapon.h"

class Bomb: public Weapon
{
public:
    Bomb();

signals:

public slots:
    void update();
};

#endif // BOMB_H
