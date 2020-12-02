#include "cashaccouttable.h"

namespace DB::Tables {

CashAccoutType::CashAccoutType(QSqlDatabase &database, QObject *parent)
    : QBase(database, parent)
{

}

void CashAccoutType::CreateTable()
{
    QString text = "CREATE TABLE IF NOT EXISTS "
            + DataCashAccType::tableName() + " ("
            + DataCashAccType::id()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL CHECK("
            + DataCashAccType::id() + " > 0),"
            + DataCashAccType::name()
            + " STRING NOT NULL CHECK ("
            + DataCashAccType::name() + " != ''),"
            + DataCashAccType::description()
            + " STRING,"
            + DataCashAccType::isIncludeDebt()
            + " BOOLEAN NOT NULL CHECK ("
            + DataCashAccType::isIncludeDebt() + " != '') DEFAULT (0),"
            + DataCashAccType::isIncludeRefund()
            + " BOOLEAN NOT NULL CHECK ("
            + DataCashAccType::isIncludeRefund() + " != '') DEFAULT (0),"
            + DataCashAccType::isIncludePurpose()
            + " BOOLEAN NOT NULL CHECK ("
            + DataCashAccType::isIncludePurpose() + " != '') DEFAULT (0));";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("CashAccoutType::CreateTable() : query error");
    }
    qDebug() << DataCashAccType::tableName() + " is created";
}

void CashAccoutType::Add(const MBase &model)
{
    QString text = "INSERT INTO "
            + DataCashAccType::tableName() + " ("
            + DataCashAccType::id() + ", "
            + DataCashAccType::name() + ", "
            + DataCashAccType::description() + ", "
            + DataCashAccType::isIncludeDebt() + ", "
            + DataCashAccType::isIncludeRefund() + ", "
            + DataCashAccType::isIncludePurpose()
            + " ) VALUES ('"
            + S_NUM(model.id) + "','"
            + static_cast<const MCashAccType&>(
                model).name + "','"
            + static_cast<const MCashAccType&>(
                model).description + "','"
            + S_NUM(static_cast<const MCashAccType&>(
                        model).settings.isIncludeDebt) + "','"
            + S_NUM(static_cast<const MCashAccType&>(
                        model).settings.isIncludeRefund) + "','"
            + S_NUM(static_cast<const MCashAccType&>(
                        model).settings.isIncludePurpose) + "');";

    auto [query, result] = MakeQuery(text);

            if(!result) {
        throw ExceptionDB("CashAccoutType::Add : query error");
    }
}

void CashAccoutType::Edit(const MBase &model)
{
    QString text = "UPDATE "
            + DataCashAccType::tableName()
            + " SET "
            + DataCashAccType::name() + " = '"
            + static_cast<const MCashAccType&>(
                model).name + "',"
            + DataCashAccType::description() + " = '"
            + static_cast<const MCashAccType&>(
                model).description + "',"
            + DataCashAccType::isIncludeDebt() + " = '"
            + S_NUM(static_cast<const MCashAccType&>(
                        model).settings.isIncludeDebt) + "',"
            + DataCashAccType::isIncludeRefund() + " = '"
            + S_NUM(static_cast<const MCashAccType&>(
                        model).settings.isIncludeRefund) + "',"
            + DataCashAccType::isIncludePurpose() + " = '"
            + S_NUM(static_cast<const MCashAccType&>(
                        model).settings.isIncludePurpose) + "' "
            + " WHERE "
            + DataCashAccType::id() + " = '" + S_NUM(model.id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Edit : query error");
    }
}

Ref<MBase> CashAccoutType::Get(uint id)
{
    QString text = "SELECT "
            + DataCashAccType::id() + ", "
            + DataCashAccType::name() + ", "
            + DataCashAccType::description() + ", "
            + DataCashAccType::isIncludeDebt() + ", "
            + DataCashAccType::isIncludeRefund() + ", "
            + DataCashAccType::isIncludePurpose() + " "
            + " FROM "
            + DataCashAccType::tableName()
            + " WHERE "
            + DataCashAccType::id() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("CashAccoutType::Get : query error");
    }

    auto output = CreateRef<MCashAccType>();
    if (query->next()) {
        *output = getModelFromQuery(query.get());
    }

    return output;
}

void CashAccoutType::Remove(uint id)
{
    QBase::removeRow(id, DataCashAccType::tableName(), DataCashAccType::id());
}

QVariantList CashAccoutType::GetAll()
{
    QString text = "SELECT "
            + DataCashAccType::id() + ", "
            + DataCashAccType::name() + ", "
            + DataCashAccType::description() + ", "
            + DataCashAccType::isIncludeDebt() + ", "
            + DataCashAccType::isIncludeRefund() + ", "
            + DataCashAccType::isIncludePurpose() + " "
            + " FROM "
            + DataCashAccType::tableName() + ";";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("CashAccoutType::GetAll : query error");
    }

    QVariantList output;
    while (query->next()) {
        output.push_back(QVariant::fromValue(getModelFromQuery(query.get())));
    }

    return output;
}

MCashAccType CashAccoutType::getModelFromQuery(QSqlQuery *query)
{
    MCashAccType category;

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
            + DataCashAcc::tableName() + " ("
            + DataCashAcc::id()
            + " INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL CHECK("
            + DataCashAcc::id() + " > 0),"
            + DataCashAcc::name()
            + " STRING NOT NULL CHECK("
            + DataCashAcc::name() + " != ''),"
            + DataCashAcc::description()
            + " STRING DEFAULT(''),"
            + DataCashAcc::idIcon()
            + "  INTEGER REFERENCES "
            + DataCashAccType::tableName() + " ("
            + DataCashAccType::id()
            + ") ON DELETE SET DEFAULT ON UPDATE CASCADE NOT NULL CHECK("
            + DataCashAcc::idIcon() + " > 0) DEFAULT(1),"
            + DataCashAcc::color()
            + " STRING DEFAULT ('#000000'),"
            + DataCashAcc::idCurrency()
            + " INTEGER REFERENCES "
            + Data::Currency::tableName() + " ("
            + Data::Currency::id()
            + ") ON DELETE SET DEFAULT ON UPDATE CASCADE NOT NULL CHECK("
            + DataCashAcc::idCurrency() + " > 0) DEFAULT(1),"
            + DataCashAcc::balance()
            + " DECIMAL NOT NULL,"
            + DataCashAcc::refund()
            + " DECIMAL DEFAULT (0),"
            + DataCashAcc::debt()
            + " DECIMAL DEFAULT (0),"
            + DataCashAcc::purpose()
            + " DECIMAL DEFAULT (0),"
            + DataCashAcc::displayInExpenses()
            + " BOOLEAN NOT NULL DEFAULT (0),"
            + DataCashAcc::displayInOverallBalance()
            + " BOOLEAN NOT NULL DEFAULT (0),"
            + DataCashAcc::idCashAccountType()
            + " INTEGER REFERENCES "
            + DataCashAccType::tableName() + " ("
            + DataCashAccType::id()
            + ") ON DELETE SET DEFAULT ON UPDATE CASCADE NOT NULL CHECK("
            + DataCashAcc::idCashAccountType() + " > 0) DEFAULT(1));";

    auto [query, result] = MakeQuery(text);
            if (!result) {
        throw ExceptionDB("CashAccount::CreateTable() : query error");
    }
    qDebug() << DataCashAcc::tableName() + " is created";
}

void CashAccount::Add(const MBase &model)
{
    //    QString text = "INSERT OR IGNORE INTO "
    QString text = "INSERT INTO "
            + DataCashAcc::tableName() + " ("
            + DataCashAcc::id() + ", "
            + DataCashAcc::name() + ", "
            + DataCashAcc::description() + ", "
            + DataCashAcc::idIcon() + ", "
            + DataCashAcc::color() + ", "
            + DataCashAcc::idCurrency() + ", "
            + DataCashAcc::balance() + ", "
            + DataCashAcc::refund() + ", "
            + DataCashAcc::debt() + ", "
            + DataCashAcc::purpose() + ", "
            + DataCashAcc::displayInExpenses() + ", "
            + DataCashAcc::displayInOverallBalance() + ", "
            + DataCashAcc::idCashAccountType()
            + ") VALUES ('"
            + S_NUM(model.id) + "','"
            + static_cast<const MCashAcc&>(
                model).name + "','"
            + static_cast<const MCashAcc&>(
                model).description + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).icon.id) + "','"
            + static_cast<const MCashAcc&>(
                model).color.hex() + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).currency.id) + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).balance.getAsDouble()) + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).refund.getAsDouble()) + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).debt.getAsDouble()) + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).purpose.getAsDouble()) + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).settings.displayInExpenses) + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).settings.displayInOverallBalance) + "','"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).type.id) + "');";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Add : query error");
    }
}

void CashAccount::Edit(const MBase &model)
{
    QString text = "UPDATE "
            + DataCashAcc::tableName()
            + " SET "
            + DataCashAcc::name() + " = '"
            + static_cast<const MCashAcc&>(
                model).name + "',"
            + DataCashAcc::description() + " = '"
            + static_cast<const MCashAcc&>(
                model).description + "',"
            + DataCashAcc::idIcon() + " = '"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).icon.id) + "',"
            + DataCashAcc::color() + " = '"
            + static_cast<const MCashAcc&>(
                model).color.hex() + "',"
            + DataCashAcc::idCurrency() + " = '"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).currency.id) + "',"
            + DataCashAcc::balance() + " = '"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).balance.getAsDouble()) + "',"
            + DataCashAcc::refund() + " = '"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).refund.getAsDouble()) + "',"
            + DataCashAcc::debt() + " = '"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).debt.getAsDouble()) + "',"
            + DataCashAcc::purpose() + " = '"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).purpose.getAsDouble()) + "',"
            + DataCashAcc::displayInExpenses()
            + " = '" + S_NUM(static_cast<const MCashAcc&>(
                                 model).settings.displayInExpenses) + "',"
            + DataCashAcc::displayInOverallBalance() + " = '"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).settings.displayInOverallBalance) + "',"
            + DataCashAcc::idCashAccountType() + " = '"
            + S_NUM(static_cast<const MCashAcc&>(
                        model).type.id) + "' "
            + " WHERE "
            + DataCashAcc::id() + " = '" + S_NUM(model.id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Edit : query error");
    }

}

Ref<MBase> CashAccount::Get(uint id)
{
    QString text = "SELECT "
            + DataCashAcc::id() + ","
            + DataCashAcc::name() + ","
            + DataCashAcc::description() + ", "
            + DataCashAcc::idIcon() + ","
            + DataCashAcc::color() + ","
            + DataCashAcc::idCurrency() + ","
            + DataCashAcc::balance() + ","
            + DataCashAcc::refund() + ","
            + DataCashAcc::debt() + ","
            + DataCashAcc::purpose() + ","
            + DataCashAcc::displayInExpenses() + ","
            + DataCashAcc::displayInOverallBalance() + ","
            + DataCashAcc::idCashAccountType() +
            + " FROM "
            + DataCashAcc::tableName()
            + " WHERE "
            + DataCashAcc::id() + " = '"
            + S_NUM(id) + "';";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Get : query error");
    }

    auto output = CreateRef<MCashAcc>();
    if(query->next()) {
        *output = getModelFromQuery(query.get());
    }
    return output;

}

void CashAccount::Remove(uint id)
{
    QBase::removeRow(id, DataCashAcc::tableName(), DataCashAcc::id());
}

QVariantList CashAccount::GetAll()
{
    QString text = "SELECT "
            + DataCashAcc::id() + ","
            + DataCashAcc::name() + ","
            + DataCashAcc::description() + ", "
            + DataCashAcc::idIcon() + ","
            + DataCashAcc::color() + ","
            + DataCashAcc::idCurrency() + ","
            + DataCashAcc::balance() + ","
            + DataCashAcc::refund() + ","
            + DataCashAcc::debt() + ","
            + DataCashAcc::purpose() + ","
            + DataCashAcc::displayInExpenses() + ","
            + DataCashAcc::displayInOverallBalance() + ","
            + DataCashAcc::idCashAccountType() +
            + " FROM "
            + DataCashAcc::tableName() + ";";

    auto [query, result] = MakeQuery(text);

            if (!result) {
        throw ExceptionDB("CashAccount::Get All: query error");
    }

    QVariantList output;
    while(query->next()) {
        output.push_back(QVariant::fromValue(getModelFromQuery(query.get())));
    }
    return output;
}

MCashAcc CashAccount::getModelFromQuery(QSqlQuery *query)
{
    MCashAcc cashAcc;

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
    cashAcc.type.id = query->value(12).toUInt();

    return cashAcc;
}

}
