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

private:
    QSqlDatabase db;
    Ref<Controllers::QCashAccount> cashAccount;

    void createControllers();
    void fillDB();
    void closeDB();
};

}

#endif // DBDISPATCHER_H
