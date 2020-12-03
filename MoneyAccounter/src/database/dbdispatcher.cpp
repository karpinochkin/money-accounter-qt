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

DB::Controllers::QCashAccount &DB::QDispatcher::CashAccount() const
{
    return *cashAccount;
}

DB::Controllers::QCategory &DB::QDispatcher::Category() const
{
    return *category;
}

DB::Controllers::QTransaction &DB::QDispatcher::Transaction() const
{
    return *transaction;
}

void DB::QDispatcher::createControllers()
{
    currency = CreateScope<Controllers::QCurrency>(db, this);
    icon = CreateScope<Controllers::QIcon>(db, this);
    cashAccountType = CreateScope<Controllers::QCashAccountType>(db, this);
    cashAccount = CreateScope<Controllers::QCashAccount>(*currency, *icon, *cashAccountType, db, this);
    category = CreateScope<Controllers::QCategory>(*currency, *icon, db, this);
    transaction = CreateScope<Controllers::QTransaction>(*cashAccount, *category, db, this);
}

void DB::QDispatcher::fillDB()
{
    QVector<Ref<DefaultFillers::QFillerBase>> fillers;
    fillers.push_back(CreateRef<DefaultFillers::QCurrencyFiller>(*currency));
    fillers.push_back(CreateRef<DefaultFillers::QIconFiller>(*icon));
    fillers.push_back(CreateRef<DefaultFillers::QCashAccountTypeFiller>(*cashAccountType));
    fillers.push_back(CreateRef<DefaultFillers::QCashAccountFiller>(*cashAccount));
    fillers.push_back(CreateRef<DefaultFillers::QCategoryFiller>(*category));

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



