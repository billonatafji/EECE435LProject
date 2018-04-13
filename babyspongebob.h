#ifndef BABYSPONGEBOB_H
#define BABYSPONGEBOB_H

#include<QGraphicsPixmapItem>
#include <QTimer>

class BabySpongeBob : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit BabySpongeBob(int healthyItemsFed = 0, QObject *parent = nullptr);

    QTimer* timer;

    int healthyItemsFed;

signals:

public slots:
    void update();
};

#endif // BABYSPONGEBOB_H
