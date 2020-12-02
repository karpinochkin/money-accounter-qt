#include "basetable.h"

namespace DB::Tables {

QBase::QBase(QSqlDatabase &database, QObject *parent)
    : QObject(parent),
      db(database) {
    mutex = new QMutex();
    execQuery("PRAGMA foreign_keys = ON;");
}

void QBase::removeRow(uint id, const QString &tableName, const QString &idColumnName)
{
    QString text = "DELETE FROM "
            + tableName
            + " WHERE "
            + idColumnName
            + " = '"
            + S_NUM(id)
            + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        QString err = tableName + " : remove query error";
        throw ExceptionDB(err.toStdString());
    }
}

QBase::QBase::~QBase()
{
    delete mutex;
}

QueryBool QBase::MakeQuery(const QString &textQuery)
{
    auto [query, result] = execQuery(textQuery);
            if (!result) {
        printTextError(query.get()->lastError().text(), textQuery);
    }

    return std::make_tuple(query, result);
}

QueryBool QBase::MakeQuery(const QString &textQuery,
                                       const QString &bindName,
                                       QVariant bindValue) {
    auto [query, result] = execQuery(textQuery, bindName, bindValue);
            if (!result) {
        printTextError(query.get()->lastError().text(), textQuery);
    }

    return std::make_tuple(query, result);
}

QueryBool QBase::execQuery(const QString &textQuery)
{
    bool result = false;
    auto query = std::make_shared<QSqlQuery>(db);

    mutex->lock();

    try {
        checkDatabaseValid();
        openDatabaseIfNotOpened();
        result = query.get()->exec(textQuery);

    } catch(ExceptionDB& err) {
        qDebug() <<  err.what();
    }

    mutex->unlock();

    return std::make_tuple(query, result);
}

QueryBool QBase::execQuery(const QString &textQuery,
                                       const QString &bindName,
                                       QVariant bindValue) {
    bool result = false;
    auto query = std::make_shared<QSqlQuery>(db);

    mutex->lock();
    try {
        checkDatabaseValid();
        openDatabaseIfNotOpened();

        query.get()->prepare(textQuery);
        query.get()->bindValue(bindName, bindValue);
        result = query.get()->exec();

    } catch(const ExceptionDB& err) {
        qDebug() << err.what();
    }
    mutex->unlock();

    return std::make_tuple(query, result);
}

void QBase::printTextError(const QString &textError, const QString &textQuery)
{
    qDebug()<<"Error query: "<<textError;
    qDebug()<<"textQuery = "<<textQuery;
}

void QBase::checkDatabaseValid() const
{
    if (!db.isValid()) {
        throw ExceptionDB("current database is not valid!");
    }
}

void QBase::openDatabaseIfNotOpened()
{
    if (!db.isOpen()) {
        db.open();
        if (!db.isOpen()) {
            throw ExceptionDB("database is not opened!");
        }
    }
}

}
