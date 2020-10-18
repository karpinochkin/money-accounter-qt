#include "dbdefaultfillers.h"

namespace DB::DefaultFillers {

QCurrencyFiller::QCurrencyFiller(Ref<Controllers::QCurrency> &currency)
    : m_currency(currency)
{

}

void QCurrencyFiller::setDefaultValuesIntoTables()
{
    try {
        auto kid = parser->ParseKID("../" + qAppName() + "/data/currency-default.kid");
//        auto kid = parser->ParseKID(":/../data/currency-default.kid");
        addIntoDB(kid);
    } catch (ExceptionParser &err) {
        qDebug() << err.what();
    }
}

void QCurrencyFiller::addIntoDB(const QList<KIDRow> &kid)
{
    uint symId = 1;
    for (auto row : kid) {
        Models::Currency currency;
        currency.id = row.objects.at(0)().toInt();
        currency.name = row.objects.at(1)();
        currency.symbols = getSymbols(row, currency.id, symId);

       m_currency->Add(currency);
    }
}

Symbols QCurrencyFiller::getSymbols(const KIDRow &row, uint currencyID, uint &symID)
{
    Symbols output;

    for (auto symbols : row.array_objects) {
        for (auto sym : symbols) {
            output.push_back(Sym { symID++, sym(), currencyID });
        }
    }
    return output;
}

QIconFiller::QIconFiller(Ref<Controllers::QIcon> &icon)
    : m_icon(icon)
{

}

void QIconFiller::setDefaultValuesIntoTables()
{
    try {
        auto qrc = parser->ParseQRC("../" + qAppName() + "/resources/icon_resources.qrc", "images/icons");

        Models::Icon icon;
        uint id = 1;
        for (auto i : qrc) {
            icon.id = id;
            icon.path = i;
            m_icon->Add(icon);
            ++id;
        }
    } catch (ExceptionParser &err) {
        qDebug() << err.what();
    }
}

QCashAccountCategoryFiller::QCashAccountCategoryFiller(Ref<Controllers::QCashAccountCategory> &category)
 : m_category(category)
{

}

void QCashAccountCategoryFiller::setDefaultValuesIntoTables()
{
    try {
        auto kid = parser->ParseKID("../" + qAppName() + "/data/cash-acc-categ-default.kid");
        addIntoDB(kid);
    } catch (ExceptionParser &err) {
        qDebug() << err.what();
    }
}

void QCashAccountCategoryFiller::addIntoDB(const QList<KIDRow> &kid)
{
    for (auto row : kid) {
        Category category;
        category.id = row.objects.at(0)().toUInt();
        category.name = row.objects.at(1)();
        category.description = row.objects.at(2)();
        category.settings.isIncludeDebt = row.objects.at(3)().toInt();
        category.settings.isIncludeRefund = row.objects.at(4)().toInt();
        category.settings.isIncludePurpose = row.objects.at(5)().toInt();

        m_category->Add(category);
    }
}

QCashAccountFiller::QCashAccountFiller(Ref<Controllers::QCashAccount> &cashAcc)
    : m_cashAcc(cashAcc)
{

}

void QCashAccountFiller::setDefaultValuesIntoTables()
{
    try {
        auto kid = parser->ParseKID("../" + qAppName() + "/data/cash-acc-default.kid");
        addIntoDB(kid);
    } catch (ExceptionParser &err) {
        qDebug() << err.what();
    }
}

void QCashAccountFiller::addIntoDB(const QList<KIDRow> &kid)
{
    for (auto row : kid) {
        CashAcc cashAcc;

        cashAcc.id = row.objects.at(0)().toUInt();
        cashAcc.name = row.objects.at(1)();
        cashAcc.description = row.objects.at(2)();
        cashAcc.icon.id = row.objects.at(3)().toUInt();
        cashAcc.currency.id = row.objects.at(4)().toUInt();
        cashAcc.balance.setAsDouble(row.objects.at(5)().toDouble());
        cashAcc.category.id = row.objects.at(6)().toUInt();

        m_cashAcc->Add(cashAcc);
    }
}

}
