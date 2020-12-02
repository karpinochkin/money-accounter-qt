#ifndef CURRENCY_H
#define CURRENCY_H

#include "basemodel.h"

namespace Models {

class Currency : public Base {
public:
    QString name;
    QString symbol;

    bool isCorrect() const override {
        return !(id < 1 || name.isEmpty() || symbol.isEmpty());
    }
};

}

using MCurrency = Models::Currency;
using MCurrencies = QList<Models::Currency>;

#endif // CURRENCY_H
