#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QKeyEvent>

class Weapon : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Weapon(QObject *parent = nullptr);
    QGraphicsPixmapItem* head;
    QGraphicsLineItem* rope;
    QGraphicsItem* grabbedItem;
    QTimer* throwTimer;
    QTimer* prepareTimer;
    QString name;
    bool thrown;
    bool grabbingItem;
    bool ready;
    int step;
    int strength;


signals:

public slots:
    virtual void update();
};

#endif // WEAPON_H
