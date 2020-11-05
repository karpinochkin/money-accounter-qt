#ifndef CATEGORYTABLE_H
#define CATEGORYTABLE_H

#include "basetable.h"
#include "../../core/base.h"
#include "../../models/category.h"

namespace DB::Tables {

class Category : public QBase
{
    using CategData = Tables::Data::Category;

public:
    explicit Category(QSqlDatabase &database, QObject *parent = nullptr);
    ~Category() = default;

    void CreateTable() override;
    void Add(const Models::Category& model);
    void Edit(const Models::Category& model);
    Models::Category Get(uint id);
    QList<Models::Category> GetAll();
    void Remove(uint id);

private:
    inline Models::Category getModelFromQuery(QSqlQuery *query);
};
}

#endif // CATEGORYTABLE_H
