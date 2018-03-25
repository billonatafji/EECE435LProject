#ifndef PAUSE_H
#define PAUSE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Pause : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Pause(QObject *parent = nullptr);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

signals:

public slots:
};

#endif // PAUSE_H
