#ifndef CURRENCYTABLE_H
#define CURRENCYTABLE_H

#include "basetable.h"
#include "../../models/currency.h"
#include "../../core/base.h"

namespace DB::Tables {

class QCurrency : public QBase
{
public:
    explicit QCurrency(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCurrency() = default;

    void CreateTable() override;
    void Add(const MBase& model) override;
    void Edit(const MBase &model) override;
    void Remove(uint id) override;
    Ref<MBase> Get(uint id) override;
    QVariantList GetAll() override;

private:
    MCurrency getModelFromQuery(QSqlQuery *query);
};
}

Q_DECLARE_METATYPE(MCurrency);

#endif // CURRENCYTABLE_H
