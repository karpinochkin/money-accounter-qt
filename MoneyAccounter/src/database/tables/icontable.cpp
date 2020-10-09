#include "icontable.h"

namespace DB::Tables {

QIcon::QIcon(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void QIcon::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + Data::Icon::tableDB() + " ("
            + Data::Icon::idColumnDB() + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
            + Data::Icon::pathColumnDB() + " STRING UNIQUE NOT NULL DEFAULT defaultpath);";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("QIcon::CreateTable() : query error");
    }
    qDebug() << Data::Icon::tableDB() + " is created";
}

void QIcon::Add(const Models::Icon &model)
{
    QString text = "INSERT OR IGNORE INTO "
            + Data::Icon::tableDB() + " ("
            + Data::Icon::idColumnDB() + ", "
            + Data::Icon::pathColumnDB() + " "
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + model.path + "');";

    auto [query, result] = MakeQuery(text);

            if(!result) {
        throw ExceptionDB("QIcon::Add : query error");
    }
}

Models::Icon QIcon::Get(uint id)
{
    QString text = "SELECT "
            + Data::Icon::idColumnDB() + ", "
            + Data::Icon::pathColumnDB() + " "
            + " FROM "
            + Data::Icon::tableDB()
            + " WHERE "
            + Data::Icon::idColumnDB() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("QIcon::Get : query error");
    }

    Models::Icon output;
    if(query.get()->next()) {
        output = getModelFromQuery(query.get());
    }

    return output;
}

Icons QIcon::GetAll()
{
    QString text = "SELECT "
            + Data::Icon::idColumnDB() + ", "
            + Data::Icon::pathColumnDB() + " "
            + " FROM "
            + Data::Icon::tableDB() + ";";

    auto [query, result] = MakeQuery(text);;

            if (!result) {
        throw ExceptionDB("QIcon::GetAll() : query error");
    }

    Icons output;
    while (query.get()->next()) {
        output.push_back(getModelFromQuery(query.get()));
    }

    return output;
}

Models::Icon QIcon::getModelFromQuery(QSqlQuery *query)
{
    return Models::Icon { query->value(0).toUInt(),
                query->value(1).toString()
    };
}

}
