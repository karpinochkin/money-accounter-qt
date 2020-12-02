#include "currencytable.h"

namespace DB::Tables {

QCurrency::QCurrency(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void QCurrency::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + DataCurrency::tableName() + " ("
            + DataCurrency::id()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL CHECK("
            + DataCurrency::id() + " > 0),"
            + DataCurrency::name()
            + " STRING UNIQUE NOT NULL CHECK("
            + DataCurrency::name() + " != ''),"
            + DataCurrency::symbol()
            + " STRING UNIQUE NOT NULL CHECK("
            + DataCurrency::symbol()
            + " != ''));";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("QCurrency::CreateTable() : query error");
    }
    qDebug() << DataCurrency::tableName() + " is created";
}

void QCurrency::Add(const MBase &model)
{
    //    QString text = "INSERT OR IGNORE INTO "
    QString text = "INSERT INTO "
            + DataCurrency::tableName() + " ("
            + DataCurrency::id() + ", "
            + DataCurrency::name() + ", "
            + DataCurrency::symbol() + " "
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + static_cast<const MCurrency&>(
                model).name + "','"
            + static_cast<const MCurrency&>(
                model).symbol + "');";

    auto [query, result] = MakeQuery(text);

            if(!result) {
        throw ExceptionDB("QCurrency::Add : query error");
    }
}

void QCurrency::Edit(const MBase &model)
{
    QString text = "UPDATE "
            + DataCurrency::tableName()
            + " SET "
            + DataCurrency::name() + " = '"
            + static_cast<const Models::Currency&>(
                model).name + "',"
            + DataCurrency::symbol() + " = '"
            + static_cast<const Models::Currency&>(
                model).symbol + "' "
            + " WHERE "
            + DataCurrency::id() + " = '"
            + S_NUM(model.id) + "';";
    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Edit : query error");
    }
}

Ref<MBase> QCurrency::Get(uint id)
{
    QString text = "SELECT "
            + DataCurrency::id() + ", "
            + DataCurrency::name() + ", "
            + DataCurrency::symbol() + " "
            + " FROM "
            + DataCurrency::tableName()
            + " WHERE "
            + DataCurrency::id() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("QCurrency::Get : query error");
    }

    auto output = CreateRef<MCurrency>();
    if(query->next()) {
        *output = getModelFromQuery(query.get());
    }

    return output;
}

void QCurrency::Remove(uint id)
{
    QBase::removeRow(id, DataCurrency::tableName(), DataCurrency::id());
}

QVariantList QCurrency::GetAll()
{
    QString text = "SELECT "
            + DataCurrency::id() + ", "
            + DataCurrency::name() + ", "
            + DataCurrency::symbol() + " "
            + " FROM "
            + DataCurrency::tableName() + ";";

    auto [query, result] = MakeQuery(text);;

            if (!result) {
        throw ExceptionDB("QCurrency::GetAll() : query error");
    }

    QVariantList output;
    while (query->next()) {
        output.push_back(QVariant::fromValue(getModelFromQuery(query.get())));
    }

    return output;
}

MCurrency QCurrency::getModelFromQuery(QSqlQuery *query)
{
    MCurrency currency{};
    currency.id = query->value(0).toUInt();
    currency.name = query->value(1).toString();
    currency.symbol = query->value(2).toString();

    return currency;
}

}
