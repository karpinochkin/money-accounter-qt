#include "categorytable.h"

namespace DB::Tables {

Category::Category(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void Category::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + DataCategory::tableName() + " ("
            + DataCategory::id()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL CHECK("
            + DataCategory::id() + " > 0),"
            + DataCategory::name()
            + " STRING NOT NULL CHECK("
            + DataCategory::name() + " != ''),"
            + DataCategory::description()
            + " STRING,"
            + DataCategory::color()
            + " STRING DEFAULT ('#000000'),"
            + DataCategory::idCurrency()
            + " INTEGER REFERENCES "
            + Data::Currency::tableName() + " ("
            + Data::Currency::id()
            + ") ON DELETE SET DEFAULT ON UPDATE CASCADE NOT NULL CHECK("
            + DataCategory::idCurrency() + " > 0) DEFAULT(1),"
            + DataCategory::idIcon()
            + " INTEGER REFERENCES "
            + Data::Icon::tableName() + " ("
            + Data::Icon::id()
            + ") ON DELETE SET DEFAULT ON UPDATE CASCADE NOT NULL CHECK("
            + DataCategory::idIcon() + " > 0) DEFAULT(1));";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("Category::CreateTable() : query error");
    }
    qDebug() << DataCategory::tableName() + " is created";
}

void Category::Add(const MBase &model)
{
//    QString text = "INSERT OR IGNORE INTO "
    QString text = "INSERT INTO "
            + DataCategory::tableName() + " ("
            + DataCategory::id() + ","
            + DataCategory::name() + ","
            + DataCategory::description() + ","
            + DataCategory::idCurrency() + ","
            + DataCategory::idIcon() + ","
            + DataCategory::color()
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + static_cast<const MCategory&>(model).name + "','"
            + static_cast<const MCategory&>(model).description + "','"
            + S_NUM(static_cast<const MCategory&>(model).currency.id) + "','"
            + S_NUM(static_cast<const MCategory&>(model).icon.id) + "','"
            + static_cast<const MCategory&>(model).color.hex() + "');";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Add : query error");
    }
}

void Category::Edit(const MBase &model)
{
    QString text = "UPDATE "
            + DataCategory::tableName()
            + " SET "
            + DataCategory::name() + " = '" + static_cast<const MCategory&>(model).name + "',"
            + DataCategory::description() + " = '" + static_cast<const MCategory&>(model).description + "',"
            + DataCategory::idCurrency() + " = '" + S_NUM(static_cast<const MCategory&>(model).currency.id) + "',"
            + DataCategory::idIcon() + " = '" + S_NUM(static_cast<const MCategory&>(model).icon.id) + "',"
            + DataCategory::color() + " = '" + static_cast<const MCategory&>(model).color.hex() + "' "
            + " WHERE "
            + DataCategory::id() + " = '" + S_NUM(model.id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Edit : query error");
    }
}

Ref<MBase> Category::Get(uint id)
{
    QString text = "SELECT "
            + DataCategory::id() + ","
            + DataCategory::name() + ","
            + DataCategory::description() + ","
            + DataCategory::idCurrency() + ","
            + DataCategory::idIcon() + ","
            + DataCategory::color() + " "
            + " FROM "
            + DataCategory::tableName()
            + " WHERE "
            + DataCategory::id() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Get : query error");
    }

    auto output = CreateRef<MCategory>();
    if(query->next()) {
        *output = getModelFromQuery(query.get());
    }
    return output;
}

void Category::Remove(uint id)
{
    QBase::removeRow(id, DataCategory::tableName(), DataCategory::id());
}

QVariantList Category::GetAll()
{
    QString text = "SELECT "
            + DataCategory::id() + ","
            + DataCategory::name() + ","
            + DataCategory::description() + ","
            + DataCategory::idCurrency() + ","
            + DataCategory::idIcon() + ","
            + DataCategory::color() + " "
            + " FROM "
            + DataCategory::tableName() + ";";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("Category::Get All: query error");
    }

    QVariantList output;
    while(query->next()) {
        output.push_back(QVariant::fromValue(getModelFromQuery(query.get())));
    }
    return output;
}

MCategory Category::getModelFromQuery(QSqlQuery *query)
{
    MCategory category;

    category.id = query->value(0).toUInt();
    category.name = query->value(1).toString();
    category.description = query->value(2).toString();
    category.currency.id = query->value(3).toUInt();
    category.icon.id = query->value(4).toUInt();
    category.color.set(query->value(5).toString());

    return category;
}

}
