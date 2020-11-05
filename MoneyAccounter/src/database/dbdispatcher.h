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

    Ref<Controllers::QCashAccount>& CashAccount();
    Ref<Controllers::QCategory>& Category();

private:
    QSqlDatabase db;
    Ref<Controllers::QCashAccount> cashAccount;
    Ref<Controllers::QCategory> category;

    void createControllers();
    void fillDB();
    void closeDB();
};

}

#endif // DBDISPATCHER_H
