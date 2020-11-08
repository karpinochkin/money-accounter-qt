#ifndef CASHACCOUNT__H
#define CASHACCOUNT__H

#include "color.h"
#include "currency.h"
#include "icon.h"
#include "../vendor/decimal/include/decimal.h"

namespace Models {

using Decimal = declib::decimal<2>;

struct CashAccountTypeSettings {
    bool isIncludeRefund;
    bool isIncludeDebt;
    bool isIncludePurpose;
};

class CashAccountType : public Base {
public:
    QString name;
    QString description;
    CashAccountTypeSettings settings{};

    bool isCorrect() const override {
        return !(id < 1 || name.isEmpty());
    }

    bool isCorrectDB() const override {
        return isCorrect();
    }
};

struct CashAccountSettings {
    bool displayInOverallBalance;
    bool displayInExpenses;
};

class CashAccount : public Base {
public:
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

    bool isCorrect() const override {
        return !(id < 1 || name.isEmpty() || !icon.isCorrect()
                 || !currency.isCorrect() || !category.isCorrect());
    }

    bool isCorrectDB() const override {
        return !(id < 1 || name.isEmpty() || icon.id < 1
                 || currency.id < 1 || category.id < 1);
    }
};

}

#endif // CASHACCOUNT_H
