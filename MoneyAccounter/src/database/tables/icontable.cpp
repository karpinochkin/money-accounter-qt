#include "icontable.h"

namespace DB::Tables {

QIcon::QIcon(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void QIcon::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + DataIcon::tableName() + " ("
            + DataIcon::id() + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL CHECK("
                                       + DataIcon::id() + " > 0),"
            + DataIcon::path() + " STRING UNIQUE NOT NULL CHECK("
                                         + DataIcon::path() + " != '') DEFAULT defaultpath);";

    this->MakeQuery(text);
    qDebug() << DataIcon::tableName() + " is created";
}

void QIcon::Add(const MBase &model)
{
    uint uid = getCorrectID(model, DataIcon::tableName(), DataIcon::id());
    QString text = "INSERT INTO "
            + DataIcon::tableName() + " ("
            + DataIcon::id() + ", "
            + DataIcon::path() + " "
            + ") VALUES ('"
            + S_NUM(uid) + "','"
            + static_cast<const MIcon&>(model).path + "');";

    this->MakeQuery(text);
}

Ref<MBase> QIcon::Get(uint id)
{
    QString text = "SELECT "
            + DataIcon::id() + ", "
            + DataIcon::path() + " "
            + " FROM "
            + DataIcon::tableName()
            + " WHERE "
            + DataIcon::id() + " = '"
            + S_NUM(id) + "';";

    auto query = MakeQuery(text);
    return QBase::getRow<MIcon>(query.get());;
}

void QIcon::Remove(uint id)
{
    QBase::removeRow(id, DataIcon::tableName(), DataIcon::id());
}

QVariantList QIcon::GetAll()
{
    QString text = "SELECT "
            + DataIcon::id() + ", "
            + DataIcon::path() + " "
            + " FROM "
            + DataIcon::tableName() + ";";

    auto query = MakeQuery(text);
    return QBase::getAllRows<MIcon>(query.get());
}

void QIcon::Edit(const MBase &model)
{
    QString text = "UPDATE "
            + DataIcon::tableName()
            + " SET "
            + DataIcon::path() + " = '" + static_cast<const MIcon&>(model).path + "' "
            + " WHERE "
            + DataIcon::id() + " = '" + S_NUM(model.id) + "';";

    this->MakeQuery(text);
}

}
