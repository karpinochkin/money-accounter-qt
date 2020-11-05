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

Ref<DB::Controllers::QCashAccount> &DB::QDispatcher::CashAccount()
{
    return cashAccount;
}

Ref<DB::Controllers::QCategory> &DB::QDispatcher::Category()
{
    return category;
}

void DB::QDispatcher::createControllers()
{
    cashAccount = CreateRef<Controllers::QCashAccount>(db, this);
    category = CreateRef<Controllers::QCategory>(db, this);
}

void DB::QDispatcher::fillDB()
{
    QVector<Ref<DefaultFillers::QFillerBase>> fillers;
    fillers.push_back(CreateRef<DefaultFillers::QCurrencyFiller>(cashAccount->currencyCntrl));
    fillers.push_back(CreateRef<DefaultFillers::QIconFiller>(cashAccount->iconCntrl));
    fillers.push_back(CreateRef<DefaultFillers::QCashAccountTypeFiller>(cashAccount->cashAccCategoryCntrl));
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



