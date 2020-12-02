#include "transactiontable.h"

DB::Tables::Transaction::Transaction(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void DB::Tables::Transaction::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + DataTransact::tableName() + " ("
            + DataTransact::id()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
            + DataTransact::name()
            + " STRING NOT NULL "
            + "CHECK (" + DataTransact::name() + " != ''),"
            + DataTransact::descrpiption()
            + " STRING,"
            + DataTransact::datetime()
            + " DATETIME NOT NULL,"
            + DataTransact::sum()
            + "  DECIMAL DEFAULT (0),"
            + DataTransact::idCashAccount()
            + " INTEGER REFERENCES "
            + Data::CashAccount::tableName() + " ("
            + Data::CashAccount::id()
            + ")  ON DELETE SET DEFAULT ON UPDATE CASCADE NOT NULL "
            + "CHECK (" + DataTransact::idCashAccount() + " > 0) DEFAULT(1),"
            + DataTransact::idCategory()
            + " INTEGER REFERENCES "
            + Data::Category::tableName() + " ("
            + Data::Category::id()
            + ")  ON DELETE SET DEFAULT ON UPDATE CASCADE NOT NULL "
            + "CHECK (" + DataTransact::idCategory() + " > 0) DEFAULT(1));";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("DataTransact::CreateTable() : query error");
    }
    qDebug() << DataTransact::tableName() + " is created";
}

void DB::Tables::Transaction::Add(const MBase &model)
{
    QString text = "INSERT INTO "
            + DataTransact::tableName() + " ("
            + DataTransact::id() + ", "
            + DataTransact::name() + ", "
            + DataTransact::descrpiption() + ", "
            + DataTransact::datetime() + ", "
            + DataTransact::sum() + ", "
            + DataTransact::idCashAccount() + ", "
            + DataTransact::idCategory()
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + static_cast<const MTransact&>
            (model).name + "','"
            + static_cast<const MTransact&>
            (model).description + "','"
            + static_cast<const MTransact&>
            (model).datetime.toString() + "','"
            + S_NUM(static_cast<const MTransact&>
                    (model).sum.getAsDouble()) + "','"
            + S_NUM(static_cast<const MTransact&>
                    (model).cashAccount.id) + "','"
            + S_NUM(static_cast<const MTransact&>
                    (model).category.id) + "');";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Transaction::Add : query error");
    }
}

void DB::Tables::Transaction::Edit(const MBase &model)
{
    QString text = "UPDATE "
            + DataTransact::tableName()
            + " SET "
            + DataTransact::name() + " = '"
            + static_cast<const MTransact&>(
                model).name + "',"
            + DataTransact::descrpiption() + " = '"
            + static_cast<const MTransact&>(
                model).description + "',"
            + DataTransact::datetime() + " = '"
            + static_cast<const MTransact&>(
                model).datetime.toString() + "',"
            + DataTransact::sum() + " = '"
            + S_NUM(static_cast<const MTransact&>(
                        model).sum.getAsDouble()) + "',"
            + DataTransact::idCashAccount() + " = '"
            + S_NUM(static_cast<const MTransact&>(
                        model).cashAccount.id) + "',"
            + DataTransact::idCategory() + " = '"
            + S_NUM(static_cast<const MTransact&>(
                        model).category.id) + "' "
            + " WHERE "
            + DataTransact::id() + " = '" + S_NUM(model.id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Transaction::Edit : query error");
    }
}

Ref<MBase> DB::Tables::Transaction::Get(uint id)
{
    QString text = "SELECT "
            + DataTransact::id() + ","
            + DataTransact::name() + ","
            + DataTransact::descrpiption() + ","
            + DataTransact::datetime() + ","
            + DataTransact::sum() + ","
            + DataTransact::idCashAccount() + ","
            + DataTransact::idCategory()
            + " FROM "
            + DataTransact::tableName()
            + " WHERE "
            + DataTransact::id() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Transaction::Get : query error");
    }

    auto output = CreateRef<MTransact>();
    if(query->next()) {
        *output = getModelFromQuery(query.get());
    }
    return output;
}

void DB::Tables::Transaction::Remove(uint id)
{
    QBase::removeRow(id, DataTransact::tableName(), DataTransact::id());
}

QVariantList DB::Tables::Transaction::GetAll()
{
    QString text = "SELECT "
            + DataTransact::id() + ","
            + DataTransact::name() + ","
            + DataTransact::descrpiption() + ","
            + DataTransact::datetime() + ","
            + DataTransact::sum() + ","
            + DataTransact::idCashAccount() + ","
            + DataTransact::idCategory()
            + " FROM "
            + DataTransact::tableName() + ";";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Transaction::Get All: query error");
    }

    QVariantList output;
    while(query->next()) {
        output.push_back(QVariant::fromValue(getModelFromQuery(query.get())));
    }
    return output;
}

MTransact DB::Tables::Transaction::getModelFromQuery(QSqlQuery *query)
{
    MTransact output;

    output.id = query->value(0).toUInt();
    output.name = query->value(1).toString();
    output.description = query->value(2).toString();
    output.datetime = QDateTime::fromString(query->value(3).toString());
    output.sum.setAsDouble(query->value(4).toDouble());
    output.cashAccount.id = query->value(5).toUInt();
    output.category.id = query->value(6).toUInt();

    return output;
}
