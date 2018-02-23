#include "dbmanager.h"

DbManager::DbManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("game1.db");

    if (!m_db.open())
    {
        qDebug("Error: connection with database fail");
    }
    else
    {
        qDebug("Database: connection ok");
    }
}

bool DbManager::addUser(User user){
    bool success = false;
    // you should check if args are ok first...
    QSqlQuery query;
    query.prepare("INSERT INTO Users(Username,Password,FirstName,LastName,DateOfBirth,Gender,ProfilePicture) VALUES(:Username,:Password,:FirstName,:LastName,:DateOfBirth,:Gender,:ProfilePicture)");

    query.bindValue(":Username", user.username);
    query.bindValue(":Password", user.password);
    query.bindValue(":FirstName", user.firstName);
    query.bindValue(":LastName", user.lastName);
    query.bindValue(":DateOfBirth", user.dateOfBirth);
    query.bindValue(":Gender", user.gender);
    query.bindValue(":ProfilePicture", user.profilePicture);

    if(query.exec())
    {
        success = true;
        qDebug("successfully added user");
    }
    else
    {
        qDebug( query.lastError().text().toLatin1());
    }
    return success;
}

void DbManager::printUsers(){
    QSqlQuery query("SELECT * FROM Users");
    int idName = query.record().indexOf("Username");
    while (query.next())
    {
       QString name = query.value(idName).toString();
       qDebug( name.toLatin1());
    }
}
