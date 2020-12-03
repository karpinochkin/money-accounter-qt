#ifndef ICONTABLE_H
#define ICONTABLE_H

#include "basetable.h"
#include "../../models/icon.h"
#include "../../core/base.h"

namespace DB::Tables {

class QIcon : public QBase
{
public:
    explicit QIcon(QSqlDatabase &database, QObject *parent = nullptr);
    ~QIcon() = default;

    void CreateTable() override;
    void Add(const MBase &model) override;
    void Edit(const MBase &model) override;
    void Remove(uint id) override;
    Ref<MBase> Get(uint id) override;
    QVariantList GetAll() override;
};

}
Q_DECLARE_METATYPE(MIcon);

#endif // ICONTABLE_H
