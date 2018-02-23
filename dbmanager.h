#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include "user.h"

class DbManager
{
public:
    DbManager();

    bool addUser(User user);
    void printUsers();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
