#ifndef CASHACCOUTTABLE_H
#define CASHACCOUTTABLE_H

#include "basetable.h"
#include "../../core/base.h"
#include "../../core/cashaccountsnames.h"

namespace DB::Tables {

using CategData = Data::CashAccountCategory;
using CashAccData = Data::CashAccount;

class CashAccoutCategory : public QBase
{
public:
    explicit CashAccoutCategory(QSqlDatabase &database, QObject *parent = nullptr);
    ~CashAccoutCategory() = default;

    void CreateTable() override;
    void Add(const Category& model);
    Category Get(uint id);
    Categories GetAll();

private:
    inline Category getModelFromQuery(QSqlQuery *query);
};

class CashAccount : public QBase
{
public:
    explicit CashAccount(QSqlDatabase &database, QObject *parent = nullptr);
    ~CashAccount() = default;

    void CreateTable() override;
    void Add(const CashAcc& model);
    void Edit(const CashAcc& model);
    CashAcc Get(uint id);
    CashAccs GetAll();

private:
    inline CashAcc getModelFromQuery(QSqlQuery *query);
};

}

#endif // CASHACCOUTTABLE_H
