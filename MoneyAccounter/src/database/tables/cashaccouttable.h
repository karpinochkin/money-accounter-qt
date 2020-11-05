#ifndef CASHACCOUTTABLE_H
#define CASHACCOUTTABLE_H

#include "basetable.h"
#include "../../core/base.h"
#include "../../core/cashaccountsnames.h"

namespace DB::Tables {

using TypeData = Data::CashAccountType;
using CashAccData = Data::CashAccount;

class CashAccoutType : public QBase
{
public:
    explicit CashAccoutType(QSqlDatabase &database, QObject *parent = nullptr);
    ~CashAccoutType() = default;

    void CreateTable() override;
    void Add(const Type& model);
    Type Get(uint id);
    Types GetAll();

private:
    inline Type getModelFromQuery(QSqlQuery *query);
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
    void Remove(uint id);

private:
    inline CashAcc getModelFromQuery(QSqlQuery *query);
};

}

#endif // CASHACCOUTTABLE_H
