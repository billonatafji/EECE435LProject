#ifndef USER_H
#define USER_H

#include <QString>
#include <QPixmap>
#include <QBuffer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include "header.h"

class User
{
public:
    explicit User(QString username, QString password, QString firstName, QString lastName, QString dateOfBirth, QString gender, QImage profilePicture);
    User();

    QString Username;
    QString Password;
    QString FirstName;
    QString LastName;
    QString DateOfBirth;
    QString Gender;
    QImage ProfilePicture;

    static bool AddUser(User user);
    static User* GetUser(QString username, QString password);
    static QJsonObject UserToJson(User user);
    static User* JsonToUser(QJsonObject object, QString username);
    static void PauseGameForUser(Header* header, bool completed);
    static Header* ResumeGameForUser(QString game, QString username);
    static int GetUserLevel(QString game, QString username);
    static void UpgradeUserToLevel(QString game, QString username, int level);

};

#endif // USER_H
