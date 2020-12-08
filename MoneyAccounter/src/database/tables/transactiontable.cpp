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

    this->MakeQuery(text);
    qDebug() << DataTransact::tableName() + " is created";
}

void DB::Tables::Transaction::Add(const MBase &model)
{
    uint uid = getCorrectID(model, DataTransact::tableName(), DataTransact::id());
    qDebug() << uid;
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
            + S_NUM(uid) + "','"
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

    this->MakeQuery(text);
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

    this->MakeQuery(text);
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

    auto query = MakeQuery(text);
    return QBase::getRow<MTransact>(query.get());;
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

    auto query = MakeQuery(text);
    return QBase::getAllRows<MTransact>(query.get());
}
