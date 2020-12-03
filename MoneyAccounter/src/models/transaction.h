#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "cashaccount.h"
#include "category.h"
#include <QDateTime>

namespace Models {

class Transaction : public Base {
public:
    QString name;
    QString description;
    CashAccount cashAccount;
    Category category;
    QDateTime datetime;
    Decimal sum;

    bool isCorrect() const override {
        return !(id < 1 || name.isEmpty() || !cashAccount.isCorrect()
                 || !category.isCorrect() || !datetime.isValid());
    }

    void operator<<(QSqlQuery *query) {
        id = query->value(0).toUInt();
        name = query->value(1).toString();
        description = query->value(2).toString();
        datetime = QDateTime::fromString(query->value(3).toString());
        sum.setAsDouble(query->value(4).toDouble());
        cashAccount.id = query->value(5).toUInt();
        category.id = query->value(6).toUInt();
    }
};

}

using MTransact = Models::Transaction;
using MTransactions = QList<Models::Transaction>;

#endif // TRANSACTION_H
