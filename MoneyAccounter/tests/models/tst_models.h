#ifndef TST_MODELS_H
#define TST_MODELS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../utils/models_utils.h"

TEST(currency_sym_model_test, isCorrect) {
    Models::CurrencySymbol sym{};
    ASSERT_FALSE(sym.isCorrect());

    sym.id = 0;
    sym.symbol = "";
    sym.idCurrency = 0;
    ASSERT_FALSE(sym.isCorrect());

    sym.id = 1;
    sym.symbol = "";
    sym.idCurrency = 0;
    ASSERT_FALSE(sym.isCorrect());

    sym.id = 1;
    sym.symbol = "";
    sym.idCurrency = -1;
    ASSERT_FALSE(sym.isCorrect());

    sym.id = 1;
    sym.symbol = "";
    sym.idCurrency = 1;
    ASSERT_FALSE(sym.isCorrect());

    sym.id = 1;
    sym.symbol = "2";
    sym.idCurrency = 0;
    ASSERT_FALSE(sym.isCorrect());

    sym.id = 1;
    sym.symbol = "1";
    sym.idCurrency = 1;
    ASSERT_TRUE(sym.isCorrect());
}

TEST(currency_model_test, isCorrect) {
    Models::Currency currency{};
    ASSERT_FALSE(currency.isCorrect());

    currency.id = 18;
    currency.name = "2";
    ASSERT_FALSE(currency.isCorrect());

    currency.id = 0;
    currency.symbols.push_back(Models::CurrencySymbol {1,"2",1});
    ASSERT_FALSE(currency.isCorrect());

    currency.id = 1;
    currency.name = "";
    ASSERT_FALSE(currency.isCorrect());

    currency.name = "33";
    ASSERT_TRUE(currency.isCorrect());
}

TEST(icon_model_test, isCorrect) {
    Models::Icon icon{};
    ASSERT_FALSE(icon.isCorrect());

    icon.id = 1;
    ASSERT_FALSE(icon.isCorrect());

    icon.id = 0;
    icon.path = "path";
    ASSERT_FALSE(icon.isCorrect());

    icon.id = 2;
    ASSERT_TRUE(icon.isCorrect());
}

TEST(cash_account_category, isCorrect) {
    Models::CashAccountCategory category{};
    ASSERT_FALSE(category.isCorrect());

    category.id = 3;
    ASSERT_FALSE(category.isCorrect());

    category.name = "test";
    ASSERT_TRUE(category.isCorrect());

    category.id = 0;
    ASSERT_FALSE(category.isCorrect());

    category.description = "test desc";
    ASSERT_FALSE(category.isCorrect());

    ASSERT_FALSE(category.settings.isIncludeDebt);
    ASSERT_FALSE(category.settings.isIncludeRefund);
    ASSERT_FALSE(category.settings.isIncludePurpose);

    category.id = 1;
    ASSERT_TRUE(category.isCorrect());
}

#endif // TST_MODELS_H
