#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "game1scene.h"

/**
*\mainpageLab3
*\author Abdel Jawad Alami
*\date 22-2-2018
*/

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    game1scene *scene1=new game1scene();

    QGraphicsView view( scene1);
    view.setFixedSize(1000,600);
    view.setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view.setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view.show();


    return app.exec();
}

