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

CashAccount::CashAccount(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void CashAccount::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + CashAccData::tableDB() + " ("
            + CashAccData::idColumnDB()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
            + CashAccData::nameColumnDB()
            + " STRING NOT NULL,"
            + CashAccData::descriptionColumnDB()
            + " STRING DEFAULT(''),"
            + CashAccData::idIconColumnDB()
            + "  INTEGER REFERENCES "
            + CategData::tableDB() + " ("
            + CategData::idColumnDB()
            + ") NOT NULL,"
            + CashAccData::colorColumnDB()
            + " STRING DEFAULT ('#000000'),"
            + CashAccData::idCurrencyColumnDB()
            + " INTEGER REFERENCES "
            + Data::Currency::tableDB() + " ("
            + Data::Currency::idColumnDB()
            + ") NOT NULL,"
            + CashAccData::balanceColumnDB()
            + " DECIMAL NOT NULL,"
            + CashAccData::refundColumnDB()
            + " DECIMAL DEFAULT (0),"
            + CashAccData::debtColumnDB()
            + " DECIMAL DEFAULT (0),"
            + CashAccData::purposeColumnDB()
            + " DECIMAL DEFAULT (0),"
            + CashAccData::displayInExpensesColumnDB()
            + " BOOLEAN NOT NULL DEFAULT (0),"
            + CashAccData::displayInOverallBalanceColumnDB()
            + " BOOLEAN NOT NULL DEFAULT (0),"
            + CashAccData::idCashAccountCategoryColumnDB()
            + " INTEGER REFERENCES "
            + CategData::tableDB() + " ("
            + CategData::idColumnDB()
            + ") NOT NULL);";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("CashAccount::CreateTable() : query error");
    }
    qDebug() << CashAccData::tableDB() + " is created";
}

void CashAccount::Add(const CashAcc &model)
{
    QString text = "INSERT OR IGNORE INTO "
            + CashAccData::tableDB() + " ("
            + CashAccData::idColumnDB() + ", "
            + CashAccData::nameColumnDB() + ", "
            + CashAccData::descriptionColumnDB() + ", "
            + CashAccData::idIconColumnDB() + ", "
            + CashAccData::colorColumnDB() + ", "
            + CashAccData::idCurrencyColumnDB() + ", "
            + CashAccData::balanceColumnDB() + ", "
            + CashAccData::refundColumnDB() + ", "
            + CashAccData::debtColumnDB() + ", "
            + CashAccData::purposeColumnDB() + ", "
            + CashAccData::displayInExpensesColumnDB() + ", "
            + CashAccData::displayInOverallBalanceColumnDB() + ", "
            + CashAccData::idCashAccountCategoryColumnDB()
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + model.name + "','"
            + model.description + "','"
            + S_NUM(model.icon.id) + "','"
            + model.color.hex() + "','"
            + S_NUM(model.currency.id) + "','"
            + S_NUM(model.balance.getAsDouble()) + "','"
            + S_NUM(model.refund.getAsDouble()) + "','"
            + S_NUM(model.debt.getAsDouble()) + "','"
            + S_NUM(model.purpose.getAsDouble()) + "','"
            + S_NUM(model.settings.displayInExpenses) + "','"
            + S_NUM(model.settings.displayInOverallBalance) + "','"
            + S_NUM(model.category.id) + "');";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Add : query error");
    }
}

void CashAccount::Edit(const CashAcc &model)
{
    QString text = "UPDATE "
            + CashAccData::tableDB()
            + " SET "
            + CashAccData::nameColumnDB() + " = '" + model.name + "',"
            + CashAccData::descriptionColumnDB() + " = '" + model.description + "',"
            + CashAccData::idIconColumnDB() + " = '" + S_NUM(model.icon.id) + "',"
            + CashAccData::colorColumnDB() + " = '" + model.color.hex() + "',"
            + CashAccData::idCurrencyColumnDB() + " = '" + S_NUM(model.currency.id) + "',"
            + CashAccData::balanceColumnDB() + " = '" + S_NUM(model.balance.getAsDouble()) + "',"
            + CashAccData::refundColumnDB() + " = '" + S_NUM(model.refund.getAsDouble()) + "',"
            + CashAccData::debtColumnDB() + " = '" + S_NUM(model.debt.getAsDouble()) + "',"
            + CashAccData::purposeColumnDB() + " = '" + S_NUM(model.purpose.getAsDouble()) + "',"
            + CashAccData::displayInExpensesColumnDB() + " = '" + S_NUM(model.settings.displayInExpenses) + "',"
            + CashAccData::displayInOverallBalanceColumnDB() + " = '" + S_NUM(model.settings.displayInOverallBalance) + "',"
            + CashAccData::idCashAccountCategoryColumnDB() + " = '" + S_NUM(model.category.id) + "' "
            + " WHERE "
            + CashAccData::idColumnDB() + " = '" + S_NUM(model.id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Edit : query error");
    }

}

CashAcc CashAccount::Get(uint id)
{
    QString text = "SELECT "
            + CashAccData::idColumnDB() + ","
            + CashAccData::nameColumnDB() + ","
            + CashAccData::descriptionColumnDB() + ", "
            + CashAccData::idIconColumnDB() + ","
            + CashAccData::colorColumnDB() + ","
            + CashAccData::idCurrencyColumnDB() + ","
            + CashAccData::balanceColumnDB() + ","
            + CashAccData::refundColumnDB() + ","
            + CashAccData::debtColumnDB() + ","
            + CashAccData::purposeColumnDB() + ","
            + CashAccData::displayInExpensesColumnDB() + ","
            + CashAccData::displayInOverallBalanceColumnDB() + ","
            + CashAccData::idCashAccountCategoryColumnDB() +
            + " FROM "
            + CashAccData::tableDB()
            + " WHERE "
            + CashAccData::idColumnDB() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Get : query error");
    }

    CashAcc output;
    if(query->next()) {
        output = getModelFromQuery(query.get());
    }
    return output;

}

CashAccs CashAccount::GetAll()
{
    QString text = "SELECT "
            + CashAccData::idColumnDB() + ","
            + CashAccData::nameColumnDB() + ","
            + CashAccData::descriptionColumnDB() + ", "
            + CashAccData::idIconColumnDB() + ","
            + CashAccData::colorColumnDB() + ","
            + CashAccData::idCurrencyColumnDB() + ","
            + CashAccData::balanceColumnDB() + ","
            + CashAccData::refundColumnDB() + ","
            + CashAccData::debtColumnDB() + ","
            + CashAccData::purposeColumnDB() + ","
            + CashAccData::displayInExpensesColumnDB() + ","
            + CashAccData::displayInOverallBalanceColumnDB() + ","
            + CashAccData::idCashAccountCategoryColumnDB() +
            + " FROM "
            + CashAccData::tableDB() + ";";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Get All: query error");
    }

    CashAccs output;
    while(query->next()) {
        output.push_back(getModelFromQuery(query.get()));
    }
    return output;
}

void CashAccount::Remove(uint id)
{
    QString text = "DELETE FROM "
            + CashAccData::tableDB()
            + " WHERE "
            + CashAccData::idColumnDB()
            + " = '"
            + S_NUM(id)
            + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Remove: query error");
    }
}

CashAcc CashAccount::getModelFromQuery(QSqlQuery *query)
{
    CashAcc cashAcc;

    cashAcc.id = query->value(0).toUInt();
    cashAcc.name = query->value(1).toString();
    cashAcc.description = query->value(2).toString();
    cashAcc.icon.id = query->value(3).toUInt();
    cashAcc.color.set(query->value(4).toString());
    cashAcc.currency.id = query->value(5).toUInt();
    cashAcc.balance.setAsDouble(query->value(6).toDouble());
    cashAcc.refund.setAsDouble(query->value(7).toDouble());
    cashAcc.debt.setAsDouble(query->value(8).toDouble());
    cashAcc.purpose.setAsDouble(query->value(9).toDouble());
    cashAcc.settings.displayInExpenses = query->value(10).toBool();
    cashAcc.settings.displayInOverallBalance = query->value(11).toBool();
    cashAcc.category.id = query->value(12).toUInt();

    return cashAcc;
}

}
