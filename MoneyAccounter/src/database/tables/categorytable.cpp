#include "categorytable.h"

namespace DB::Tables {

Category::Category(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void Category::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + CategData::tableDB() + " ("
            + CategData::idColumnDB()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
            + CategData::nameColumnDB()
            + " STRING NOT NULL,"
            + CategData::descriptionColumnDB()
            + " STRING,"
            + CategData::colorColumnDB()
            + " STRING DEFAULT ('#000000'),"
            + CategData::idCurrencyColumnDB()
            + " INTEGER REFERENCES "
            + Data::Currency::tableDB() + " ("
            + Data::Currency::idColumnDB()
            + ") NOT NULL,"
            + CategData::idIconColumnDB()
            + " INTEGER REFERENCES "
            + Data::Icon::tableDB() + " ("
            + Data::Icon::idColumnDB()
            + ") NOT NULL);";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("Category::CreateTable() : query error");
    }
    qDebug() << CategData::tableDB() + " is created";
}

void Category::Add(const Models::Category &model)
{
    QString text = "INSERT OR IGNORE INTO "
            + CategData::tableDB() + " ("
            + CategData::idColumnDB() + ","
            + CategData::nameColumnDB() + ","
            + CategData::descriptionColumnDB() + ","
            + CategData::idCurrencyColumnDB() + ","
            + CategData::idIconColumnDB() + ","
            + CategData::colorColumnDB()
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + model.name + "','"
            + model.description + "','"
            + S_NUM(model.currency.id) + "','"
            + S_NUM(model.icon.id) + "','"
            + model.color.hex() + "');";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Add : query error");
    }
}

void Category::Edit(const Models::Category &model)
{
    QString text = "UPDATE "
            + CategData::tableDB()
            + " SET "
            + CategData::nameColumnDB() + " = '" + model.name + "',"
            + CategData::descriptionColumnDB() + " = '" + model.description + "',"
            + CategData::idCurrencyColumnDB() + " = '" + S_NUM(model.currency.id) + "',"
            + CategData::idIconColumnDB() + " = '" + S_NUM(model.icon.id) + "',"
            + CategData::colorColumnDB() + " = '" + model.color.hex() + "' "
            + " WHERE "
            + CategData::idColumnDB() + " = '" + S_NUM(model.id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Edit : query error");
    }
}

Models::Category Category::Get(uint id)
{
    QString text = "SELECT "
            + CategData::idColumnDB() + ","
            + CategData::nameColumnDB() + ","
            + CategData::descriptionColumnDB() + ","
            + CategData::idCurrencyColumnDB() + ","
            + CategData::idIconColumnDB() + ","
            + CategData::colorColumnDB() + " "
            + " FROM "
            + CategData::tableDB()
            + " WHERE "
            + CategData::idColumnDB() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Get : query error");
    }

    Models::Category output;
    if(query->next()) {
        output = getModelFromQuery(query.get());
    }
    return output;
}

QList<Models::Category> Category::GetAll()
{
    QString text = "SELECT "
            + CategData::idColumnDB() + ","
            + CategData::nameColumnDB() + ","
            + CategData::descriptionColumnDB() + ","
            + CategData::idCurrencyColumnDB() + ","
            + CategData::idIconColumnDB() + ","
            + CategData::colorColumnDB() + " "
            + " FROM "
            + CategData::tableDB() + ";";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Get All: query error");
    }

    QList<Models::Category> output;
    while(query->next()) {
        output.push_back(getModelFromQuery(query.get()));
    }
    return output;
}

void Category::Remove(uint id)
{
    QString text = "DELETE FROM "
            + CategData::tableDB()
            + " WHERE "
            + CategData::idColumnDB()
            + " = '"
            + S_NUM(id)
            + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Remove: query error");
    }
}

Models::Category Category::getModelFromQuery(QSqlQuery *query)
{
    Models::Category category;

    category.id = query->value(0).toUInt();
    category.name = query->value(1).toString();
    category.description = query->value(2).toString();
    category.currency.id = query->value(3).toUInt();
    category.icon.id = query->value(4).toUInt();
    category.color.set(query->value(5).toString());

    return category;
}

}
