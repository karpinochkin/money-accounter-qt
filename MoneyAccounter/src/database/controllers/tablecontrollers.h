#ifndef TABLECONTROLLERS_H
#define TABLECONTROLLERS_H

#include <QObject>
#include "../tables/currencytable.h"
#include "../tables/icontable.h"
#include "../tables/cashaccouttable.h"
#include "../tables/categorytable.h"

namespace DB {

class QDispatcher;
}

namespace DB::Controllers {

///
/// \brief The QCurrencyController class - currency facade
///
class QCurrency : public QObject {
public:
    explicit QCurrency(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCurrency() = default;

    bool CreateTables();
    bool Add(const Models::Currency &model);
    Models::Currency Get(uint id);
    Currencies GetAll();

private:
    Scope<Tables::QCurrency> currencyTable;
    Scope<Tables::QCurrencySymbol> symbolTable;

    void isCurrencyCorrect(const Models::Currency &model) const;
};

///
/// \brief The QIcon class - icon facade
///
class QIcon : public QObject {
public:
    explicit QIcon(QSqlDatabase &database, QObject *parent = nullptr);
    ~QIcon() = default;

    bool CreateTables();
    bool Add(const Models::Icon &model);
    Models::Icon Get(uint id);
    Icons GetAll();

private:
    Scope<Tables::QIcon> iconTable;

    void isIconCorrect(const Models::Icon &model) const;
};

///
/// \brief The QCashAccountCategory class - cash acc category facade
///
class QCashAccountType : public QObject
{
public:
    explicit QCashAccountType(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCashAccountType() = default;

    bool CreateTables();
    bool Add(const Type &model);
    Type Get(uint id);
    Types GetAll();

private:
    Scope<Tables::CashAccoutType> cashAccCategory;

    void isCategoryCorrect(const Type &model) const;
};

class QCashAccount : public QObject
{
public:
    friend class DB::QDispatcher;

    explicit QCashAccount(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCashAccount() = default;

    bool CreateTables();
    bool Add(const CashAcc &model);
    bool Edit(const CashAcc &model);
    CashAcc Get(uint id);
    CashAccs GetAll();
    bool Remove(uint id);

private:
    Ref<QCurrency> currencyCntrl;
    Ref<QIcon> iconCntrl;
    Ref<QCashAccountType> cashAccCategoryCntrl;

    Scope<Tables::CashAccount> cashAccTable;

    void isCashAccountCorrect(const CashAcc &model) const;
    void isCashAccountCorrectForDB(const CashAcc &model) const;
};

class QCategory : public QObject
{
public:
    explicit QCategory(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCategory() = default;

    bool CreateTables();
    bool Add(const Models::Category& model);
    bool Edit(const Models::Category &model);
    Models::Category Get(uint id);
    QList<Models::Category> GetAll();
    bool Remove(uint id);

private:
    Scope<Tables::Category> category;
    Ref<QCurrency> currencyCntrl;
    Ref<QIcon> iconCntrl;

    void isCategoryCorrect(const Models::Category&);
    void isCategoryCorrectForDB(const Models::Category&);

};

}

#endif // TABLECONTROLLERS_H
