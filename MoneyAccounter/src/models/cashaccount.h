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

    void operator<<(QSqlQuery *query) {
        id = query->value(0).toUInt();
        name = query->value(1).toString();
        description = query->value(2).toString();
        settings.isIncludeDebt = query->value(3).toBool();
        settings.isIncludeRefund = query->value(4).toBool();
        settings.isIncludePurpose = query->value(5).toBool();
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
    CashAccountType type{};

    bool isCorrect() const override {
        return !(id < 1 || name.isEmpty() || !icon.isCorrect()
                 || !currency.isCorrect() || !type.isCorrect());
    }

    void operator<<(QSqlQuery *query) {
        id = query->value(0).toUInt();
        name = query->value(1).toString();
        description = query->value(2).toString();
        icon.id = query->value(3).toUInt();
        color.set(query->value(4).toString());
        currency.id = query->value(5).toUInt();
        balance.setAsDouble(query->value(6).toDouble());
        refund.setAsDouble(query->value(7).toDouble());
        debt.setAsDouble(query->value(8).toDouble());
        purpose.setAsDouble(query->value(9).toDouble());
        settings.displayInExpenses = query->value(10).toBool();
        settings.displayInOverallBalance = query->value(11).toBool();
        type.id = query->value(12).toUInt();
    }
};

}

using MCashAcc = Models::CashAccount;
using MCashAccs = QList<Models::CashAccount>;
using MCashAccType = Models::CashAccountType;
using MCashAccTypes = QList<Models::CashAccountType>;

#endif // CASHACCOUNT_H
