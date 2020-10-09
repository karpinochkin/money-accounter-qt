#ifndef CURRENCYTABLE_H
#define CURRENCYTABLE_H

#include "basetable.h"
#include "../../core/currencynames.h"
#include "../../core/base.h"

namespace DB::Tables {

using SymData = Data::CurrencySymbol;
using Sym = Models::CurrencySymbol;
using Currency = Models::Currency;

///
/// \brief The QCurrencySymbol class - control of currency symbol db table
///
class QCurrencySymbol : public QBase
{
public:
    explicit QCurrencySymbol(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCurrencySymbol() = default;

    void CreateTable() override;
    void Add(const Sym& model);
    Sym Get(uint id);
    Symbols GetByCurrencyID(uint id);
    Symbols GetAll();

private:
    inline Sym getModelFromQuery(QSqlQuery *query);
};

///
/// \brief The QCurrency class - control of currency db table
///
class QCurrency : public QBase
{
public:
    explicit QCurrency(QSqlDatabase &database, QObject *parent = nullptr);
    ~QCurrency() = default;

    void CreateTable() override;
    void Add(const Currency& model);
    Currency Get(uint id);
    Currencies GetAll();

private:
    inline Currency getModelFromQuery(QSqlQuery *query);
};

}

#endif // CURRENCYTABLE_H
