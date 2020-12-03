#ifndef CATEGORYTABLE_H
#define CATEGORYTABLE_H

#include "basetable.h"
#include "../../core/base.h"
#include "../../models/category.h"

namespace DB::Tables {

class Category : public QBase
{
public:
    explicit Category(QSqlDatabase &database, QObject *parent = nullptr);
    ~Category() = default;

    void CreateTable() override;
    void Add(const MBase& model) override;
    void Edit(const MBase &model) override;
    void Remove(uint id) override;
    Ref<MBase> Get(uint id) override;
    QVariantList GetAll() override;
};
}

Q_DECLARE_METATYPE(MCategory);


#endif // CATEGORYTABLE_H
