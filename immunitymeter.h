#ifndef IMMUNITYMETER_H
#define IMMUNITYMETER_H

#include <QGraphicsProxyWidget>
#include <QPen>
#include "cleanlinessmeter.h"

class ImmunityMeter:  public QGraphicsItemGroup
{
public:
    ImmunityMeter();

    double Progress;

    QGraphicsItem* cleanlinessMeter;
    QGraphicsPixmapItem* hearts[3];
    QGraphicsTextItem* timeLabel;
    QGraphicsTextItem* levelLabel;
    QGraphicsTextItem* scoreLabel;
    QGraphicsLineItem* needle;


    int time;
    int level;
    int score;

    void SetProgress(int val);

    void AddCleanlMeter(int x, int y);
    void AddChart(int x, int y, int width, int height, int startAngle, int spanAngle, QColor color);
    void AddHeart(int x, int y, int number);
    void AddTime(int x, int y);
    void AddLevel(int x, int y);
    void AddScore(int x, int y);
    void AddNeedle(int x, int y);


};

#endif // IMMUNITYMETER_H
