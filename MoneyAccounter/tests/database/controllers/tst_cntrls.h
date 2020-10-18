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
auto cashAcc = CreateScope<DB::Controllers::QCashAccount>(db);

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
    ASSERT_TRUE(icon->Add(Models::Icon {2, "77777"}));
    ASSERT_TRUE(icon->Add(Models::Icon {88, "8888888"}));
}

TEST(icon_controller_test, Get) {
    auto m = icon->Get(2);
    ASSERT_TRUE(m.isCorrect());
    ASSERT_EQ(m.id, 2);
    ASSERT_EQ(m.path, "77777");
}

TEST(icon_controller_test, GetAll) {
    auto models = icon->GetAll();

    ASSERT_EQ(2, std::size(models));
    ASSERT_TRUE(models.at(0).isCorrect());
    ASSERT_TRUE(models.at(1).isCorrect());

    ASSERT_EQ(models.at(0).id, 2);
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
    model_1.id = 2;
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
    auto m1 = cashAccCateg->Get(2);
    auto m3 = cashAccCateg->Get(3);

    ASSERT_TRUE(m1.isCorrect());
    ASSERT_EQ(m1.id, 2);
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
    ASSERT_EQ(list[0].id, 2);
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

TEST(cash_account_controller_test, CreateTable) {
    ASSERT_TRUE(cashAcc->CreateTables());

}

TEST(cash_account_controller_test, Add) {
    Models::CashAccount model{};
    model.id = 1;
    ASSERT_FALSE(cashAcc->Add(model));
    model.name = "name1";
    ASSERT_FALSE(cashAcc->Add(model));
    model.icon.id = 1;
    ASSERT_FALSE(cashAcc->Add(model));
    model.currency.id = 1;
    ASSERT_FALSE(cashAcc->Add(model));
    model.category.id = 1;
    ASSERT_TRUE(cashAcc->Add(model));

    model.id = 2;
    model.name = "name2";
    model.icon.id = 1;
    model.currency.id = 2;
    model.category.id = 2;
    ASSERT_TRUE(cashAcc->Add(model));
}

TEST(cash_account_controller_test, Edit) {
    Models::CashAccount model;
    model.id = 1;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.name = "test111";
    ASSERT_FALSE(cashAcc->Edit(model));
    model.description = "desc";
    ASSERT_FALSE(cashAcc->Edit(model));
    model.debt = 12;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.color.set(QString("#000012"));
    ASSERT_FALSE(cashAcc->Edit(model));
    model.refund = 1232.1;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.balance = 1323.23;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.purpose = 123;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.settings.displayInExpenses = true;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.settings.displayInOverallBalance = false;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.icon.id = 2;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.currency.id = 2;
    ASSERT_FALSE(cashAcc->Edit(model));
    model.category.id = 2;
    ASSERT_TRUE(cashAcc->Edit(model));

    Models::CashAccount model2;
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.id = 2;
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.name = "test222";
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.icon.id = 88;
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.currency.id = 1;
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.category.id = 132;
    ASSERT_TRUE(cashAcc->Edit(model2));
}

TEST(cash_account_controller_test, Get) {
    auto m = cashAcc->Get(1);
    ASSERT_EQ(m.id, 1);
    ASSERT_EQ(m.name, "test111");
    ASSERT_EQ(m.description, "desc");
    ASSERT_EQ(m.color.hex(), "#000012");
    ASSERT_EQ(m.refund.getAsDouble(), 1232.1);
    ASSERT_EQ(m.balance.getAsDouble(), 1323.23);
    ASSERT_EQ(m.purpose.getAsDouble(), 123);
    ASSERT_EQ(m.settings.displayInExpenses, true);
    ASSERT_EQ(m.settings.displayInOverallBalance, false);
    ASSERT_EQ(m.icon.id, 2);
    ASSERT_EQ(m.currency.id, 2);
    ASSERT_EQ(m.category.id, 2);

    auto m2 = cashAcc->Get(2);
    ASSERT_EQ(m2.id, 2);
    ASSERT_EQ(m2.name, "test222");
    ASSERT_EQ(m2.description, "");
    ASSERT_EQ(m2.color.hex(), "#000000");
    ASSERT_EQ(m2.refund.getAsDouble(), 0);
    ASSERT_EQ(m2.balance.getAsDouble(), 0);
    ASSERT_EQ(m2.purpose.getAsDouble(), 0);
    ASSERT_EQ(m2.settings.displayInExpenses, false);
    ASSERT_EQ(m2.settings.displayInOverallBalance, false);
    ASSERT_EQ(m2.icon.id, 88);
    ASSERT_EQ(m2.currency.id, 1);
    ASSERT_EQ(m2.category.id, 132);
}

TEST(cash_account_controller_test, GetAll) {
    auto mdls = cashAcc->GetAll();
    ASSERT_EQ(mdls.at(0).id, 1);
    ASSERT_EQ(mdls.at(0).name, "test111");
    ASSERT_EQ(mdls.at(0).description, "desc");
    ASSERT_EQ(mdls.at(0).color.hex(), "#000012");
    ASSERT_EQ(mdls.at(0).refund.getAsDouble(), 1232.1);
    ASSERT_EQ(mdls.at(0).balance.getAsDouble(), 1323.23);
    ASSERT_EQ(mdls.at(0).purpose.getAsDouble(), 123);
    ASSERT_EQ(mdls.at(0).settings.displayInExpenses, true);
    ASSERT_EQ(mdls.at(0).settings.displayInOverallBalance, false);
    ASSERT_EQ(mdls.at(0).icon.id, 2);
    ASSERT_EQ(mdls.at(0).currency.id, 2);
    ASSERT_EQ(mdls.at(0).category.id, 2);

    ASSERT_EQ(mdls.at(1).id, 2);
    ASSERT_EQ(mdls.at(1).name, "test222");
    ASSERT_EQ(mdls.at(1).description, "");
    ASSERT_EQ(mdls.at(1).color.hex(), "#000000");
    ASSERT_EQ(mdls.at(1).refund.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(1).balance.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(1).purpose.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(1).settings.displayInExpenses, false);
    ASSERT_EQ(mdls.at(1).settings.displayInOverallBalance, false);
    ASSERT_EQ(mdls.at(1).icon.id, 88);
    ASSERT_EQ(mdls.at(1).currency.id, 1);
    ASSERT_EQ(mdls.at(1).category.id, 132);
}

TEST(controller_end_test, drop_db) {
    dropDB();
}
}

#endif // TST_CURRENCY_CNTRL_H
