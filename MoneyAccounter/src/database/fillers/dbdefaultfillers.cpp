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
        currency.id = row.objects.at(0).info.toInt();
        currency.name = row.objects.at(1).info;
        currency.symbols = getSymbols(row, currency.id, symId);

       m_currency->Add(currency);
    }
}

Symbols QCurrencyFiller::getSymbols(const KIDRow &row, uint currencyID, uint &symID)
{
    Symbols output;

    for (auto symbols : row.array_objects) {
        for (auto sym : symbols) {
            output.push_back(Sym { symID++, sym.info, currencyID });
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
        category.id = row.objects.at(0).info.toUInt();
        category.name = row.objects.at(1).info;
        category.description = row.objects.at(2).info;
        category.settings.isIncludeDebt = row.objects.at(3).info.toInt();
        category.settings.isIncludeRefund = row.objects.at(4).info.toInt();
        category.settings.isIncludePurpose = row.objects.at(5).info.toInt();

        m_category->Add(category);
    }
}

}
