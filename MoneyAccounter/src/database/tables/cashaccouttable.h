#ifndef CASHACCOUTTABLE_H
#define CASHACCOUTTABLE_H

#include "basetable.h"
#include "../../core/base.h"
#include "../../models/cashaccount.h"

namespace DB::Tables {

class CashAccoutType : public QBase
{
public:
    explicit CashAccoutType(QSqlDatabase &database, QObject *parent = nullptr);
    ~CashAccoutType() = default;

    void CreateTable() override;
    void Add(const MBase &model) override;
    void Edit(const MBase &model) override;
    Ref<MBase> Get(uint id) override;
    void Remove(uint id) override;
    QVariantList GetAll() override;

private:
    inline MCashAccType getModelFromQuery(QSqlQuery *query);
};

class CashAccount : public QBase
{
public:
    explicit CashAccount(QSqlDatabase &database, QObject *parent = nullptr);
    ~CashAccount() = default;

    void CreateTable() override;
    void Add(const MBase &model) override;
    void Edit(const MBase &model) override;
    void Remove(uint id) override;
    Ref<MBase> Get(uint id) override;
    QVariantList GetAll() override;

private:
    MCashAcc getModelFromQuery(QSqlQuery *query);
};

}

Q_DECLARE_METATYPE(MCashAccType);
Q_DECLARE_METATYPE(MCashAcc);

#endif // CASHACCOUTTABLE_H
