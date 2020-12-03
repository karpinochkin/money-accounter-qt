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

    this->MakeQuery(text);
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

    this->MakeQuery(text);
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

    this->MakeQuery(text);
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

    auto query = MakeQuery(text);
    return QBase::getRow<MCashAccType>(query.get());;
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

    auto query = MakeQuery(text);
    return QBase::getAllRows<MCashAccType>(query.get());
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

    auto query = MakeQuery(text);
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

    auto query = MakeQuery(text);
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

    auto query = MakeQuery(text);

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

    auto query = MakeQuery(text);
    return QBase::getRow<MCashAcc>(query.get());

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

    auto query = MakeQuery(text);
    return QBase::getAllRows<MCashAcc>(query.get());
}

}
