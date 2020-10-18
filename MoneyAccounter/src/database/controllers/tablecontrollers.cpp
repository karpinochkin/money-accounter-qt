#include "tablecontrollers.h"

DB::Controllers::QCurrency::QCurrency(QSqlDatabase &database, QObject *parent)
    : QObject(parent)
{
    currencyTable = CreateScope<Tables::QCurrency>(database, this);
    symbolTable = CreateScope<Tables::QCurrencySymbol>(database, this);

    if (!CreateTables()) {
        throw ExceptionDB("currency tables is not created");
    }
}

bool DB::Controllers::QCurrency::CreateTables()
{
    try {
        currencyTable->CreateTable();
        symbolTable->CreateTable();
        return true;
    } catch (const  ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCurrency::Add(const Models::Currency &model)
{
    try {
        isCurrencyCorrect(model);
        currencyTable->Add(model);
        for (auto symbol : model.symbols) {
            symbolTable->Add(symbol);
        }
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

Models::Currency DB::Controllers::QCurrency::Get(uint id)
{
    try {
        auto model = currencyTable->Get(id);
        model.symbols = symbolTable->GetByCurrencyID(id);
        isCurrencyCorrect(model);
        return model;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return Models::Currency {};
    }
}

Currencies DB::Controllers::QCurrency::GetAll()
{
    try {
        Currencies output;

        auto models = currencyTable->GetAll();
        for (auto model : models) {
            try {
                model.symbols = symbolTable->GetByCurrencyID(model.id);
                isCurrencyCorrect(model);
                output.push_back(model);
            } catch (const ExceptionDB &err) {
                qDebug() << err.what();
            }
        }
        return output;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return Currencies {};
    }
}

void DB::Controllers::QCurrency::isCurrencyCorrect(const Models::Currency &model) const
{
    if (!model.isCorrect()) {
        throw ExceptionDB("QCurrency::isCurrencyCorrect : model is not correct");
    }
}

DB::Controllers::QIcon::QIcon(QSqlDatabase &database, QObject *parent)
    : QObject(parent)
{
    iconTable = CreateScope<Tables::QIcon>(database, this);

    if (!CreateTables()) {
        throw ExceptionDB("icon table is not created");
    }
}

bool DB::Controllers::QIcon::CreateTables()
{
    try {
        iconTable->CreateTable();
        return true;
    } catch (const  ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QIcon::Add(const Models::Icon &model)
{
    try {
        isIconCorrect(model);
        iconTable->Add(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

Models::Icon DB::Controllers::QIcon::Get(uint id)
{
    try {
        auto model = iconTable->Get(id);
        isIconCorrect(model);
        return model;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return Models::Icon {};
    }
}

Icons DB::Controllers::QIcon::GetAll()
{
    try {
        auto models = iconTable->GetAll();
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return Icons {};
    }
}

void DB::Controllers::QIcon::isIconCorrect(const Models::Icon &model) const
{
    if (!model.isCorrect()) {
        throw ExceptionDB("QIcon::isIconCorrect : model is not correct");
    }
}

DB::Controllers::QCashAccountCategory::QCashAccountCategory(QSqlDatabase &database, QObject *parent)
    : QObject(parent)
{
    cashAccCategory = CreateScope<Tables::CashAccoutCategory>(database, this);

    if (!CreateTables()) {
        throw ExceptionDB("cash acc category table is not created");
    }
}

bool DB::Controllers::QCashAccountCategory::CreateTables()
{
    try {
        cashAccCategory->CreateTable();
        return true;
    } catch (const  ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCashAccountCategory::Add(const Category &model)
{
    try {
        isCategoryCorrect(model);
        cashAccCategory->Add(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

Category DB::Controllers::QCashAccountCategory::Get(uint id)
{
    try {
        auto model = cashAccCategory->Get(id);\
        isCategoryCorrect(model);
        return model;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return Category {};
    }
}

Categories DB::Controllers::QCashAccountCategory::GetAll()
{
    try {
        auto models = cashAccCategory->GetAll();
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return Categories {};
    }
}

void DB::Controllers::QCashAccountCategory::isCategoryCorrect(const Category &model) const
{
    if (!model.isCorrect()) {
        throw ExceptionDB("QCashAccountCategory::isCategoryCorrect : model is not correct");
    }
}

DB::Controllers::QCashAccount::QCashAccount(QSqlDatabase &database, QObject *parent)
    : QObject(parent)
{
    currencyCntrl = CreateRef<QCurrency>(database, this);
    iconCntrl = CreateRef<QIcon>(database, this);
    cashAccCategoryCntrl = CreateRef<QCashAccountCategory>(database, this);

    cashAccTable = CreateScope<Tables::CashAccount>(database, this);

    if (!CreateTables()) {
        throw ExceptionDB("cash account tables is not created");
    }
}

bool DB::Controllers::QCashAccount::CreateTables()
{
    try {
        cashAccTable->CreateTable();
        return true;
    } catch (const  ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCashAccount::Add(const CashAcc &model)
{
    try {
        isCashAccountCorrectForDB(model);
        cashAccTable->Add(model);

        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCashAccount::Edit(const CashAcc &model)
{
    try {
        isCashAccountCorrectForDB(model);
        cashAccTable->Edit(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

CashAcc DB::Controllers::QCashAccount::Get(uint id)
{
    try {
        auto model = cashAccTable->Get(id);
        qDebug() << model.icon.id << model.currency.id << model.category.id;
        model.icon = iconCntrl->Get(model.icon.id);
        model.currency = currencyCntrl->Get(model.currency.id);
        model.category = cashAccCategoryCntrl->Get(model.category.id);
        isCashAccountCorrect(model);

        return model;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return CashAcc {};
    }
}

CashAccs DB::Controllers::QCashAccount::GetAll()
{
    try {
        CashAccs output;

        auto models = cashAccTable->GetAll();
        for (auto model : models) {
            try {
                model.icon = iconCntrl->Get(model.icon.id);
                model.currency = currencyCntrl->Get(model.currency.id);
                model.category = cashAccCategoryCntrl->Get(model.category.id);
                isCashAccountCorrect(model);
                output.push_back(model);
            } catch (const ExceptionDB &err) {
                qDebug() << err.what();
            }
        }
        return output;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return CashAccs {};
    }
}

void DB::Controllers::QCashAccount::isCashAccountCorrect(const CashAcc &model) const
{
    if (!model.isCorrect()) {
        throw ExceptionDB("QCashAccount::isCashAccountCorrect : model is not correct");
    }
}

void DB::Controllers::QCashAccount::isCashAccountCorrectForDB(const CashAcc &model) const
{
    if (!model.isCorrectTable()) {
        throw ExceptionDB("QCashAccount::isCashAccountCorrectForDB : model is not correct");
    }
}
