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

    Controllers::QCashAccount& CashAccount() const;
    Controllers::QCategory& Category() const;
    Controllers::QTransaction &Transaction() const;

private:
    QSqlDatabase db;
    Scope<Controllers::QCurrency> currency;
    Scope<Controllers::QIcon> icon;
    Scope<Controllers::QCashAccountType> cashAccountType;
    Scope<Controllers::QCashAccount> cashAccount;
    Scope<Controllers::QCategory> category;
    Scope<Controllers::QTransaction> transaction;

    void createControllers();
    void fillDB();
    void closeDB();
};

}

#endif // DBDISPATCHER_H
