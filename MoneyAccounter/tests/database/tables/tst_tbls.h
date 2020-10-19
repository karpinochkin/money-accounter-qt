#ifndef TST_TBLS_H
#define TST_TBLS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../../utils/tables_utils.h"

using namespace testing;

namespace DB::Tables {

/// *** init objects *** ///
auto currency = CreateScope<DB::Tables::QCurrency>(db);
auto symbols = CreateScope<DB::Tables::QCurrencySymbol>(db);
auto icon = CreateScope<DB::Tables::QIcon>(db);
auto cashAccsCateg = CreateScope<DB::Tables::CashAccoutCategory>(db);
auto cashAcc = CreateScope<DB::Tables::CashAccount>(db);

/// *** open db *** ///
TEST(tables_start_test, open_db) {
    ASSERT_TRUE(openDB());
}
/// *** *** ///

/// *** currency tables tests *** ///
TEST(currency_table_test, create_table) {
    currency->CreateTable();
    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::Currency::tableDB() + "';";

    auto [query, result] = currency->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::Currency::tableDB());
}

TEST(currency_table_test, add_test) {
    currency->Add(Models::Currency {
                      1, "Доллар США", Symbols {
                      }
                  });
    currency->Add(Models::Currency {
                      2, "Евро", Symbols {
                      }
                  });

    QString text = "select " + DB::Tables::Data::Currency::nameColumnDB()
            + " from " + DB::Tables::Data::Currency::tableDB()
            + " where " + DB::Tables::Data::Currency::idColumnDB()
            + " = '2';";
    auto [query, result] = currency->MakeQuery(text);
    ASSERT_TRUE(result);
    if(query->next()) {
        ASSERT_EQ(query->value(0).toString(), "Евро");
    }
}

TEST(currency_table_test, get_test) {
    auto model = currency->Get(2);

    ASSERT_FALSE(model.isCorrect());
    ASSERT_EQ(model.id, 2);
    ASSERT_EQ(model.name, "Евро");
    ASSERT_TRUE(model.symbols.isEmpty());
}

TEST(currency_table_test, get_all_test) {
    auto models = currency->GetAll();

    ASSERT_EQ(std::size(models), 2);

    ASSERT_FALSE(models.at(0).isCorrect());
    ASSERT_EQ(models.at(0).id, 1);
    ASSERT_EQ(models.at(0).name, "Доллар США");
    ASSERT_TRUE(models.at(0).symbols.isEmpty());

    ASSERT_FALSE(models.at(1).isCorrect());
    ASSERT_EQ(models.at(1).id, 2);
    ASSERT_EQ(models.at(1).name, "Евро");
    ASSERT_TRUE(models.at(1).symbols.isEmpty());
}
/// *** *** ///

/// *** currency symbols table tests *** ///
TEST(currency_table_test, create_table_sym) {
    symbols->CreateTable();
    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::CurrencySymbol::tableDB() + "';";

    auto [query, result] = symbols->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::CurrencySymbol::tableDB());
}

TEST(currency_table_test, add_sym) {
    symbols->Add(Sym { 1, "$", 1 });
    symbols->Add(Sym { 2, "$$", 2 });
    symbols->Add(Sym { 3, "$$$", 1 });

    QString text = "select " + DB::Tables::Data::CurrencySymbol::symbolColumnDB() + ", "
            + DB::Tables::Data::CurrencySymbol::idCorrencyColumnDB()
            + " from " + DB::Tables::Data::CurrencySymbol::tableDB()
            + " where " + DB::Tables::Data::CurrencySymbol::idColumnDB()
            + " = '3';";

    auto [query, result] = currency->MakeQuery(text);
    ASSERT_TRUE(result);
    if(query->next()) {
        ASSERT_EQ(query->value(0).toString(), "$$$");
        ASSERT_EQ(query->value(1).toUInt(), 1);
    }
}

TEST(currency_table_test, get_sym) {
    auto model = symbols->Get(1);
    ASSERT_EQ(1, model.id);
    ASSERT_EQ("$", model.symbol);
    ASSERT_EQ(1, model.idCurrency);

    model = symbols->Get(2);
    ASSERT_EQ(2, model.id);
    ASSERT_EQ("$$", model.symbol);
    ASSERT_EQ(2, model.idCurrency);
}

TEST(currency_table_test, get_by_currency_id_sym) {
    auto models = symbols->GetByCurrencyID(1);

    ASSERT_EQ(2, std::size(models));
    ASSERT_EQ(1, models.at(0).id);
    ASSERT_EQ("$", models.at(0).symbol);
    ASSERT_EQ(1, models.at(0).idCurrency);
    ASSERT_EQ(3, models.at(1).id);
    ASSERT_EQ("$$$", models.at(1).symbol);
    ASSERT_EQ(1, models.at(1).idCurrency);

    models = symbols->GetByCurrencyID(2);
    ASSERT_EQ(1, std::size(models));
    ASSERT_EQ(2, models.at(0).id);
    ASSERT_EQ("$$", models.at(0).symbol);
    ASSERT_EQ(2, models.at(0).idCurrency);
}

TEST(currency_table_test, get_all_sym) {
    auto models = symbols->GetAll();

    ASSERT_EQ(3, std::size(models));

    ASSERT_EQ(1, models.at(0).id);
    ASSERT_EQ("$", models.at(0).symbol);
    ASSERT_EQ(1, models.at(0).idCurrency);

    ASSERT_EQ(2, models.at(1).id);
    ASSERT_EQ("$$", models.at(1).symbol);
    ASSERT_EQ(2, models.at(1).idCurrency);

    ASSERT_EQ(3, models.at(2).id);
    ASSERT_EQ("$$$", models.at(2).symbol);
    ASSERT_EQ(1, models.at(2).idCurrency);
}
/// *** *** ///

TEST(icon_table_test, CreateTable) {
    icon->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::Icon::tableDB() + "';";

    auto [query, result] = icon->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::Icon::tableDB());
}

TEST(icon_table_test, Add) {
    icon->Add(Models::Icon {1, "path1"});
    icon->Add(Models::Icon {2, "path12"});
    icon->Add(Models::Icon {3, "path123"});

    QString text = "select " + DB::Tables::Data::Icon::pathColumnDB()
            + " from " + DB::Tables::Data::Icon::tableDB()
            + " where " + DB::Tables::Data::Icon::idColumnDB()
            + " = '3';";

    auto [query, result] = icon->MakeQuery(text);
    ASSERT_TRUE(result);
    if(query->next()) {
        ASSERT_EQ(query->value(0).toString(), "path123");
    }
}

TEST(icon_table_test, Get) {
    auto m = icon->Get(1);
    ASSERT_TRUE(m.isCorrect());
    ASSERT_EQ(m.id, 1);
    ASSERT_EQ(m.path, "path1");

    m = icon->Get(3);
    ASSERT_TRUE(m.isCorrect());
    ASSERT_EQ(m.id, 3);
    ASSERT_EQ(m.path, "path123");
}

TEST(icon_table_test, GetAll) {
    auto models = icon->GetAll();

    ASSERT_EQ(std::size(models), 3);
    ASSERT_TRUE(models.at(0).isCorrect());
    ASSERT_EQ(models.at(0).id, 1);
    ASSERT_EQ(models.at(0).path, "path1");

    ASSERT_TRUE(models.at(1).isCorrect());
    ASSERT_EQ(models.at(1).id, 2);
    ASSERT_EQ(models.at(1).path, "path12");

    ASSERT_TRUE(models.at(2).isCorrect());
    ASSERT_EQ(models.at(2).id, 3);
    ASSERT_EQ(models.at(2).path, "path123");
}

TEST(cash_accs_categ_table_test, CreateTable) {
    cashAccsCateg->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::CashAccountCategory::tableDB() + "';";

    auto [query, result] = cashAccsCateg->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::CashAccountCategory::tableDB());
}

TEST(cash_accs_categ_table_test, Add) {
    Category model_1;
    model_1.id = 13;
    model_1.name = "test";
    model_1.settings.isIncludeDebt = 0;
    model_1.settings.isIncludeRefund = 1;
    model_1.settings.isIncludePurpose = 1;
    model_1.description = "test descr";

    Category model_2;
    model_2.id = 132;
    model_2.name = "test2";

    cashAccsCateg->Add(model_1);
    cashAccsCateg->Add(model_2);
}

TEST(cash_accs_categ_table_test, Get) {
    auto m2 = cashAccsCateg->Get(132);
    auto m1 = cashAccsCateg->Get(13);
    auto m3 = cashAccsCateg->Get(3);

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

TEST(cash_accs_categ_table_test, GetAll) {
    auto list = cashAccsCateg->GetAll();
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

TEST(cash_acc_table_test, CreateTable) {
    cashAcc->CreateTable();

    QString text = "select DISTINCT tbl_name from sqlite_master where tbl_name = '" + DB::Tables::Data::CashAccount::tableDB() + "';";

    auto [query, result] = cashAcc->MakeQuery(text);
            ASSERT_TRUE(result);

            QString answer = "";
            if (query->next()) {
        answer = query->value(0).toString();
    }

    ASSERT_EQ(answer, DB::Tables::Data::CashAccount::tableDB());
}

TEST(cash_acc_table_test, Add) {
    Models::CashAccount model;
    model.id = 1;
    model.name = "name1";
    model.icon.id = 1;
    model.currency.id = 1;
    model.category.id = 1;
    cashAcc->Add(model);

    model.id = 2;
    model.name = "name2";
    model.icon.id = 1;
    model.currency.id = 2;
    model.category.id = 2;
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
    model.category.id = 2;
    cashAcc->Edit(model);

    Models::CashAccount model2;
    model2.id = 2;
    model2.name = "test222";
    model2.icon.id = 1;
    model2.currency.id = 1;
    model2.category.id = 1;
    cashAcc->Edit(model2);
}

TEST(cash_acc_table_test, Get) {
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
    qDebug() << m2.name;
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
    ASSERT_EQ(m2.category.id, 1);
}

TEST(cash_acc_table_test, GetAll) {
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
    ASSERT_EQ(mdls.at(1).icon.id, 1);
    ASSERT_EQ(mdls.at(1).currency.id, 1);
    ASSERT_EQ(mdls.at(1).category.id, 1);

}

TEST(cash_acc_table_test, Remove) {
    cashAcc->Remove(1);

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
    ASSERT_EQ(mdls.at(0).icon.id, 1);
    ASSERT_EQ(mdls.at(0).currency.id, 1);
    ASSERT_EQ(mdls.at(0).category.id, 1);
}

/// *** close db *** ///
TEST(tables_end_test, drop_db) {
    dropDB();
}
/// *** *** ///
}

#endif // TST_CURRENCY_TBL_H
