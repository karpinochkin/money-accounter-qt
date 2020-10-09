#include "cashaccouttable.h"

namespace DB::Tables {

CashAccoutCategory::CashAccoutCategory(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void CashAccoutCategory::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + CategData::tableDB() + " ("
            + CategData::idColumnDB()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
            + CategData::nameColumnDB()
            + " STRING NOT NULL,"
            + CategData::descriptionColumnDB()
            + " STRING,"
            + CategData::isIncludeDebtColumnDB()
            + " BOOLEAN NOT NULL DEFAULT (0),"
            + CategData::isIncludeRefundColumnDB()
            + " BOOLEAN NOT NULL DEFAULT (0),"
            + CategData::isIncludePurposeColumnDB()
            + " BOOLEAN NOT NULL DEFAULT (0));";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("CashAccoutCategory::CreateTable() : query error");
    }
    qDebug() << CategData::tableDB() + " is created";
}

void CashAccoutCategory::Add(const Category &model)
{
    QString text = "INSERT OR IGNORE INTO "
            + CategData::tableDB() + " ("
            + CategData::idColumnDB() + ", "
            + CategData::nameColumnDB() + ", "
            + CategData::descriptionColumnDB() + ", "
            + CategData::isIncludeDebtColumnDB() + ", "
            + CategData::isIncludeRefundColumnDB() + ", "
            + CategData::isIncludePurposeColumnDB()
            + " ) VALUES ('"
            + S_NUM(model.id) + "','"
            + model.name + "','"
            + model.description + "','"
            + S_NUM(model.settings.isIncludeDebt) + "','"
            + S_NUM(model.settings.isIncludeRefund) + "','"
            + S_NUM(model.settings.isIncludePurpose) + "');";

    auto [query, result] = MakeQuery(text);

            if(!result) {
        throw ExceptionDB("CashAccoutCategory::Add : query error");
    }
}

Category CashAccoutCategory::Get(uint id)
{
    QString text = "SELECT "
            + CategData::idColumnDB() + ", "
            + CategData::nameColumnDB() + ", "
            + CategData::descriptionColumnDB() + ", "
            + CategData::isIncludeDebtColumnDB() + ", "
            + CategData::isIncludeRefundColumnDB() + ", "
            + CategData::isIncludePurposeColumnDB() + " "
            + " FROM "
            + CategData::tableDB()
            + " WHERE "
            + CategData::idColumnDB() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("CashAccoutCategory::Get : query error");
    }

    Category output;
    if (query->next()) {
        output = getModelFromQuery(query.get());
    }

    return output;
}

Categories CashAccoutCategory::GetAll()
{
    QString text = "SELECT "
            + CategData::idColumnDB() + ", "
            + CategData::nameColumnDB() + ", "
            + CategData::descriptionColumnDB() + ", "
            + CategData::isIncludeDebtColumnDB() + ", "
            + CategData::isIncludeRefundColumnDB() + ", "
            + CategData::isIncludePurposeColumnDB() + " "
            + " FROM "
            + CategData::tableDB() + ";";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("CashAccoutCategory::GetAll : query error");
    }

    Categories output;
    while (query->next()) {
        output.push_back(getModelFromQuery(query.get()));
    }

    return output;
}

Category CashAccoutCategory::getModelFromQuery(QSqlQuery *query)
{
    Category category;

    category.id = query->value(0).toUInt();
    category.name = query->value(1).toString();
    category.description = query->value(2).toString();
    category.settings.isIncludeDebt = query->value(3).toBool();
    category.settings.isIncludeRefund = query->value(4).toBool();
    category.settings.isIncludePurpose = query->value(5).toBool();

    return category;
}

}
