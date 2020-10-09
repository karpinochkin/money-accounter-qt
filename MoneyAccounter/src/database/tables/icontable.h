#ifndef ICONTABLE_H
#define ICONTABLE_H

#include "basetable.h"
#include "../../core/iconsnames.h"
#include "../../core/base.h"

namespace DB::Tables {

class QIcon : public QBase
{
public:
    explicit QIcon(QSqlDatabase &database, QObject *parent = nullptr);
    ~QIcon() = default;

    void CreateTable() override;
    void Add(const Models::Icon& model);
    Models::Icon Get(uint id);
    Icons GetAll();

private:
    inline Models::Icon getModelFromQuery(QSqlQuery *query);
};

}

#endif // ICONTABLE_H
