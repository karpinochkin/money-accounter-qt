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

Ref<DB::Controllers::QCurrency> &DB::QDispatcher::Currency()
{
    return currency;
}

Ref<DB::Controllers::QIcon> &DB::QDispatcher::Icon()
{
    return icon;
}

Ref<DB::Controllers::QCashAccountCategory> &DB::QDispatcher::CashAccountCategory()
{
    return cashAccountCategory;
}

void DB::QDispatcher::createControllers()
{
    currency = CreateRef<Controllers::QCurrency>(db, this);
    icon = CreateRef<Controllers::QIcon>(db, this);
    cashAccountCategory = CreateRef<Controllers::QCashAccountCategory>(db, this);
}

void DB::QDispatcher::fillDB()
{
    Scope<DefaultFillers::QFillerBase> filler = CreateScope<DefaultFillers::QCurrencyFiller>(currency);
    filler->FillByDefault();

    filler = CreateScope<DefaultFillers::QIconFiller>(icon);
    filler->FillByDefault();

    filler = CreateScope<DefaultFillers::QCashAccountCategoryFiller>(cashAccountCategory);
    filler->FillByDefault();
}

void DB::QDispatcher::closeDB()
{
    if (db.isOpen()) {
        db.close();
    }
}



