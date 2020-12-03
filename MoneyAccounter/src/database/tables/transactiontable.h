#ifndef TRANSACTIONTABLE_H
#define TRANSACTIONTABLE_H

#include "basetable.h"
#include "../../core/base.h"
#include "../../models/transaction.h"

namespace DB::Tables {

class Transaction : public QBase {
public:
    explicit Transaction(QSqlDatabase &database, QObject *parent = nullptr);
    ~Transaction() = default;

    void CreateTable() override;
    void Add(const MBase &model) override;
    void Edit(const MBase &model) override;
    void Remove(uint id) override;
    Ref<MBase> Get(uint id) override;
    QVariantList GetAll() override;
};

}

Q_DECLARE_METATYPE(MTransact);

#endif // TRANSACTIONTABLE_H
