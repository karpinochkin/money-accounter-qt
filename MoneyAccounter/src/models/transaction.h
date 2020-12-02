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
};

}

using MTransact = Models::Transaction;
using MTransactions = QList<Models::Transaction>;

#endif // TRANSACTION_H
