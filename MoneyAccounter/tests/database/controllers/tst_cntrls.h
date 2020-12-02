#ifndef TST_CNTRLS_H
#define TST_CNTRLS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../src/database/controllers/tablecontrollers.h"
#include "../../utils/db_utils.h"

namespace DB::Controllers {
auto currency = CreateScope<DB::Controllers::QCurrency>(db);
auto icon = CreateScope<DB::Controllers::QIcon>(db);
auto cashAccType = CreateScope<DB::Controllers::QCashAccountType>(db);
auto cashAcc = CreateScope<DB::Controllers::QCashAccount>(currency.get(), icon.get(), cashAccType.get(), db);
auto category = CreateScope<DB::Controllers::QCategory>(currency.get(), icon.get(), db);
auto transaction = CreateScope<DB::Controllers::QTransaction>(cashAcc.get(), category.get(), db);

TEST(controller_start_test, open_db) {
    ASSERT_TRUE(openDB());
    ASSERT_TRUE(pragmaON());
}

TEST(currency_controller_test, create_tables) {
    ASSERT_TRUE(currency->CreateTables());
}

TEST(currency_controller_test, add_currency) {
    Models::Currency currency_;
    ASSERT_FALSE(currency->Add(currency_));
    currency_.id = 1;
    ASSERT_FALSE(currency->Add(currency_));
    currency_.name = "dollar usa";
    ASSERT_FALSE(currency->Add(currency_));
    currency_.symbol = "$";
    ASSERT_TRUE(currency->Add(currency_));
    ASSERT_FALSE(currency->Add(currency_));

    currency_.id = 2;
    currency_.name = "Euro";
    ASSERT_FALSE(currency->Add(currency_));
    currency_.symbol = "EUR";
    ASSERT_TRUE(currency->Add(currency_));
    ASSERT_FALSE(currency->Add(currency_));
}

TEST(currency_controller_test, get_currency) {
        auto model = currency->Get(2);

        ASSERT_TRUE(model.isCorrect());
        ASSERT_EQ(2, model.id);
        ASSERT_EQ("Euro", model.name);
        ASSERT_EQ(model.symbol, "EUR");
}

TEST(currency_controller_test, get_currencies) {
        auto models = currency->GetAll();

        ASSERT_EQ(2, std::size(models));
        ASSERT_TRUE(models.at(0).isCorrect());
        ASSERT_TRUE(models.at(1).isCorrect());

        ASSERT_EQ(2, models.at(1).id);
        ASSERT_EQ("Euro", models.at(1).name);
        ASSERT_EQ(models.at(1).symbol, "EUR");
        ASSERT_EQ(models.at(0).id, 1);
        ASSERT_EQ("dollar usa", models.at(0).name);
        ASSERT_EQ(models.at(0).symbol, "$");
}

TEST(icon_controller_test, CreateTables) {
    ASSERT_TRUE(icon->CreateTables());
}

TEST(icon_controller_test, Add) {
    Models::Icon icon_;
    ASSERT_FALSE(icon->Add(icon_));
    icon_.id = 2;
    ASSERT_FALSE(icon->Add(icon_));
    icon_.path = "77777";
    ASSERT_TRUE(icon->Add(icon_));
    ASSERT_FALSE(icon->Add(icon_));
    icon_.id = 88;
    icon_.path = "8888888";
    ASSERT_TRUE(icon->Add(icon_));
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
    ASSERT_TRUE(cashAccType->CreateTables());
}

TEST(cash_account_category_controller_test, Add) {
    MCashAccType model_1{};
    ASSERT_FALSE(cashAccType->Add(model_1));
    model_1.id = 2;
    ASSERT_FALSE(cashAccType->Add(model_1));
    model_1.name = "test";
    model_1.settings.isIncludeDebt = 0;
    model_1.settings.isIncludeRefund = 1;
    model_1.settings.isIncludePurpose = 1;
    model_1.description = "test descr";

    MCashAccType model_2{};
    ASSERT_FALSE(cashAccType->Add(model_2));
    model_2.id = 132;
    ASSERT_FALSE(cashAccType->Add(model_2));
    model_2.name = "test2";
    ASSERT_TRUE(cashAccType->Add(model_1));
    ASSERT_TRUE(cashAccType->Add(model_2));
    ASSERT_FALSE(cashAccType->Add(model_1));
    ASSERT_FALSE(cashAccType->Add(model_2));
}

TEST(cash_account_category_controller_test, Get) {
    auto m2 = cashAccType->Get(132);
    auto m1 = cashAccType->Get(2);
    auto m3 = cashAccType->Get(3);

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
    auto list = cashAccType->GetAll();
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
    ASSERT_FALSE(cashAcc->Add(model));
    model.id = 1;
    ASSERT_FALSE(cashAcc->Add(model));
    model.name = "name1";
    ASSERT_FALSE(cashAcc->Add(model));
    model.icon.id = 2;
    ASSERT_FALSE(cashAcc->Add(model));
    model.currency.id = 2;
    ASSERT_FALSE(cashAcc->Add(model));
    model.type.id = 132;
    ASSERT_TRUE(cashAcc->Add(model));
    ASSERT_FALSE(cashAcc->Add(model));

    model.id = 2;
    model.name = "name2";
    model.icon.id = 2;
    model.currency.id = 2;
    model.type.id = 2;
    ASSERT_TRUE(cashAcc->Add(model));
    ASSERT_FALSE(cashAcc->Add(model));
}

TEST(cash_account_controller_test, Edit) {
    Models::CashAccount model{};
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
    model.type.id = 2;
    ASSERT_TRUE(cashAcc->Edit(model));

    Models::CashAccount model2;
    model2.id = 2;
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.name = "test222";
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.icon.id = 2;
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.currency.id = 2;
    ASSERT_FALSE(cashAcc->Edit(model2));
    model2.type.id = 132;
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
    ASSERT_EQ(m.type.id, 2);

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
    ASSERT_EQ(m2.icon.id, 2);
    ASSERT_EQ(m2.currency.id, 2);
    ASSERT_EQ(m2.type.id, 132);
}

TEST(cash_account_controller_test, GetAll) {
    auto mdls = cashAcc->GetAll();
    ASSERT_EQ(std::size(mdls), 2);
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
    ASSERT_EQ(mdls.at(0).type.id, 2);

    ASSERT_EQ(mdls.at(1).id, 2);
    ASSERT_EQ(mdls.at(1).name, "test222");
    ASSERT_EQ(mdls.at(1).description, "");
    ASSERT_EQ(mdls.at(1).color.hex(), "#000000");
    ASSERT_EQ(mdls.at(1).refund.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(1).balance.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(1).purpose.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(1).settings.displayInExpenses, false);
    ASSERT_EQ(mdls.at(1).settings.displayInOverallBalance, false);
    ASSERT_EQ(mdls.at(1).icon.id, 2);
    ASSERT_EQ(mdls.at(1).currency.id, 2);
    ASSERT_EQ(mdls.at(1).type.id, 132);
}

TEST(cash_account_controller_test, Remove) {
    bool result = cashAcc->Remove(1);
    ASSERT_TRUE(result);
    auto mdls = cashAcc->GetAll();
    ASSERT_EQ(std::size(mdls), 1);
    ASSERT_EQ(mdls.at(0).id, 2);
    ASSERT_EQ(mdls.at(0).name, "test222");
    ASSERT_EQ(mdls.at(0).description, "");
    ASSERT_EQ(mdls.at(0).color.hex(), "#000000");
    ASSERT_EQ(mdls.at(0).refund.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(0).balance.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(0).purpose.getAsDouble(), 0);
    ASSERT_EQ(mdls.at(0).settings.displayInExpenses, false);
    ASSERT_EQ(mdls.at(0).settings.displayInOverallBalance, false);
    ASSERT_EQ(mdls.at(0).icon.id, 2);
    ASSERT_EQ(mdls.at(0).currency.id, 2);
    ASSERT_EQ(mdls.at(0).type.id, 132);

}

TEST(category_controller_test, CreateTable) {
    ASSERT_TRUE(category->CreateTables());
}

TEST(category_controller_test, Add) {
    Models::Category model;
    model.id = 1;
    ASSERT_FALSE(category->Add(model));
    model.name = "name1";
    ASSERT_FALSE(category->Add(model));
    model.icon.id = 2;
    ASSERT_FALSE(category->Add(model));
    model.currency.id = 2;
    ASSERT_TRUE(category->Add(model));
    ASSERT_FALSE(category->Add(model));

    model.id = 2;
    model.name = "name2";
    model.icon.id = 2;
    model.currency.id = 2;
    ASSERT_TRUE(category->Add(model));
    ASSERT_FALSE(category->Add(model));
}

TEST(category_controller_test, Edit) {
    Models::Category model;
    model.id = 1;
    ASSERT_FALSE(category->Edit(model));
    model.name = "test111";
    ASSERT_FALSE(category->Edit(model));
    model.description = "desc";
    ASSERT_FALSE(category->Edit(model));
    model.color.set(QString("#000012"));
    ASSERT_FALSE(category->Edit(model));
    model.icon.id = 2;
    ASSERT_FALSE(category->Edit(model));
    model.currency.id = 2;
    ASSERT_TRUE(category->Edit(model));

    Models::Category model2;
    model2.id = 2;
    ASSERT_FALSE(category->Edit(model2));
    model2.name = "test222";
    ASSERT_FALSE(category->Edit(model2));
    model2.icon.id = 88;
    ASSERT_FALSE(category->Edit(model2));
    model2.currency.id = 1;
    ASSERT_TRUE(category->Edit(model2));
}

TEST(category_controller_test, Get) {
    auto m = category->Get(1);
    ASSERT_EQ(m.id, 1);
    ASSERT_EQ(m.name, "test111");
    ASSERT_EQ(m.description, "desc");
    ASSERT_EQ(m.color.hex(), "#000012");
    ASSERT_EQ(m.icon.id, 2);
    ASSERT_EQ(m.currency.id, 2);

    auto m2 = category->Get(2);
    ASSERT_EQ(m2.id, 2);
    ASSERT_EQ(m2.name, "test222");
    ASSERT_EQ(m2.description, "");
    ASSERT_EQ(m2.color.hex(), "#000000");
    ASSERT_EQ(m2.icon.id, 88);
    ASSERT_EQ(m2.currency.id, 1);
}

TEST(category_controller_test, GetAll) {
    auto mdls = category->GetAll();
    ASSERT_EQ(std::size(mdls), 2);
    ASSERT_EQ(mdls.at(0).id, 1);
    ASSERT_EQ(mdls.at(0).name, "test111");
    ASSERT_EQ(mdls.at(0).description, "desc");
    ASSERT_EQ(mdls.at(0).color.hex(), "#000012");
    ASSERT_EQ(mdls.at(0).icon.id, 2);
    ASSERT_EQ(mdls.at(0).currency.id, 2);

    ASSERT_EQ(mdls.at(1).id, 2);
    ASSERT_EQ(mdls.at(1).name, "test222");
    ASSERT_EQ(mdls.at(1).description, "");
    ASSERT_EQ(mdls.at(1).color.hex(), "#000000");
    ASSERT_EQ(mdls.at(1).icon.id, 88);
    ASSERT_EQ(mdls.at(1).currency.id, 1);
}

TEST(category_controller_test, Remove) {
    bool result = category->Remove(1);
    ASSERT_TRUE(result);
    auto mdls = category->GetAll();
    ASSERT_EQ(std::size(mdls), 1);
    ASSERT_EQ(mdls.at(0).id, 2);
    ASSERT_EQ(mdls.at(0).name, "test222");
    ASSERT_EQ(mdls.at(0).description, "");
    ASSERT_EQ(mdls.at(0).color.hex(), "#000000");
    ASSERT_EQ(mdls.at(0).icon.id, 88);
    ASSERT_EQ(mdls.at(0).currency.id, 1);
}

TEST(transaction_controller_test, CreateTable) {
    ASSERT_TRUE(transaction->CreateTables());
}

TEST(transaction_controller_test, Add) {

    Models::Transaction model;
    model.id = 1;
    ASSERT_FALSE(transaction->Add(model));
    model.name = "name1";
    ASSERT_FALSE(transaction->Add(model));
    model.datetime = QDateTime::currentDateTime();
    ASSERT_FALSE(transaction->Add(model));
    model.sum = 18;
    ASSERT_FALSE(transaction->Add(model));
    model.cashAccount.id = 2;
    ASSERT_FALSE(transaction->Add(model));
    model.category.id = 2;
    ASSERT_TRUE(transaction->Add(model));

    Models::Transaction model2;
    model2.id = 2;
    ASSERT_FALSE(transaction->Add(model2));
    model2.name = "name2";
    ASSERT_FALSE(transaction->Add(model2));
    model2.datetime = QDateTime::currentDateTime();
    ASSERT_FALSE(transaction->Add(model2));
    model2.sum = 3;
    ASSERT_FALSE(transaction->Add(model2));
    model2.cashAccount.id = 2;
    ASSERT_FALSE(transaction->Add(model2));
    model2.category.id = 2;
    ASSERT_TRUE(transaction->Add(model2));
}

TEST(transaction_controller_test, Edit) {
    Models::Transaction model;
    model.id = 1;
    model.name = "test111";
    model.description = "desc";
    model.cashAccount.id = 2;
    model.category.id = 2;
    model.sum = 180;
    model.datetime = QDateTime::currentDateTime();
    ASSERT_TRUE(transaction->Edit(model));

    Models::Transaction model2;
    model2.id = 2;
    model2.name = "test222";
    model2.cashAccount.id = 2;
    model2.category.id = 2;
    model2.sum = 1;
    model2.datetime = QDateTime::currentDateTime();
    ASSERT_TRUE(transaction->Edit(model2));
}

TEST(transaction_controller_test, Get) {

    auto m = transaction->Get(1);
    ASSERT_EQ(m.id, 1);
    ASSERT_EQ(m.name, "test111");
    ASSERT_EQ(m.description, "desc");
    ASSERT_EQ(m.cashAccount.id, 2);
    ASSERT_EQ(m.category.id, 2);
    ASSERT_EQ(m.sum.getAsDouble(), 180);

    auto m2 = transaction->Get(2);
    ASSERT_EQ(m2.id, 2);
    ASSERT_EQ(m2.name, "test222");
    ASSERT_EQ(m2.description, "");
    ASSERT_EQ(m2.cashAccount.id, 2);
    ASSERT_EQ(m2.category.id, 2);
    ASSERT_EQ(m2.sum.getAsDouble(), 1);
}

TEST(transaction_controller_test, GetAll) {
    auto ms = transaction->GetAll();
    ASSERT_EQ(std::size(ms), 2);
    ASSERT_EQ(ms.at(0).id, 1);
    ASSERT_EQ(ms.at(0).name, "test111");
    ASSERT_EQ(ms.at(0).description, "desc");
    ASSERT_EQ(ms.at(0).cashAccount.id, 2);
    ASSERT_EQ(ms.at(0).category.id, 2);
    ASSERT_EQ(ms.at(0).sum.getAsDouble(), 180);

    ASSERT_EQ(ms.at(1).id, 2);
    ASSERT_EQ(ms.at(1).name, "test222");
    ASSERT_EQ(ms.at(1).description, "");
    ASSERT_EQ(ms.at(1).cashAccount.id, 2);
    ASSERT_EQ(ms.at(1).category.id, 2);
    ASSERT_EQ(ms.at(1).sum.getAsDouble(), 1);
}

TEST(transaction_controller_test, Remove) {
    ASSERT_TRUE(transaction->Remove(1));
    auto ms = transaction->GetAll();
    ASSERT_EQ(std::size(ms), 1);

    ASSERT_EQ(ms.at(0).id, 2);
    ASSERT_EQ(ms.at(0).name, "test222");
    ASSERT_EQ(ms.at(0).description, "");
    ASSERT_EQ(ms.at(0).cashAccount.id, 2);
    ASSERT_EQ(ms.at(0).category.id, 2);
    ASSERT_EQ(ms.at(0).sum.getAsDouble(), 1);

    Models::Category category_;
    category_.id = 33;
    category_.name = "testremovename33";
    category_.currency.id = 2;
    category_.icon.id = 88;
    ASSERT_TRUE(category->Add(category_));
    category_.id = 1;
    ASSERT_TRUE(category->Add(category_));

    Models::CashAccount cash;
    cash.id = 33;
    cash.name = "testcashacc33";
    cash.icon.id = 2;
    cash.type.id = 132;
    cash.currency.id = 2;
    ASSERT_TRUE(cashAcc->Add(cash));
    cash.id = 1;
    ASSERT_TRUE(cashAcc->Add(cash));

    Models::Transaction tr;
    tr.id = 33;
    tr.name = "testtransactionname33";
    tr.category.id = 33;
    tr.datetime = QDateTime::currentDateTime();
    tr.cashAccount.id = 33;
    ASSERT_TRUE(transaction->Add(tr));

    ms = transaction->GetAll();
    ASSERT_EQ(std::size(ms), 2);
    ASSERT_EQ(ms.at(1).id, 33);
    ASSERT_EQ(ms.at(1).name, "testtransactionname33");
    ASSERT_EQ(ms.at(1).description, "");
    ASSERT_EQ(ms.at(1).cashAccount.id, 33);
    ASSERT_EQ(ms.at(1).category.id, 33);
    ASSERT_EQ(ms.at(1).sum.getAsDouble(), 0.0);

    ASSERT_TRUE(category->Remove(33));
    ms = transaction->GetAll();
    ASSERT_EQ(std::size(ms), 2);
    ASSERT_EQ(ms.at(1).id, 33);
    ASSERT_EQ(ms.at(1).name, "testtransactionname33");
    ASSERT_EQ(ms.at(1).description, "");
    ASSERT_EQ(ms.at(1).cashAccount.id, 33);
    ASSERT_EQ(ms.at(1).category.id, 1);
    ASSERT_EQ(ms.at(1).sum.getAsDouble(), 0.0);

    ASSERT_TRUE(cashAcc->Remove(33));
    ms = transaction->GetAll();
    ASSERT_EQ(std::size(ms), 2);
    ASSERT_EQ(ms.at(1).id, 33);
    ASSERT_EQ(ms.at(1).name, "testtransactionname33");
    ASSERT_EQ(ms.at(1).description, "");
    ASSERT_EQ(ms.at(1).cashAccount.id, 1);
    ASSERT_EQ(ms.at(1).category.id, 1);
    ASSERT_EQ(ms.at(1).sum.getAsDouble(), 0.0);

}

TEST(controller_end_test, drop_db) {
    dropDB();
}
}

#endif // TST_CURRENCY_CNTRL_H
