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
};

}

using MCategory = Models::Category;
using MCategories = QList<Models::Category>;

#endif // CATEGORY_H
