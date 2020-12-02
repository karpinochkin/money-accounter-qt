#ifndef TST_TBLS_H
#define TST_TBLS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../../utils/tables_utils.h"

using namespace testing;

namespace DB::Tables {

/// *** init objects *** ///
auto currency = CreateScope<DB::Tables::QCurrency>(db);
auto icon = CreateScope<DB::Tables::QIcon>(db);
auto cashAccsCateg = CreateScope<DB::Tables::CashAccoutType>(db);
auto cashAcc = CreateScope<DB::Tables::CashAccount>(db);
auto category = CreateScope<DB::Tables::Category>(db);
auto transaction = CreateScope<DB::Tables::Transaction>(db);

/// *** open db *** ///
TEST(tables_start_test, open_db) {
    ASSERT_TRUE(openDB());
}
/// *** *** ///

/// *** currency tables tests *** ///
TEST(currency_table_test, create_table) {
    currency->CreateTable();
    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::Currency::tableName() + "';";

    auto [query, result] = currency->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::Currency::tableName());
}

TEST(currency_table_test, add_test) {
    Models::Currency currency_;
    currency_.id = 1;
    currency_.name = "dollar usa";
    currency_.symbol = "$";
    currency->Add(currency_);

    currency_.id = 2;
    currency_.name = "Euro";
    currency_.symbol = "EUR";
    currency->Add(currency_);

    QString text = "select " + DB::Tables::Data::Currency::name() + ", "
            + DB::Tables::Data::Currency::symbol()
            + " from " + DB::Tables::Data::Currency::tableName()
            + " where " + DB::Tables::Data::Currency::id()
            + " = '2';";
    auto [query, result] = currency->MakeQuery(text);
    ASSERT_TRUE(result);
    if(query->next()) {
        ASSERT_EQ(query->value(0).toString(), "Euro");
        ASSERT_EQ(query->value(1).toString(), "EUR");
    }
}

TEST(currency_table_test, get_test) {
    auto model = std::dynamic_pointer_cast<Models::Currency>(currency->Get(2));

    ASSERT_TRUE(model->isCorrect());
    ASSERT_EQ(model->id, 2);
    ASSERT_EQ(model->name, "Euro");
    ASSERT_EQ(model->symbol, "EUR");
}

TEST(currency_table_test, get_all_test) {
    auto models = currency->GetAll();

    ASSERT_EQ(std::size(models), 2);

    ASSERT_TRUE(models.at(0).value<Models::Currency>().isCorrect());
    ASSERT_EQ(models.at(0).value<Models::Currency>().id, 1);
    ASSERT_EQ(models.at(0).value<Models::Currency>().name, "dollar usa");
    ASSERT_EQ(models.at(0).value<Models::Currency>().symbol, "$");

    ASSERT_TRUE(models.at(1).value<Models::Currency>().isCorrect());
    ASSERT_EQ(models.at(1).value<Models::Currency>().id, 2);
    ASSERT_EQ(models.at(1).value<Models::Currency>().name, "Euro");
    ASSERT_EQ(models.at(1).value<Models::Currency>().symbol, "EUR");
}
/// *** *** ///

TEST(icon_table_test, CreateTable) {
    icon->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::Icon::tableName() + "';";

    auto [query, result] = icon->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::Icon::tableName());
}

TEST(icon_table_test, Add) {
    Models::Icon icon_;
    icon_.id = 1;
    icon_.path = "path1";
    icon->Add(icon_);

    icon_.id = 2;
    icon_.path = "path12";
    icon->Add(icon_);

    icon_.id = 3;
    icon_.path = "path123";
    icon->Add(icon_);

    QString text = "select " + DB::Tables::Data::Icon::path()
            + " from " + DB::Tables::Data::Icon::tableName()
            + " where " + DB::Tables::Data::Icon::id()
            + " = '3';";

    auto [query, result] = icon->MakeQuery(text);
    ASSERT_TRUE(result);
    if(query->next()) {
        ASSERT_EQ(query->value(0).toString(), "path123");
    }
}

TEST(icon_table_test, Get) {
    auto m = std::dynamic_pointer_cast<Models::Icon>(icon->Get(1));
    ASSERT_TRUE(m->isCorrect());
    ASSERT_EQ(m->id, 1);
    ASSERT_EQ(m->path, "path1");

    m = std::dynamic_pointer_cast<Models::Icon>(icon->Get(3));
    ASSERT_TRUE(m->isCorrect());
    ASSERT_EQ(m->id, 3);
    ASSERT_EQ(m->path, "path123");
}

TEST(icon_table_test, GetAll) {
    auto models = icon->GetAll();

    ASSERT_EQ(std::size(models), 3);
    ASSERT_TRUE(models.at(0).value<Models::Icon>().isCorrect());
    ASSERT_EQ(models.at(0).value<Models::Icon>().id, 1);
    ASSERT_EQ(models.at(0).value<Models::Icon>().path, "path1");

    ASSERT_TRUE(models.at(1).value<Models::Icon>().isCorrect());
    ASSERT_EQ(models.at(1).value<Models::Icon>().id, 2);
    ASSERT_EQ(models.at(1).value<Models::Icon>().path, "path12");

    ASSERT_TRUE(models.at(2).value<Models::Icon>().isCorrect());
    ASSERT_EQ(models.at(2).value<Models::Icon>().id, 3);
    ASSERT_EQ(models.at(2).value<Models::Icon>().path, "path123");
}

TEST(cash_accs_categ_table_test, CreateTable) {
    cashAccsCateg->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::CashAccountType::tableName() + "';";

    auto [query, result] = cashAccsCateg->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::CashAccountType::tableName());
}

TEST(cash_accs_categ_table_test, Add) {
    MCashAccType model_1;
    model_1.id = 13;
    model_1.name = "test";
    model_1.settings.isIncludeDebt = 0;
    model_1.settings.isIncludeRefund = 1;
    model_1.settings.isIncludePurpose = 1;
    model_1.description = "test descr";

    MCashAccType model_2;
    model_2.id = 132;
    model_2.name = "test2";

    cashAccsCateg->Add(model_1);
    cashAccsCateg->Add(model_2);
}

TEST(cash_accs_categ_table_test, Get) {
    auto m2 = std::dynamic_pointer_cast<MCashAccType>(cashAccsCateg->Get(132));
    auto m1 = std::dynamic_pointer_cast<MCashAccType>(cashAccsCateg->Get(13));
    auto m3 = std::dynamic_pointer_cast<MCashAccType>(cashAccsCateg->Get(3));

    ASSERT_TRUE(m1->isCorrect());
    ASSERT_EQ(m1->id, 13);
    ASSERT_EQ(m1->name, "test");
    ASSERT_EQ(m1->description, "test descr");
    ASSERT_EQ(m1->settings.isIncludeDebt, false);
    ASSERT_EQ(m1->settings.isIncludeRefund, true);
    ASSERT_EQ(m1->settings.isIncludePurpose, true);

    ASSERT_TRUE(m2->isCorrect());
    ASSERT_EQ(m2->id, 132);
    ASSERT_EQ(m2->name, "test2");
    ASSERT_EQ(m2->description, "");
    ASSERT_EQ(m2->settings.isIncludeDebt, false);
    ASSERT_EQ(m2->settings.isIncludeRefund, false);
    ASSERT_EQ(m2->settings.isIncludePurpose, false);

    ASSERT_FALSE(m3->isCorrect());
}

TEST(cash_accs_categ_table_test, GetAll) {
    auto list = cashAccsCateg->GetAll();
    ASSERT_EQ(std::size(list), 2);

    ASSERT_TRUE(list[0].value<Models::CashAccountType>().isCorrect());
    ASSERT_EQ(list[0].value<Models::CashAccountType>().id, 13);
    ASSERT_EQ(list[0].value<Models::CashAccountType>().name, "test");
    ASSERT_EQ(list[0].value<Models::CashAccountType>().description, "test descr");
    ASSERT_EQ(list[0].value<Models::CashAccountType>().settings.isIncludeDebt, false);
    ASSERT_EQ(list[0].value<Models::CashAccountType>().settings.isIncludeRefund, true);
    ASSERT_EQ(list[0].value<Models::CashAccountType>().settings.isIncludePurpose, true);

    ASSERT_TRUE(list[1].value<Models::CashAccountType>().isCorrect());
    ASSERT_EQ(list[1].value<Models::CashAccountType>().id, 132);
    ASSERT_EQ(list[1].value<Models::CashAccountType>().name, "test2");
    ASSERT_EQ(list[1].value<Models::CashAccountType>().description, "");
    ASSERT_EQ(list[1].value<Models::CashAccountType>().settings.isIncludeDebt, false);
    ASSERT_EQ(list[1].value<Models::CashAccountType>().settings.isIncludeRefund, false);
    ASSERT_EQ(list[1].value<Models::CashAccountType>().settings.isIncludePurpose, false);
}

TEST(cash_acc_table_test, CreateTable) {
    cashAcc->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::CashAccount::tableName() + "';";

    auto [query, result] = cashAcc->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::CashAccount::tableName());
}

TEST(cash_acc_table_test, Add) {
    Models::CashAccount model;
    model.id = 1;
    model.name = "name1";
    model.icon.id = 1;
    model.currency.id = 1;
    model.type.id = 1;
    cashAcc->Add(model);

    model.id = 2;
    model.name = "name2";
    model.icon.id = 1;
    model.currency.id = 2;
    model.type.id = 2;
    cashAcc->Add(model);
}

TEST(cash_acc_table_test, Edit) {
    Models::CashAccount model;
    model.id = 1;
    model.name = "test111";
    model.description = "desc";
    model.debt = 12;
    model.color.set(QString("#000012"));
    model.refund = 1232.1;
    model.balance = 1323.23;
    model.purpose = 123;
    model.settings.displayInExpenses = true;
    model.settings.displayInOverallBalance = false;
    model.icon.id = 2;
    model.currency.id = 2;
    model.type.id = 2;
    cashAcc->Edit(model);

    Models::CashAccount model2;
    model2.id = 2;
    model2.name = "test222";
    model2.icon.id = 1;
    model2.currency.id = 1;
    model2.type.id = 1;
    cashAcc->Edit(model2);
}

TEST(cash_acc_table_test, Get) {
    auto m = std::dynamic_pointer_cast<MCashAcc>(cashAcc->Get(1));
    ASSERT_EQ(m->id, 1);
    ASSERT_EQ(m->name, "test111");
    ASSERT_EQ(m->description, "desc");
    ASSERT_EQ(m->color.hex(), "#000012");
    ASSERT_EQ(m->refund.getAsDouble(), 1232.1);
    ASSERT_EQ(m->balance.getAsDouble(), 1323.23);
    ASSERT_EQ(m->purpose.getAsDouble(), 123);
    ASSERT_EQ(m->settings.displayInExpenses, true);
    ASSERT_EQ(m->settings.displayInOverallBalance, false);
    ASSERT_EQ(m->icon.id, 2);
    ASSERT_EQ(m->currency.id, 2);
    ASSERT_EQ(m->type.id, 2);

    auto m2 = std::dynamic_pointer_cast<MCashAcc>(cashAcc->Get(2));
    qDebug() << m2->name;
    ASSERT_EQ(m2->id, 2);
    ASSERT_EQ(m2->name, "test222");
    ASSERT_EQ(m2->description, "");
    ASSERT_EQ(m2->color.hex(), "#000000");
    ASSERT_EQ(m2->refund.getAsDouble(), 0);
    ASSERT_EQ(m2->balance.getAsDouble(), 0);
    ASSERT_EQ(m2->purpose.getAsDouble(), 0);
    ASSERT_EQ(m2->settings.displayInExpenses, false);
    ASSERT_EQ(m2->settings.displayInOverallBalance, false);
    ASSERT_EQ(m2->icon.id, 1);
    ASSERT_EQ(m2->currency.id, 1);
    ASSERT_EQ(m2->type.id, 1);
}

TEST(cash_acc_table_test, GetAll) {
    auto mdls = cashAcc->GetAll();
    auto m1 = unpack<Models::CashAccount>(mdls.at(0));
    ASSERT_EQ(std::size(mdls), 2);
    ASSERT_EQ(m1.id, 1);
    ASSERT_EQ(m1.name, "test111");
    ASSERT_EQ(m1.description, "desc");
    ASSERT_EQ(m1.color.hex(), "#000012");
    ASSERT_EQ(m1.refund.getAsDouble(), 1232.1);
    ASSERT_EQ(m1.balance.getAsDouble(), 1323.23);
    ASSERT_EQ(m1.purpose.getAsDouble(), 123);
    ASSERT_EQ(m1.settings.displayInExpenses, true);
    ASSERT_EQ(m1.settings.displayInOverallBalance, false);
    ASSERT_EQ(m1.icon.id, 2);
    ASSERT_EQ(m1.currency.id, 2);
    ASSERT_EQ(m1.type.id, 2);

    auto m2 = unpack<Models::CashAccount>(mdls.at(1));
    ASSERT_EQ(m2.id, 2);
    ASSERT_EQ(m2.name, "test222");
    ASSERT_EQ(m2.description, "");
    ASSERT_EQ(m2.color.hex(), "#000000");
    ASSERT_EQ(m2.refund.getAsDouble(), 0);
    ASSERT_EQ(m2.balance.getAsDouble(), 0);
    ASSERT_EQ(m2.purpose.getAsDouble(), 0);
    ASSERT_EQ(m2.settings.displayInExpenses, false);
    ASSERT_EQ(m2.settings.displayInOverallBalance, false);
    ASSERT_EQ(m2.icon.id, 1);
    ASSERT_EQ(m2.currency.id, 1);
    ASSERT_EQ(m2.type.id, 1);

}

TEST(cash_acc_table_test, Remove) {
    cashAcc->Remove(1);

    auto mdls = cashAcc->GetAll();
    auto m1 = unpack<Models::CashAccount>(mdls.at(0));
    ASSERT_EQ(std::size(mdls), 1);
    ASSERT_EQ(m1.id, 2);
    ASSERT_EQ(m1.name, "test222");
    ASSERT_EQ(m1.description, "");
    ASSERT_EQ(m1.color.hex(), "#000000");
    ASSERT_EQ(m1.refund.getAsDouble(), 0);
    ASSERT_EQ(m1.balance.getAsDouble(), 0);
    ASSERT_EQ(m1.purpose.getAsDouble(), 0);
    ASSERT_EQ(m1.settings.displayInExpenses, false);
    ASSERT_EQ(m1.settings.displayInOverallBalance, false);
    ASSERT_EQ(m1.icon.id, 1);
    ASSERT_EQ(m1.currency.id, 1);
    ASSERT_EQ(m1.type.id, 1);
}

TEST(category_table_test, CreateTable) {
    category->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::Category::tableName() + "';";

    auto [query, result] = category->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::Category::tableName());
}

TEST(category_table_test, Add) {
    Models::Category model;
    model.id = 1;
    model.name = "name1";
    model.icon.id = 1;
    model.currency.id = 1;
    model.description = "desc1";
    category->Add(model);

    model.id = 2;
    model.name = "name2";
    model.icon.id = 1;
    model.currency.id = 2;
    model.description = "desc2";
    category->Add(model);
}

TEST(category_table_test, Edit) {
    Models::Category model;
    model.id = 1;
    model.name = "test111";
    model.description = "desc";
    model.color.set(QString("#000012"));
    model.icon.id = 2;
    model.currency.id = 2;
    category->Edit(model);

    Models::Category model2;
    model2.id = 2;
    model2.name = "test222";
    model2.icon.id = 1;
    model2.currency.id = 1;
    category->Edit(model2);
}

TEST(category_table_test, Get) {
    auto m = std::dynamic_pointer_cast<Models::Category>(category->Get(1));
    ASSERT_EQ(m->id, 1);
    ASSERT_EQ(m->name, "test111");
    ASSERT_EQ(m->description, "desc");
    ASSERT_EQ(m->color.hex(), "#000012");
    ASSERT_EQ(m->icon.id, 2);
    ASSERT_EQ(m->currency.id, 2);

    auto m2 = std::dynamic_pointer_cast<Models::Category>(category->Get(2));
    ASSERT_EQ(m2->id, 2);
    ASSERT_EQ(m2->name, "test222");
    ASSERT_EQ(m2->description, "");
    ASSERT_EQ(m2->color.hex(), "#000000");
    ASSERT_EQ(m2->icon.id, 1);
    ASSERT_EQ(m2->currency.id, 1);
}

TEST(category_table_test, GetAll) {
    auto mdls = category->GetAll();
    auto m1 = unpack<Models::Category>(mdls.at(0));
    ASSERT_EQ(std::size(mdls), 2);
    ASSERT_EQ(m1.id, 1);
    ASSERT_EQ(m1.name, "test111");
    ASSERT_EQ(m1.description, "desc");
    ASSERT_EQ(m1.color.hex(), "#000012");
    ASSERT_EQ(m1.icon.id, 2);
    ASSERT_EQ(m1.currency.id, 2);

    auto m2 = unpack<Models::Category>(mdls.at(1));
    ASSERT_EQ(m2.id, 2);
    ASSERT_EQ(m2.name, "test222");
    ASSERT_EQ(m2.description, "");
    ASSERT_EQ(m2.color.hex(), "#000000");
    ASSERT_EQ(m2.icon.id, 1);
    ASSERT_EQ(m2.currency.id, 1);
}

TEST(category_table_test, Remove) {
    category->Remove(1);

    auto mdls = category->GetAll();
    auto m1 = unpack<Models::Category>(mdls.at(0));

    ASSERT_EQ(std::size(mdls), 1);
    ASSERT_EQ(m1.id, 2);
    ASSERT_EQ(m1.name, "test222");
    ASSERT_EQ(m1.description, "");
    ASSERT_EQ(m1.color.hex(), "#000000");
    ASSERT_EQ(m1.icon.id, 1);
    ASSERT_EQ(m1.currency.id, 1);
}

TEST(transaction_table_test, CreateTable)
{
    transaction->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::Transaction::tableName() + "';";

    auto [query, result] = transaction->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::Transaction::tableName());
}

TEST(transaction_table_test, Add) {
    Models::Transaction model;
    model.id = 1;
    model.name = "name1";
    model.datetime = QDateTime::currentDateTime();
    model.sum = 18;
    model.cashAccount.id = 1;
    model.category.id = 2;
    transaction->Add(model);

    Models::Transaction model2;
    model2.id = 2;
    model2.name = "name2";
    model2.datetime = QDateTime::currentDateTime();
    model2.sum = 3;
    model2.cashAccount.id = 2;
    model2.category.id = 1;
    transaction->Add(model2);
}

TEST(transaction_table_test, Edit) {
    Models::Transaction model;
    model.id = 1;
    model.name = "test111";
    model.description = "desc";
    model.cashAccount.id = 2;
    model.category.id = 2;
    model.sum = 180;
    transaction->Edit(model);

    Models::Transaction model2;
    model2.id = 2;
    model2.name = "test222";
    model2.cashAccount.id = 1;
    model2.category.id = 1;
    model2.sum = 1;
    transaction->Edit(model2);
}

TEST(transaction_table_test, Get) {
    auto m = std::dynamic_pointer_cast<Models::Transaction>(transaction->Get(1));
    ASSERT_EQ(m->id, 1);
    ASSERT_EQ(m->name, "test111");
    ASSERT_EQ(m->description, "desc");
    ASSERT_EQ(m->cashAccount.id, 2);
    ASSERT_EQ(m->category.id, 2);
    ASSERT_EQ(m->sum.getAsDouble(), 180);

    auto m2 = std::dynamic_pointer_cast<Models::Transaction>(transaction->Get(2));
    ASSERT_EQ(m2->id, 2);
    ASSERT_EQ(m2->name, "test222");
    ASSERT_EQ(m2->description, "");
    ASSERT_EQ(m2->cashAccount.id, 1);
    ASSERT_EQ(m2->category.id, 1);
    ASSERT_EQ(m2->sum.getAsDouble(), 1);
}

TEST(transaction_table_test, GetAll) {
    auto ms = transaction->GetAll();
    auto m1 = unpack<Models::Transaction>(ms.at(0));
    ASSERT_EQ(std::size(ms), 2);
    ASSERT_EQ(m1.id, 1);
    ASSERT_EQ(m1.name, "test111");
    ASSERT_EQ(m1.description, "desc");
    ASSERT_EQ(m1.cashAccount.id, 2);
    ASSERT_EQ(m1.category.id, 2);
    ASSERT_EQ(m1.sum.getAsDouble(), 180);

    auto m2 = unpack<Models::Transaction>(ms.at(1));
    ASSERT_EQ(m2.id, 2);
    ASSERT_EQ(m2.name, "test222");
    ASSERT_EQ(m2.description, "");
    ASSERT_EQ(m2.cashAccount.id, 1);
    ASSERT_EQ(m2.category.id, 1);
    ASSERT_EQ(m2.sum.getAsDouble(), 1);
}

TEST(transaction_table_test, Remove) {
    transaction->Remove(1);

    auto ms = transaction->GetAll();
    auto m1 = unpack<Models::Transaction>(ms.at(0));
    ASSERT_EQ(std::size(ms), 1);

    ASSERT_EQ(m1.id, 2);
    ASSERT_EQ(m1.name, "test222");
    ASSERT_EQ(m1.description, "");
    ASSERT_EQ(m1.cashAccount.id, 1);
    ASSERT_EQ(m1.category.id, 1);
    ASSERT_EQ(m1.sum.getAsDouble(), 1);
}

TEST(transaction_table_test, Add2) {
    QString text = "INSERT INTO "
            + Data::Transaction::tableName() + " ("
            + Data::Transaction::id() + ", "
            + Data::Transaction::name() + ", "
            + Data::Transaction::descrpiption() + ", "
            + Data::Transaction::datetime() + ", "
            + Data::Transaction::sum() + ", "
            + Data::Transaction::idCashAccount() + ", "
            + Data::Transaction::idCategory()
            + ") VALUES ('"
            + S_NUM(3) + "','"
            + "','"
            + "','"
            + "','"
            + "','"
            + S_NUM(0) + "','"
            + S_NUM(0) + "');";
    auto [query,result] = transaction->MakeQuery(text);
            ASSERT_FALSE(result);
}

/// *** close db *** ///
TEST(tables_end_test, drop_db) {
    dropDB();
}
/// *** *** ///
}

#endif // TST_CURRENCY_TBL_H
