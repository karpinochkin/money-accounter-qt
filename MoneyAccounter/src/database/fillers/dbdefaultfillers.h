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
//    QCurrencyFiller(Ref<Controllers::QCurrency> &currency);
    QCurrencyFiller(Controllers::QCurrency &currency);
    ~QCurrencyFiller() = default;

private:
//    Ref<Controllers::QCurrency> m_currency;
    Controllers::QCurrency &m_currency;

    void setDefaultValuesIntoTables() override;
    void addIntoDB(const QList<KIDRow> &kid);
};

class QIconFiller : public QFillerBase {
public:
    QIconFiller(Controllers::QIcon &icon);
    ~QIconFiller() = default;

private:
    Controllers::QIcon &m_icon;
    void addIntoDB(const QList<KIDRow> &qrc);

    void setDefaultValuesIntoTables() override;
};

class QCashAccountTypeFiller : public QFillerBase {
public:
    QCashAccountTypeFiller(Controllers::QCashAccountType &type);
    ~QCashAccountTypeFiller() = default;

private:
    Controllers::QCashAccountType &m_type;
    void setDefaultValuesIntoTables() override;
    void addIntoDB(const QList<KIDRow> &kid);
};

class QCashAccountFiller : public QFillerBase {
public:
    QCashAccountFiller(Controllers::QCashAccount &cashAcc);
    ~QCashAccountFiller() = default;

private:
    Controllers::QCashAccount &m_cashAcc;
    void setDefaultValuesIntoTables() override;
    void addIntoDB(const QList<KIDRow> &kid);
};

class QCategoryFiller : public QFillerBase {
public:
    QCategoryFiller(Controllers::QCategory &category);
    ~QCategoryFiller() = default;

private:
    Controllers::QCategory &m_category;
    void setDefaultValuesIntoTables() override;
    void addIntoDB(const QList<KIDRow> &kid);
};

}

#endif // DBDEFAULTFILLERS_H
