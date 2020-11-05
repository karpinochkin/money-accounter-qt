#ifndef CASHACCOUNT__H
#define CASHACCOUNT__H

#include "color.h"
#include "currency.h"
#include "icon.h"
#include "../vendor/decimal/include/decimal.h"

namespace Models {

using Decimal = declib::decimal<2>;

struct CashAccountCategorySettings {
    bool isIncludeRefund;
    bool isIncludeDebt;
    bool isIncludePurpose;
};

class CashAccountType {
public:
    uint id;
    QString name;
    QString description;
    CashAccountCategorySettings settings{};

    bool isCorrect() const {
        return !(id < 1 || name.isEmpty());
    }
};

struct CashAccountSettings {
    bool displayInOverallBalance;
    bool displayInExpenses;
};

class CashAccount {
public:
    uint id;
    QString name;
    QString description;
    Icon icon {};
    Color color{};
    Currency currency{};
    Decimal balance{};
    Decimal refund{};
    Decimal debt{};
    Decimal purpose {};
    CashAccountSettings settings {};
    CashAccountType category{};

    // checking for model
    bool isCorrect() const {
        return !(id < 1 || name.isEmpty() || !icon.isCorrect()
                 || !currency.isCorrect() || !category.isCorrect());
    }

    // checking model for db table
    bool isCorrectTable() const {
        return !(id < 1 || name.isEmpty() || icon.id < 1
                 || currency.id < 1 || category.id < 1);
    }
};

}

#endif // CASHACCOUNT_H
