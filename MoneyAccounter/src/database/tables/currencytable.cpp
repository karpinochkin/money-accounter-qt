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

    this->MakeQuery(text);
    qDebug() << DataCurrency::tableName() + " is created";
}

void QCurrency::Add(const MBase &model)
{
    uint uid = getCorrectID(model, DataCurrency::tableName(), DataCurrency::id());
    //    QString text = "INSERT OR IGNORE INTO "
    QString text = "INSERT INTO "
            + DataCurrency::tableName() + " ("
            + DataCurrency::id() + ", "
            + DataCurrency::name() + ", "
            + DataCurrency::symbol() + " "
            + ") VALUES ('"
            + S_NUM(uid) + "','"
            + static_cast<const MCurrency&>(
                model).name + "','"
            + static_cast<const MCurrency&>(
                model).symbol + "');";

    this->MakeQuery(text);
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
    this->MakeQuery(text);
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

    auto query = MakeQuery(text);
    return QBase::getRow<MCurrency>(query.get());;
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

    auto query = MakeQuery(text);
    return QBase::getAllRows<MCurrency>(query.get());
}
}
