#include "user.h"
#include "game1.h"
#include "game2.h"

User::User(){

}
User::User(QString username, QString password, QString firstName, QString lastName, QString dateOfBirth, QString gender, QImage profilePicture)
{
    this->Username = username;
    this->Password = password;
    this->FirstName = firstName;
    this->LastName = lastName;
    this->DateOfBirth = dateOfBirth;
    this->Gender = gender;
    this->ProfilePicture = profilePicture;

}

bool User::AddUser(User user){

    QFile file("Users.txt");

    QJsonDocument document;

    bool didWrite = false;

    if (file.open(QFile::ReadOnly)) {

        document = QJsonDocument().fromJson(file.readAll());

        QJsonObject rootObject = document.object();

        if(!rootObject.contains(user.Username)){

            rootObject[user.Username] = UserToJson(user);

            document.setObject(rootObject);
            file.close();
            if(didWrite = file.open(QFile::WriteOnly)){
                file.write(document.toJson());
                file.close();
            }
        }
        else{
            file.close();
        }

    }
    return didWrite;
}
User* User::GetUser(QString username, QString password){

    QFile file("Users.txt");

    QJsonDocument document;

    if (file.open(QFile::ReadOnly)) {
         document = QJsonDocument().fromJson(file.readAll());
         QJsonObject rootObject = document.object();
         if(rootObject.contains(username) && rootObject.find(username).value().toObject()["Password"].toString() == password){
             return JsonToUser(rootObject.find(username).value().toObject(),username);
         }
    }
    return new User();
}
QJsonObject User::UserToJson(User user){

    QJsonObject stateObject;

    stateObject["difficulty"] = 0;
    stateObject["x"] = 0;
    stateObject["y"] = 0;
    stateObject["lives"] = 0;
    stateObject["score"] = 0;
    stateObject["immunity"] = 0;
    stateObject["cleanliness"] = 0;
    stateObject["time"] = 0;
    stateObject["completed"] = true;
    stateObject["translation"] = 0;
    stateObject["weapon"] = "";
    stateObject["bombs"] = 0;
    stateObject["requiredBombScore"] = 0;
    stateObject["weaponStrength"] = 0;
    stateObject["healthyItemsFed"] = 0;

    QJsonObject gameObject;
    gameObject["Scores"] = "";
    gameObject["State"] = stateObject;
    gameObject["Level"] = 1;

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    user.ProfilePicture.save(&buffer, "PNG");

    QJsonObject userObject;
    userObject["Password"] = user.Password;
    userObject["FirstName"] = user.FirstName;
    userObject["LastName"] = user.LastName;
    userObject["DateOfBirth"] = user.DateOfBirth;
    userObject["Gender"] = user.Gender;
    userObject["ProfilePicture"] = QString::fromLatin1(buffer.data().toBase64());
    userObject["Game1"] = gameObject;
    userObject["Game2"] = gameObject;

    return userObject;
}

User* User::JsonToUser(QJsonObject object, QString username){

    QPixmap pixMap;
    QByteArray byteArray = QByteArray::fromBase64(object["ProfilePicture"].toString().toLatin1());
    pixMap.loadFromData(byteArray,"PNG");
    User* user = new User(username,object["Password"].toString(),object["FirstName"].toString(),object["LastName"].toString(),object["DateOfBirth"].toString(),object["Gender"].toString(), pixMap.toImage());

    return user;
}

void User::PauseGameForUser(Header* header, bool completed){

    QFile file("Users.txt");

    if (file.open(QFile::ReadOnly)) {

        QJsonDocument document = QJsonDocument().fromJson(file.readAll());
        QJsonObject rootObject = document.object();

        QJsonObject userObject = rootObject.find(header->username).value().toObject();
        QJsonObject userGameObject = userObject.find(header->game).value().toObject();
        QJsonObject stateObject;

        stateObject["difficulty"] = header->difficulty;
        stateObject["x"] = header->player->currentPos.x();
        stateObject["y"] = header->player->currentPos.y();
        stateObject["lives"] = header->player->lives;
        stateObject["score"] = header->player->score;
        stateObject["immunity"] = header->player->immunity;
        stateObject["cleanliness"] = header->player->cleanliness;
        stateObject["time"] = (int)header->time;
        stateObject["completed"] = completed;

        if(header->game == Game2::name){
            stateObject["translation"] = header->player->translation;
            stateObject["bombs"] = header->player->bombs;
            stateObject["requiredBombScore"] = header->player->requiredBombScore;
            stateObject["weapon"] = header->player->weapon->name;
            stateObject["weaponStrength"] = header->player->weapon->strength;
            stateObject["healthyItemsFed"] = header->baby->healthyItemsFed;
        }


        userGameObject["State"] = stateObject;
        userObject[header->game] = userGameObject;
        rootObject[header->username] = userObject;

        document.setObject(rootObject);

        file.close();

        if(file.open(QFile::WriteOnly)){
            file.write(document.toJson());
            file.close();
        }

    }
}

Header* User::ResumeGameForUser(QString game, QString username){

    QFile file("Users.txt");
    Header* header;

    if (file.open(QFile::ReadOnly)) {

        QJsonDocument document = QJsonDocument().fromJson(file.readAll());
        QJsonObject rootObject = document.object();

        QJsonObject userObject = rootObject.find(username).value().toObject();
        QJsonObject userGameObject = userObject.find(game).value().toObject();
        QJsonObject stateObject = userGameObject.find("State").value().toObject();

        SpongeBob* player = new SpongeBob(stateObject.find("cleanliness").value().toInt(),
                                          stateObject.find("immunity").value().toInt(),
                                          stateObject.find("lives").value().toInt(),
                                          stateObject.find("score").value().toInt(),
                                          QPoint(stateObject.find("x").value().toInt(),stateObject.find("y").value().toInt()),
                                          game);

        header = new Header(player,stateObject.find("difficulty").value().toInt(), username, game, stateObject.find("completed").value().toBool(), stateObject.find("time").value().toInt());

        file.close();
    }
    return header;
}

int User::GetUserLevel(QString game, QString username){

    int level = 0;
    QFile file("Users.txt");

    if (file.open(QFile::ReadOnly)) {
        QJsonDocument document = QJsonDocument().fromJson(file.readAll());
        QJsonObject rootObject = document.object();

        QJsonObject userObject = rootObject.find(username).value().toObject();
        QJsonObject userGameObject = userObject.find(game).value().toObject();
        level = userGameObject.find("Level").value().toInt();

        file.close();
    }
    return level;
}

void User::UpgradeUserToLevel(QString game, QString username, int level){

    QFile file("Users.txt");

    if (file.open(QFile::ReadOnly)) {

        QJsonDocument document = QJsonDocument().fromJson(file.readAll());
        QJsonObject rootObject = document.object();

        QJsonObject userObject = rootObject.find(username).value().toObject();
        QJsonObject userGameObject = userObject.find(game).value().toObject();

        userGameObject["Level"] = level;
        userObject[game] = userGameObject;
        rootObject[username] = userObject;

        document.setObject(rootObject);

        file.close();

        if(file.open(QFile::WriteOnly)){
            file.write(document.toJson());
            file.close();
        }
    }

}

