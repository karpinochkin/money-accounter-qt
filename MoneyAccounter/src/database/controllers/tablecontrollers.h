#ifndef TABLECONTROLLERS_H
#define TABLECONTROLLERS_H

#include <QObject>
#include "../tables/currencytable.h"
#include "../tables/icontable.h"
#include "../tables/cashaccouttable.h"
#include "../tables/categorytable.h"
#include "../tables/transactiontable.h"

namespace DB::Controllers {

class QController : public QObject {
public:
    ~QController() = default;
protected:
    QController(QSqlDatabase &database, QObject *parent = nullptr) : QObject(parent) {
        Q_UNUSED(database)
    }

    void isModelCorrect(const MBase *model) {
        if (!model->isCorrect()) {
            std::string err = "Controllers : model is not correct |  ";
            err += typeid(model).name();
            throw ExceptionDB(err);
        }
    };
};

///
/// \brief The QCurrencyController class - currency facade
///
class QCurrency : public QController
{
public:
    explicit QCurrency(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCurrency() = default;

    bool CreateTables();
    bool Add(const MCurrency &model);
    bool Edit(const MCurrency &model);
    MCurrency Get(uint id);
    MCurrencies GetAll();

private:
    Scope<Tables::QCurrency> currencyTable;
};

///
/// \brief The QIcon class - icon facade
///
class QIcon : public QController {
public:
    explicit QIcon(QSqlDatabase &database, QObject *parent = nullptr);
    ~QIcon() = default;

    bool CreateTables();
    bool Add(const MIcon &model);
    MIcon Get(uint id);
    MIcons GetAll();

private:
    Scope<Tables::QIcon> iconTable;
};

///
/// \brief The QCashAccountCategory class - cash acc category facade
///
class QCashAccountType : public QController
{
public:
    explicit QCashAccountType(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCashAccountType() = default;

    bool CreateTables();
    bool Add(const MCashAccType &model);
    MCashAccType Get(uint id);
    MCashAccTypes GetAll();

private:
    Scope<Tables::CashAccoutType> cashAccCategory;
};

class QCashAccount : public QController
{
public:
    explicit QCashAccount(QCurrency *currency,
                          QIcon *icon,
                          QCashAccountType *cashAccType,
                          QSqlDatabase &database,
                          QObject *parent = nullptr);
    ~QCashAccount() = default;

    bool CreateTables();
    bool Add(const MCashAcc &model);
    bool Edit(const MCashAcc &model);
    MCashAcc Get(uint id);
    MCashAccs GetAll();
    bool Remove(uint id);

private:
    Scope<Tables::CashAccount> cashAccTable;

    QCurrency *currencyCntrl = nullptr;
    QIcon *iconCntrl = nullptr;
    QCashAccountType *cashAccTypeCntrl = nullptr;
};

class QCategory : public QController
{
public:
    explicit QCategory(QCurrency *currencyCntrl,
                       QIcon *iconCntrl,
                       QSqlDatabase &database,
                       QObject *parent = nullptr);
    ~QCategory() = default;

    bool CreateTables();
    bool Add(const MCategory &model);
    bool Edit(const MCategory &model);
    MCategory Get(uint id);
    MCategories GetAll();
    bool Remove(uint id);

private:
    Scope<Tables::Category> category;

    QCurrency *currencyCntrl = nullptr;
    QIcon *iconCntrl = nullptr;
};

class QTransaction : public QController
{
public:
    explicit QTransaction(QCashAccount* cashAccCntrl,
                          QCategory* categoryCntrl,
                          QSqlDatabase &database,
                          QObject *parent = nullptr);
    ~QTransaction() = default;

    bool CreateTables();
    bool Add(const MTransact &model);
    bool Edit(const MTransact &model);
    MTransact Get(uint id);
    MTransactions GetAll();
    bool Remove(uint id);

private:
    Scope<Tables::Transaction> transaction;

    QCashAccount* cashAccCntrl = nullptr;
    QCategory* categoryCntrl = nullptr;
};

}

#endif // TABLECONTROLLERS_H
