#ifndef DBDISPATCHER_H
#define DBDISPATCHER_H

#include "controllers/tablecontrollers.h"
#include "fillers/dbdefaultfillers.h"

namespace DB {

class QDispatcher : public QObject
{

public:
    QDispatcher(const QString &dbName, QObject *parent = nullptr);
    ~QDispatcher();

    Controllers::QCashAccount& CashAccount();
    Controllers::QCategory& Category();
    Controllers::QTransaction& Transaction();

private:
    QSqlDatabase db;
    Ref<Controllers::QCurrency> currency;
    Ref<Controllers::QIcon> icon;
    Ref<Controllers::QCashAccountType> cashAccountType;
    Ref<Controllers::QCashAccount> cashAccount;
    Ref<Controllers::QCategory> category;
    Ref<Controllers::QTransaction> transaction;

    void createControllers();
    void fillDB();
    void closeDB();
};

}

#endif // DBDISPATCHER_H
