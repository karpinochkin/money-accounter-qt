#ifndef DBDEFAULTFILLERS_H
#define DBDEFAULTFILLERS_H

#include <QObject>
#include "../../utils/qparser.h"
#include "../controllers/tablecontrollers.h"

namespace DB::DefaultFillers {

class QFillerBase {
public:
    QFillerBase() {
        parser = CreateScope<QParser>(nullptr);
    }
    virtual ~QFillerBase() = default;

    void FillByDefault() {
        setDefaultValuesIntoTables();
    }

protected:
    virtual void setDefaultValuesIntoTables() = 0;
    Scope<QParser> parser;

};

class QCurrencyFiller : public QFillerBase {
public:
    QCurrencyFiller(Ref<Controllers::QCurrency> &currency);
    ~QCurrencyFiller() = default;

private:
    Ref<Controllers::QCurrency> m_currency;

    void setDefaultValuesIntoTables() override;
    void addIntoDB(const QList<KIDRow> &kid);
    Symbols getSymbols(const KIDRow &row, uint currencyID, uint &symID);
};

class QIconFiller : public QFillerBase {
public:
    QIconFiller(Ref<Controllers::QIcon> &icon);
    ~QIconFiller() = default;

private:
    Ref<Controllers::QIcon> m_icon;
    void addIntoDB(const QList<KIDRow> &qrc);

    void setDefaultValuesIntoTables() override;
};

class QCashAccountTypeFiller : public QFillerBase {
public:
    QCashAccountTypeFiller(Ref<Controllers::QCashAccountType> &category);
    ~QCashAccountTypeFiller() = default;

private:
    Ref<Controllers::QCashAccountType> m_category;
    void setDefaultValuesIntoTables() override;
    void addIntoDB(const QList<KIDRow> &kid);
};

class QCashAccountFiller : public QFillerBase {
public:
    QCashAccountFiller(Ref<Controllers::QCashAccount> &cashAcc);
    ~QCashAccountFiller() = default;

private:
    Ref<Controllers::QCashAccount> &m_cashAcc;
    void setDefaultValuesIntoTables() override;
    void addIntoDB(const QList<KIDRow> &kid);
};

class QCategoryFiller : public QFillerBase {
public:
    QCategoryFiller(Ref<Controllers::QCategory> &category);
    ~QCategoryFiller() = default;

private:
    Ref<Controllers::QCategory> &m_category;
    void setDefaultValuesIntoTables() override;
    void addIntoDB(const QList<KIDRow> &kid);
};
}

#endif // DBDEFAULTFILLERS_H
