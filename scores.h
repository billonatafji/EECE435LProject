#ifndef SCORES_H
#define SCORES_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QVector>

class Scores
{
public:
    Scores();

    QString static GetHighestScore(QString game);

    QStringList static GetUserScores(QString username, QString game);

    bool static AddScore(QString username, QString score, QString game);

};

#endif // SCORES_H
