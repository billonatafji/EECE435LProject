#include "pause.h"
#include <QGraphicsScene>

Pause::Pause(QObject *parent) : QObject(parent)
{
    this->setFlags(QGraphicsItem::ItemIsSelectable);
}

void Pause::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
}
