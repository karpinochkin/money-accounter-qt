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

DB::Controllers::QCashAccountType::QCashAccountType(QSqlDatabase &database, QObject *parent)
    : QObject(parent)
{
    cashAccCategory = CreateScope<Tables::CashAccoutType>(database, this);

    if (!CreateTables()) {
        throw ExceptionDB("cash acc category table is not created");
    }
}

bool DB::Controllers::QCashAccountType::CreateTables()
{
    try {
        cashAccCategory->CreateTable();
        return true;
    } catch (const  ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCashAccountType::Add(const Type &model)
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

Type DB::Controllers::QCashAccountType::Get(uint id)
{
    try {
        auto model = cashAccCategory->Get(id);\
        isCategoryCorrect(model);
        return model;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return Type {};
    }
}

Types DB::Controllers::QCashAccountType::GetAll()
{
    try {
        auto models = cashAccCategory->GetAll();
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return Types {};
    }
}

void DB::Controllers::QCashAccountType::isCategoryCorrect(const Type &model) const
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
    cashAccCategoryCntrl = CreateRef<QCashAccountType>(database, this);

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

bool DB::Controllers::QCashAccount::Remove(uint id)
{
    try {
        cashAccTable->Remove(id);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
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

DB::Controllers::QCategory::QCategory(QSqlDatabase &database, QObject *parent)
    : QObject(parent)
{
    currencyCntrl = CreateRef<QCurrency>(database, this);
    iconCntrl = CreateRef<QIcon>(database, this);
    category = CreateScope<Tables::Category>(database, this);

    if (!CreateTables()) {
        throw ExceptionDB("category tables is not created");
    }
}

bool DB::Controllers::QCategory::CreateTables()
{
    try {
        category->CreateTable();
        return true;
    } catch (const  ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCategory::Add(const Models::Category &model)
{
    try {
        isCategoryCorrectForDB(model);
        category->Add(model);

        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCategory::Edit(const Models::Category &model)
{
    try {
        isCategoryCorrectForDB(model);
        category->Edit(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

Models::Category DB::Controllers::QCategory::Get(uint id)
{
    try {
        auto model = category->Get(id);
        model.icon = iconCntrl->Get(model.icon.id);
        model.currency = currencyCntrl->Get(model.currency.id);
        isCategoryCorrect(model);

        return model;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        Models::Category model;
        return model;
    }
}

QList<Models::Category> DB::Controllers::QCategory::GetAll()
{
    try {
        QList<Models::Category> output;

        auto models = category->GetAll();
        for (auto model : models) {
            try {
                model.icon = iconCntrl->Get(model.icon.id);
                model.currency = currencyCntrl->Get(model.currency.id);
                isCategoryCorrect(model);
                output.push_back(model);
            } catch (const ExceptionDB &err) {
                qDebug() << err.what();
            }
        }
        return output;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return QList<Models::Category>{};
    }
}

bool DB::Controllers::QCategory::Remove(uint id)
{
    try {
        category->Remove(id);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

void DB::Controllers::QCategory::isCategoryCorrect(const Models::Category &model)
{
    if (!model.isCorrect()) {
        throw ExceptionDB("QCategory model is not correct");
    }
}

void DB::Controllers::QCategory::isCategoryCorrectForDB(const Models::Category &model)
{
    if (!model.isCorrectTable()) {
        throw ExceptionDB("QCategory db : model is not correct");
    }
}
