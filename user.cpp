#include "user.h"

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
        }
        file.close();
        if(didWrite = file.open(QFile::WriteOnly)){
            file.write(document.toJson());
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

    QJsonObject gameObject;
    gameObject["Scores"] ="";

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
