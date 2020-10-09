#ifndef CURRENCY_H
#define CURRENCY_H

#include <QList>

namespace Models {

///
/// \brief The CurrencySymbol model
///
class CurrencySymbol {
public:
    uint id;
    QString symbol;
    uint idCurrency;

    bool isCorrect() const {
        return !(id < 1 || symbol.isEmpty() || idCurrency < 1);
    }
};

///
/// \brief The Currency model
///
class Currency {
public:
    uint id;
    QString name;
    QList <CurrencySymbol> symbols;

    bool isCorrect() const {
        return !(id < 1 || name.isEmpty() || std::empty(symbols));
    }
};

}

#endif // CURRENCY_H
