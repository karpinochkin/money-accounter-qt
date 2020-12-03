#ifndef CATEGORY_H
#define CATEGORY_H

#include "currency.h"
#include "icon.h"
#include "color.h"

namespace Models {

struct Category : public Base {
    QString name;
    QString description;
    Currency currency{};
    Icon icon{};
    Color color;

    bool isCorrect() const override {
        return !(id < 1 || name.isEmpty() || !currency.isCorrect() || !icon.isCorrect());
    }

    void operator<<(QSqlQuery* query) {
        id = query->value(0).toUInt();
        name = query->value(1).toString();
        description = query->value(2).toString();
        currency.id = query->value(3).toUInt();
        icon.id = query->value(4).toUInt();
        color.set(query->value(5).toString());
    }
};

}

using MCategory = Models::Category;
using MCategories = QList<Models::Category>;

#endif // CATEGORY_H
