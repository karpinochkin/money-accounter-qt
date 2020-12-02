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

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("QIcon::CreateTable() : query error");
    }
    qDebug() << DataIcon::tableName() + " is created";
}

void QIcon::Add(const MBase &model)
{
    QString text = "INSERT INTO "
            + DataIcon::tableName() + " ("
            + DataIcon::id() + ", "
            + DataIcon::path() + " "
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + static_cast<const MIcon&>(model).path + "');";

    auto [query, result] = MakeQuery(text);

            if(!result) {
        throw ExceptionDB("QIcon::Add : query error");
    }
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

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("QIcon::Get : query error");
    }

    auto output = CreateRef<MIcon>();
    if(query.get()->next()) {
        *output = getModelFromQuery(query.get());
    }

    return output;
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

    auto [query, result] = MakeQuery(text);;

            if (!result) {
        throw ExceptionDB("QIcon::GetAll() : query error");
    }

    QVariantList output;
    while (query.get()->next()) {
        output.push_back(QVariant::fromValue(getModelFromQuery(query.get())));
    }

    return output;
}

void QIcon::Edit(const MBase &model)
{
    QString text = "UPDATE "
            + DataIcon::tableName()
            + " SET "
            + DataIcon::path() + " = '" + static_cast<const MIcon&>(model).path + "' "
            + " WHERE "
            + DataIcon::id() + " = '" + S_NUM(model.id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("QIcon::Edit : query error");
    }
}
MIcon QIcon::getModelFromQuery(QSqlQuery *query)
{
   MIcon icon;
   icon.id = query->value(0).toUInt();
   icon.path = query->value(1).toString();
   return icon;
}

}
