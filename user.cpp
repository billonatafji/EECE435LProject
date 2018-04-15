/**
* \file User.cpp
* \brief User class definition
*
* this class contains all user information
*\author Bilal Natafgi
*\date 20-2-2018
*/

#include "user.h"
#include "game1.h"
#include "game2.h"
#include "bomb.h"
#include "laser.h"
#include "hook.h"

User::User(){

}
User::User(QString username, QString password, QString firstName, QString lastName, QString dateOfBirth, QString gender, QImage profilePicture)
{
    /// setting attributes
    this->Username = username;
    this->Password = password;
    this->FirstName = firstName;
    this->LastName = lastName;
    this->DateOfBirth = dateOfBirth;
    this->Gender = gender;
    this->ProfilePicture = profilePicture;

}

/**
 * @brief User::AddUser
 * @param user
 * @return
 *
 * this function adds a new user and saves the records to the json file
 */
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

/**
 * @brief User::GetUser
 * @param username
 * @param password
 * @return
 *
 * this function searches for a user based on a username and a password
 */
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
/**
 * @brief User::UserToJson
 * @param user
 * @return
 *
 * this function takes an instance of a user and converts its attributes to a json object
 */
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

/**
 * @brief User::JsonToUser
 * @param object
 * @param username
 * @return
 *
 * this function takes a json object and parses it to an user object
 */
User* User::JsonToUser(QJsonObject object, QString username){

    QPixmap pixMap;
    QByteArray byteArray = QByteArray::fromBase64(object["ProfilePicture"].toString().toLatin1());
    pixMap.loadFromData(byteArray,"PNG");
    User* user = new User(username,object["Password"].toString(),object["FirstName"].toString(),object["LastName"].toString(),object["DateOfBirth"].toString(),object["Gender"].toString(), pixMap.toImage());

    return user;
}
/// this function is used to pause the game for later access. it saves the data in a json document.
/// the values of attributes in the header are saved.
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
/// this function is given a game and a username, and is used to check if there are available paused games for the user.
/// if there is a paused game, an instance of header and spongebob are created and filled with the previously saved state.
Header* User::ResumeGameForUser(QString game, QString username){

    QFile file("Users.txt");
    Header* header;

    if (file.open(QFile::ReadOnly)) {

        QJsonDocument document = QJsonDocument().fromJson(file.readAll());
        QJsonObject rootObject = document.object();

        QJsonObject userObject = rootObject.find(username).value().toObject();
        QJsonObject userGameObject = userObject.find(game).value().toObject();
        QJsonObject stateObject = userGameObject.find("State").value().toObject();

        if(game == Game1::name){

            /// initializing according to previous metrics
            SpongeBob* player = new SpongeBob(stateObject.find("cleanliness").value().toInt(),
                                              stateObject.find("immunity").value().toInt(),
                                              stateObject.find("lives").value().toInt(),
                                              stateObject.find("score").value().toInt(),
                                              QPoint(stateObject.find("x").value().toInt(),stateObject.find("y").value().toInt()),
                                              game);

            /// initializing according to previous metrics
            header = new Header(player,
                                stateObject.find("difficulty").value().toInt(),
                                username,
                                game,
                                stateObject.find("completed").value().toBool(),
                                stateObject.find("time").value().toInt());

        }else if(game == Game2::name){
            /// initializing according to previous metrics
            SpongeBob* player = new SpongeBob(stateObject.find("cleanliness").value().toInt(),
                                              stateObject.find("immunity").value().toInt(),
                                              stateObject.find("lives").value().toInt(),
                                              stateObject.find("score").value().toInt(),
                                              QPoint(stateObject.find("x").value().toInt(),stateObject.find("y").value().toInt()),
                                              game,
                                              nullptr,
                                              stateObject.find("bombs").value().toInt(),
                                              stateObject.find("requiredBombScore").value().toInt(),
                                              stateObject.find("translation").value().toInt(),
                                              stateObject.find("weapon").value().toString(),
                                              stateObject.find("weaponStrength").value().toInt());

            /// initializing according to previous metrics
            header = new Header(player,
                                stateObject.find("difficulty").value().toInt(),
                                username,
                                game,
                                stateObject.find("completed").value().toBool(),
                                stateObject.find("time").value().toInt(),
                                stateObject.find("healthyItemsFed").value().toInt());
        }

        file.close();
    }
    return header;
}
/// this function is used to get the current level of the user in a specific game
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

/**
 * @brief User::UpgradeUserToLevel
 * @param game
 * @param username
 * @param level
 *
 * this function is called whith a game, a username, and a level.
 * it gets the json object of the user using its username, and then assigns him a higher level on the given game.
 * this allows the user to play the game on a higher level.
 */
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
