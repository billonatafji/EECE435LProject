#include "scores.h"

Scores::Scores()
{

}

QStringList Scores::GetUserScores(QString username, QString game){

    QFile file("Users.txt");

    QJsonDocument document;

    if (file.open(QFile::ReadOnly)) {
         document = QJsonDocument().fromJson(file.readAll());
         QJsonObject rootObject = document.object();

         if(rootObject.contains(username) ){
             QStringList scores = rootObject.find(username).value().toObject()[game].toObject()["Scores"].toString().split(',');
             if(scores.first() == "")
                 scores.removeFirst();
             return scores;
         }
    }
    return QStringList{};
}
bool Scores::AddScore(QString username, QString score, QString game){
    QFile file("Users.txt");

    QJsonDocument document;

    bool didWrite = false;

    if (file.open(QFile::ReadOnly)) {

        document = QJsonDocument().fromJson(file.readAll());
        QJsonObject rootObject = document.object();

        if(rootObject.contains(username) ){

             QJsonObject gameObject = rootObject.find(game).value().toObject();
            if (gameObject.find("HighestScore").value().toString().toInt() < score.toInt()){
                gameObject["HighestScore"] = score;
                gameObject["HighestScoreUser"] = username;
                rootObject[game] = gameObject;
            }

            QJsonObject userObject = rootObject.find(username).value().toObject();
            QJsonObject userGameObject = userObject.find(game).value().toObject();
            QStringList scoresList = userGameObject.find("Scores").value().toString().split(',');

            scoresList.append(score);

            userGameObject["Scores"] = scoresList.join(",");
            userObject[game] = userGameObject;
            rootObject[username] = userObject;

            document.setObject(rootObject);

            file.close();

            if(didWrite = file.open(QFile::WriteOnly)){
                file.write(document.toJson());
                file.close();
            }
        }
    }
    return didWrite;
}
QString Scores::GetHighestScore(QString game){
    QFile file("Users.txt");

    QJsonDocument document;

    if (file.open(QFile::ReadOnly)) {
        document = QJsonDocument().fromJson(file.readAll());
        QJsonObject rootObject = document.object();

        return QString("%1 - %2").arg(rootObject.find(game).value().toObject().find("HighestScore").value().toString(),rootObject.find(game).value().toObject().find("HighestScoreUser").value().toString());
    }
}
