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
    QTimer* throwTimer;
    bool thrown;
    bool grabbingItem;
    QGraphicsItem* grabbedItem;

    void keyReleaseEvent(QKeyEvent *event);

signals:

public slots:
    void update();
};

#endif // WEAPON_H
