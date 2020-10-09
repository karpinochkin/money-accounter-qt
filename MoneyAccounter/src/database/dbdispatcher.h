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

    Ref<Controllers::QCurrency>& Currency();
    Ref<Controllers::QIcon>& Icon();
    Ref<Controllers::QCashAccountCategory>& CashAccountCategory();

private:
    QSqlDatabase db;
    Ref<Controllers::QCurrency> currency;
    Ref<Controllers::QIcon> icon;
    Ref<Controllers::QCashAccountCategory> cashAccountCategory;

    void createControllers();
    void fillDB();
    void closeDB();
};

}

#endif // DBDISPATCHER_H
