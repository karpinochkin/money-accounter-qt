#include "currencytable.h"

namespace DB::Tables {

QCurrencySymbol::QCurrencySymbol(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void QCurrencySymbol::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + SymData::tableDB() + " ("
            + SymData::idColumnDB()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
            + SymData::symbolColumnDB()
            + " STRING NOT NULL,"
            + SymData::idCorrencyColumnDB()
            + " INTEGER REFERENCES "
            + Data::Currency::tableDB() + " ("
            + Data::Currency::idColumnDB()
            + ") NOT NULL);";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("QCurrencySymbol::CreateTable() : query error");
    }
    qDebug() << SymData::tableDB() + " is created";
}

void QCurrencySymbol::Add(const Sym &model)
{
    QString text = "INSERT OR IGNORE INTO "
            + SymData::tableDB() + " ("
            + SymData::idColumnDB() + ", "
            + SymData::symbolColumnDB() + ", "
            + SymData::idCorrencyColumnDB() + " "
            +") VALUES ('"
            + S_NUM(model.id) + "','"
            + model.symbol + "','"
            + S_NUM(model.idCurrency) + "');";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("QCurrencySymbol::Add : query error");
    }
}

Sym QCurrencySymbol::Get(uint id)
{
    QString text = "SELECT "
            + SymData::idColumnDB() + ", "
            + SymData::symbolColumnDB() + ", "
            + SymData::idCorrencyColumnDB() + " "
            + " FROM "
            + SymData::tableDB()
            + " WHERE "
            + SymData::idColumnDB() + " = '"
            + S_NUM(id)
            + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("QCurrencySymbol::Get : query error");
    }

    Sym output;
    if(query->next()) {
        output = getModelFromQuery(query.get());
    }
    return output;
}

Symbols QCurrencySymbol::GetByCurrencyID(uint id)
{
    QString text = "SELECT "
            + SymData::idColumnDB() + ", "
            + SymData::symbolColumnDB() + ", "
            + SymData::idCorrencyColumnDB() + " "
            + " FROM "
            + SymData::tableDB()
            + " WHERE "
            + SymData::idCorrencyColumnDB() + " = '"
            + S_NUM(id)
            + "';";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("QCurrencySymbol::GetByCurrencyID : query error");
    }

    Symbols output;
    while (query->next()) {
        output.push_back(getModelFromQuery(query.get()));
    }

    return output;
}

Symbols QCurrencySymbol::GetAll()
{
    QString text = "SELECT "
            + SymData::idColumnDB() + ", "
            + SymData::symbolColumnDB() + ", "
            + SymData::idCorrencyColumnDB() + " "
            + " FROM "
            + SymData::tableDB() + ";";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("QCurrencySymbol::GetAll() : query error");
    }

    Symbols output;
    while (query->next()) {
        output.push_back(getModelFromQuery(query.get()));
    }
    return output;
}

Sym QCurrencySymbol::getModelFromQuery(QSqlQuery *query)
{
    return Sym { query->value(0).toUInt(),
                query->value(1).toString(),
                query->value(2).toUInt()
    };
}

QCurrency::QCurrency(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void QCurrency::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + Data::Currency::tableDB() + " ("
            + Data::Currency::idColumnDB() + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
            + Data::Currency::nameColumnDB() + " STRING UNIQUE NOT NULL);";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("QCurrency::CreateTable() : query error");
    }
    qDebug() << Data::Currency::tableDB() + " is created";
}

void QCurrency::Add(const Currency &model)
{
    QString text = "INSERT OR IGNORE INTO "
            + Data::Currency::tableDB() + " ("
            + Data::Currency::idColumnDB() + ", "
            + Data::Currency::nameColumnDB() + " "
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + model.name + "');";

    auto [query, result] = MakeQuery(text);

            if(!result) {
        throw ExceptionDB("QCurrency::Add : query error");
    }
}

Currency QCurrency::Get(uint id)
{
    QString text = "SELECT "
            + Data::Currency::idColumnDB() + ", "
            + Data::Currency::nameColumnDB() + " "
            + " FROM "
            + Data::Currency::tableDB()
            + " WHERE "
            + Data::Currency::idColumnDB() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("QCurrency::Get : query error");
    }

    Currency output;
    if(query->next()) {
        output = getModelFromQuery(query.get());
    }

    return output;
}

Currencies QCurrency::GetAll()
{
    QString text = "SELECT "
            + Data::Currency::idColumnDB() + ", "
            + Data::Currency::nameColumnDB() + " "
            + " FROM "
            + Data::Currency::tableDB() + ";";

    auto [query, result] = MakeQuery(text);;

            if (!result) {
        throw ExceptionDB("QCurrency::GetAll() : query error");
    }

    Currencies output;
    while (query->next()) {
        output.push_back(getModelFromQuery(query.get()));
    }

    return output;
}

Currency QCurrency::getModelFromQuery(QSqlQuery *query)
{
    return Models::Currency { query->value(0).toUInt(),
                query->value(1).toString(),
                Symbols {}
    };
}

}
