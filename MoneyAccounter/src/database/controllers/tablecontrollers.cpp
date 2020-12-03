#include "tablecontrollers.h"

DB::Controllers::QCurrency::QCurrency(QSqlDatabase &database, QObject *parent)
    : QController(database, parent)
{
    currencyTable = CreateScope<Tables::QCurrency>(database, this);

    if (!CreateTables()) {
        throw ExceptionDB("currency tables is not created");
    }
}

bool DB::Controllers::QCurrency::CreateTables()
{
    try {
        currencyTable->CreateTable();
        return true;
    } catch (const  ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCurrency::Add(const MCurrency &model)
{
    try {
        currencyTable->Add(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCurrency::Edit(const MCurrency &model)
{
    try {
        currencyTable->Edit(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

MCurrency DB::Controllers::QCurrency::Get(uint id)
{
    try {
        auto model = std::dynamic_pointer_cast<MCurrency>(currencyTable->Get(id));
        isModelCorrect(model.get());
        return *(model);
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MCurrency {};
    }
}

MCurrencies DB::Controllers::QCurrency::GetAll()
{
    try {
        MCurrencies models;
        for (auto m : currencyTable->GetAll()) {
            models.push_back(unpack<MCurrency>(m));
        }
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MCurrencies {};
    }
}

DB::Controllers::QIcon::QIcon(QSqlDatabase &database, QObject *parent)
    : QController(database, parent)
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

bool DB::Controllers::QIcon::Add(const MIcon &model)
{
    try {
        iconTable->Add(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

MIcon DB::Controllers::QIcon::Get(uint id)
{
    try {
        auto model = std::dynamic_pointer_cast<MIcon>(iconTable->Get(id));
        isModelCorrect(model.get());
        return *(model);
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MIcon {};
    }
}

MIcons DB::Controllers::QIcon::GetAll()
{
    try {
        MIcons models;
        for (auto m : iconTable->GetAll()) {
            models.push_back(unpack<MIcon>(m));
        }
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MIcons {};
    }
}

DB::Controllers::QCashAccountType::QCashAccountType(QSqlDatabase &database, QObject *parent)
    : QController(database, parent)
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

bool DB::Controllers::QCashAccountType::Add(const MCashAccType &model)
{
    try {
        cashAccCategory->Add(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

MCashAccType DB::Controllers::QCashAccountType::Get(uint id)
{
    try {
        auto model = std::dynamic_pointer_cast<MCashAccType>(cashAccCategory->Get(id));
        isModelCorrect(model.get());
        return *(model);
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MCashAccType {};
    }
}

MCashAccTypes DB::Controllers::QCashAccountType::GetAll()
{
    try {
        MCashAccTypes models;
        for (auto m : cashAccCategory->GetAll()) {
            models.push_back(unpack<MCashAccType>(m));
        }
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MCashAccTypes {};
    }
}

DB::Controllers::QCashAccount::QCashAccount(QCurrency &currency,
                                            QIcon &icon,
                                            QCashAccountType &cashAccType,
                                            QSqlDatabase &database,
                                            QObject *parent)
    : QController(database, parent),
      currencyCntrl(currency),
      iconCntrl(icon),
      cashAccTypeCntrl(cashAccType)
{
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

bool DB::Controllers::QCashAccount::Add(const MCashAcc &model)
{
    try {
        cashAccTable->Add(model);

        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCashAccount::Edit(const MCashAcc &model)
{
    try {
        cashAccTable->Edit(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

MCashAcc DB::Controllers::QCashAccount::Get(uint id)
{
    try {
        auto model = std::dynamic_pointer_cast<MCashAcc>(cashAccTable->Get(id));
        model->icon = iconCntrl.Get(model->icon.id);
        model->currency = currencyCntrl.Get(model->currency.id);
        model->type = cashAccTypeCntrl.Get(model->type.id);
        isModelCorrect(model.get());

        return *(model);
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MCashAcc {};
    }
}

MCashAccs DB::Controllers::QCashAccount::GetAll()
{
    try {
        MCashAccs models;

        for (auto variant : cashAccTable->GetAll()) {
            try {
                auto m = unpack<MCashAcc>(variant);
                m.icon = iconCntrl.Get(m.icon.id);
                m.currency = currencyCntrl.Get(m.currency.id);
                m.type = cashAccTypeCntrl.Get(m.type.id);
                isModelCorrect(&m);
                models.push_back(m);
            } catch (const ExceptionDB &err) {
                qDebug() << err.what();
            }
        }
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MCashAccs {};
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

DB::Controllers::QCategory::QCategory(QCurrency &currencyCntrl, QIcon &iconCntrl, QSqlDatabase &database, QObject *parent)
    : QController(database, parent),
      currencyCntrl(currencyCntrl),
      iconCntrl(iconCntrl)
{
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

bool DB::Controllers::QCategory::Add(const MCategory &model)
{
    try {
        category->Add(model);

        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QCategory::Edit(const MCategory &model)
{
    try {
        category->Edit(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

MCategory DB::Controllers::QCategory::Get(uint id)
{
    try {
        auto model = std::dynamic_pointer_cast<MCategory>(category->Get(id));
        model->icon = iconCntrl.Get(model->icon.id);
        model->currency = currencyCntrl.Get(model->currency.id);
        isModelCorrect(model.get());

        return *(model);
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        MCategory model;
        return model;
    }
}

MCategories DB::Controllers::QCategory::GetAll()
{
    try {
        MCategories models;

        for (auto variant : category->GetAll()) {
            try {
                auto m = unpack<MCategory>(variant);
                m.icon = iconCntrl.Get(m.icon.id);
                m.currency = currencyCntrl.Get(m.currency.id);
                isModelCorrect(&m);
                models.push_back(m);
            } catch (const ExceptionDB &err) {
                qDebug() << err.what();
            }
        }
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MCategories{};
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

DB::Controllers::QTransaction::QTransaction(QCashAccount &cashAccCntrl,
                                            QCategory &categoryCntrl,
                                            QSqlDatabase &database,
                                            QObject *parent)
    : QController(database, parent),
      cashAccCntrl(cashAccCntrl),
      categoryCntrl(categoryCntrl)
{
    transaction = CreateScope<Tables::Transaction>(database, this);

    if (!CreateTables()) {
        throw ExceptionDB("transaction tables is not created");
    }
}

bool DB::Controllers::QTransaction::CreateTables()
{
    try {
        transaction->CreateTable();
        return true;
    } catch (const  ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QTransaction::Add(const MTransact &model)
{
    try {
        transaction->Add(model);

        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

bool DB::Controllers::QTransaction::Edit(const MTransact &model)
{
    try {
        transaction->Edit(model);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}

MTransact DB::Controllers::QTransaction::Get(uint id)
{
    try {
        auto model = std::dynamic_pointer_cast<MTransact>(transaction->Get(id));
        model->cashAccount = cashAccCntrl.Get(model->cashAccount.id);
        model->category = categoryCntrl.Get(model->category.id);
        isModelCorrect(model.get());

        return *(model);
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        MTransact model;
        return model;
    }
}

MTransactions DB::Controllers::QTransaction::GetAll()
{
    try {
        MTransactions models;

        for (auto variant : transaction->GetAll()) {
            try {
                auto m = unpack<MTransact>(variant);
                m.cashAccount = cashAccCntrl.Get(m.cashAccount.id);
                m.category = categoryCntrl.Get(m.category.id);
                isModelCorrect(&m);
                models.push_back(m);
            } catch (const ExceptionDB &err) {
                qDebug() << err.what();
            }
        }
        return models;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return MTransactions{};
    }
}

bool DB::Controllers::QTransaction::Remove(uint id)
{
    try {
        transaction->Remove(id);
        return true;
    } catch (const ExceptionDB &err) {
        qDebug() << err.what();
        return false;
    }
}
