#ifndef TST_CNTRLS_H
#define TST_CNTRLS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../src/database/controllers/tablecontrollers.h"
#include "../../utils/db_utils.h"

namespace DB::Controllers {
auto currency = CreateScope<DB::Controllers::QCurrency>(db);
auto icon = CreateScope<DB::Controllers::QIcon>(db);
auto cashAccCateg = CreateScope<DB::Controllers::QCashAccountCategory>(db);

TEST(controller_start_test, open_db) {
    ASSERT_TRUE(openDB());
}

TEST(currency_controller_test, create_tables) {
    ASSERT_TRUE(currency->CreateTables());
}

TEST(currency_controller_test, add_currency) {
    ASSERT_TRUE(currency->Add(Models::Currency {1, "Доллар США", Symbols {
                                      Sym {1, "$", 1},
                                      Sym {2, "US$", 1},
                                      Sym {3, "USD", 1}
                                  }}));
    ASSERT_TRUE(currency->Add(Models::Currency {2, "Евро", Symbols {
                                      Sym {4, "€", 2},
                                      Sym {5, "EUR", 2}
                                  }}));
}

TEST(currency_controller_test, get_currency) {
    auto model = currency->Get(2);

    ASSERT_TRUE(model.isCorrect());
    ASSERT_EQ(2, model.id);
    ASSERT_EQ("Евро", model.name);

    ASSERT_EQ(2, std::size(model.symbols));
    ASSERT_EQ(4, model.symbols.at(0).id);
    ASSERT_EQ("€", model.symbols.at(0).symbol);
    ASSERT_EQ(2, model.symbols.at(0).idCurrency);

    ASSERT_EQ("EUR", model.symbols.at(1).symbol);
    ASSERT_EQ(5, model.symbols.at(1).id);
    ASSERT_EQ(2, model.symbols.at(1).idCurrency);
}

TEST(currency_controller_test, get_currencies) {
    auto models = currency->GetAll();

    ASSERT_EQ(2, std::size(models));
    ASSERT_TRUE(models.at(0).isCorrect());
    ASSERT_TRUE(models.at(1).isCorrect());

    ASSERT_EQ(2, models.at(1).id);
    ASSERT_EQ("Евро", models.at(1).name);
    ASSERT_EQ(2, std::size(models.at(1).symbols));
    ASSERT_EQ(4, models.at(1).symbols.at(0).id);
    ASSERT_EQ("€", models.at(1).symbols.at(0).symbol);
    ASSERT_EQ(2, models.at(1).symbols.at(0).idCurrency);

    ASSERT_EQ("EUR", models.at(1).symbols.at(1).symbol);
    ASSERT_EQ(5, models.at(1).symbols.at(1).id);
    ASSERT_EQ(2, models.at(1).symbols.at(1).idCurrency);

    ASSERT_EQ(3, std::size(models.at(0).symbols));
    ASSERT_EQ("Доллар США", models.at(0).name);
}

TEST(icon_controller_test, CreateTables) {
    ASSERT_TRUE(icon->CreateTables());
}

TEST(icon_controller_test, Add) {
    ASSERT_TRUE(icon->Add(Models::Icon {77, "77777"}));
    ASSERT_TRUE(icon->Add(Models::Icon {88, "8888888"}));
}

TEST(icon_controller_test, Get) {
    auto m = icon->Get(77);
    ASSERT_TRUE(m.isCorrect());
    ASSERT_EQ(m.id, 77);
    ASSERT_EQ(m.path, "77777");
}

TEST(icon_controller_test, GetAll) {
    auto models = icon->GetAll();

    ASSERT_EQ(2, std::size(models));
    ASSERT_TRUE(models.at(0).isCorrect());
    ASSERT_TRUE(models.at(1).isCorrect());

    ASSERT_EQ(models.at(0).id, 77);
    ASSERT_EQ(models.at(0).path, "77777");

    ASSERT_EQ(models.at(1).id, 88);
    ASSERT_EQ(models.at(1).path, "8888888");
}

TEST(cash_account_category_controller_test, CreateTable) {
    ASSERT_TRUE(cashAccCateg->CreateTables());
}

TEST(cash_account_category_controller_test, Add) {
    Category model_1{};
    ASSERT_FALSE(cashAccCateg->Add(model_1));
    model_1.id = 13;
    ASSERT_FALSE(cashAccCateg->Add(model_1));
    model_1.name = "test";
    model_1.settings.isIncludeDebt = 0;
    model_1.settings.isIncludeRefund = 1;
    model_1.settings.isIncludePurpose = 1;
    model_1.description = "test descr";

    Category model_2{};
    model_2.id = 132;
    model_2.name = "test2";
    ASSERT_TRUE(cashAccCateg->Add(model_1));
    ASSERT_TRUE(cashAccCateg->Add(model_2));
}

TEST(cash_account_category_controller_test, Get) {
    auto m2 = cashAccCateg->Get(132);
    auto m1 = cashAccCateg->Get(13);
    auto m3 = cashAccCateg->Get(3);

    ASSERT_TRUE(m1.isCorrect());
    ASSERT_EQ(m1.id, 13);
    ASSERT_EQ(m1.name, "test");
    ASSERT_EQ(m1.description, "test descr");
    ASSERT_EQ(m1.settings.isIncludeDebt, false);
    ASSERT_EQ(m1.settings.isIncludeRefund, true);
    ASSERT_EQ(m1.settings.isIncludePurpose, true);

    ASSERT_TRUE(m2.isCorrect());
    ASSERT_EQ(m2.id, 132);
    ASSERT_EQ(m2.name, "test2");
    ASSERT_EQ(m2.description, "");
    ASSERT_EQ(m2.settings.isIncludeDebt, false);
    ASSERT_EQ(m2.settings.isIncludeRefund, false);
    ASSERT_EQ(m2.settings.isIncludePurpose, false);

    ASSERT_FALSE(m3.isCorrect());
}

TEST(cash_account_category_controller_test, GetAll) {
    auto list = cashAccCateg->GetAll();
    ASSERT_EQ(std::size(list), 2);

    ASSERT_TRUE(list[0].isCorrect());
    ASSERT_EQ(list[0].id, 13);
    ASSERT_EQ(list[0].name, "test");
    ASSERT_EQ(list[0].description, "test descr");
    ASSERT_EQ(list[0].settings.isIncludeDebt, false);
    ASSERT_EQ(list[0].settings.isIncludeRefund, true);
    ASSERT_EQ(list[0].settings.isIncludePurpose, true);

    ASSERT_TRUE(list[1].isCorrect());
    ASSERT_EQ(list[1].id, 132);
    ASSERT_EQ(list[1].name, "test2");
    ASSERT_EQ(list[1].description, "");
    ASSERT_EQ(list[1].settings.isIncludeDebt, false);
    ASSERT_EQ(list[1].settings.isIncludeRefund, false);
    ASSERT_EQ(list[1].settings.isIncludePurpose, false);
}

TEST(controller_end_test, drop_db) {
    dropDB();
}
}

#endif // TST_CURRENCY_CNTRL_H
