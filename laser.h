#ifndef LASER_H
#define LASER_H
#include <QObject>

#include "weapon.h"

class Laser: public Weapon
{
public:
    Laser();

signals:

public slots:
    void update();
};

#endif // LASER_H
