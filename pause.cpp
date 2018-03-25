#include "pause.h"
#include <QGraphicsScene>

Pause::Pause(QObject *parent) : QObject(parent)
{
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setSelected(true);
    this->setFlag(QGraphicsItem::ItemIsMovable);

}

void Pause::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){

    int i;
}
