#ifndef CURRENCY_H
#define CURRENCY_H

#include "basemodel.h"
#include <QSqlQuery>

namespace Models {

class Currency : public Base {
public:
    QString name;
    QString symbol;

    bool isCorrect() const override {
        return !(id < 1 || name.isEmpty() || symbol.isEmpty());
    }

    void operator<<(QSqlQuery *query) {
        id = query->value(0).toUInt();
        name = query->value(1).toString();
        symbol = query->value(2).toString();
    }
};

}

using MCurrency = Models::Currency;
using MCurrencies = QList<Models::Currency>;

#endif // CURRENCY_H
