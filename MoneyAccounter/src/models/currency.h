#ifndef CURRENCY_H
#define CURRENCY_H

#include "basemodel.h"

namespace Models {

class CurrencySymbol : public Base {
public:
    QString symbol;
    uint idCurrency;

    bool isCorrect() const override {
        return !(id < 1 || symbol.isEmpty() || idCurrency < 1);
    }

    bool isCorrectDB() const override {
        return isCorrect();
    }
};

class Currency : public Base {
public:
    QString name;
    QList <CurrencySymbol> symbols;

    bool isCorrect() const override {
        return !(id < 1 || name.isEmpty() || std::empty(symbols));
    }

    bool isCorrectDB() const override {
        return isCorrect();
    }
};

}

#endif // CURRENCY_H
