#include "dbdispatcher.h"

DB::QDispatcher::QDispatcher(const QString &dbName, QObject *parent)
    : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE", dbName);
    db.setDatabaseName(dbName);
    if (!db.open()) {
        throw ExceptionDB("db open error");
    }

    createControllers();
    fillDB();
}

DB::QDispatcher::~QDispatcher()
{
    closeDB();
}

DB::Controllers::QCashAccount &DB::QDispatcher::CashAccount()
{
    return *cashAccount;
}

DB::Controllers::QCategory &DB::QDispatcher::Category()
{
    return *category;
}

DB::Controllers::QTransaction &DB::QDispatcher::Transaction()
{
    return *transaction;
}

void DB::QDispatcher::createControllers()
{
    currency = CreateRef<Controllers::QCurrency>(db, this);
    icon = CreateRef<Controllers::QIcon>(db, this);
    cashAccountType = CreateRef<Controllers::QCashAccountType>(db, this);
    cashAccount = CreateRef<Controllers::QCashAccount>(currency.get(), icon.get(), cashAccountType.get(), db, this);
    category = CreateRef<Controllers::QCategory>(currency.get(), icon.get(), db, this);
    transaction = CreateRef<Controllers::QTransaction>(cashAccount.get(), category.get(), db, this);
}

void DB::QDispatcher::fillDB()
{
    QVector<Ref<DefaultFillers::QFillerBase>> fillers;
    fillers.push_back(CreateRef<DefaultFillers::QCurrencyFiller>(currency));
    fillers.push_back(CreateRef<DefaultFillers::QIconFiller>(icon));
    fillers.push_back(CreateRef<DefaultFillers::QCashAccountTypeFiller>(cashAccountType));
    fillers.push_back(CreateRef<DefaultFillers::QCashAccountFiller>(cashAccount));
    fillers.push_back(CreateRef<DefaultFillers::QCategoryFiller>(category));

    for (auto i : fillers) {
        i->FillByDefault();
    }
}

void DB::QDispatcher::closeDB()
{
    if (db.isOpen()) {
        db.close();
    }
}



