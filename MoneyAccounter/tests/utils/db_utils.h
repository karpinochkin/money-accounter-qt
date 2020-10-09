#ifndef DB_UTILS_H
#define DB_UTILS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <memory>

QString databaseName = "testing_money_db.db";
auto db = QSqlDatabase::addDatabase("QSQLITE", databaseName);

bool openDB() {
    return db.open();
}

void closeDB() {
    db.close();
}

void removeDB() {
    QSqlDatabase::removeDatabase(databaseName);
}

bool dropDB(){
    auto query = std::make_shared<QSqlQuery>();
    return query->exec("drop database " + databaseName);
}

#endif // DB_UTILS_H
