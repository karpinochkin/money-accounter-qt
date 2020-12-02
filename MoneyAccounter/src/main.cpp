#include <QApplication>

#include "database/dbdispatcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);{
        Scope<DB::QDispatcher> dispatcher;
        try {

            dispatcher = CreateScope<DB::QDispatcher>("db_money_accounter.db", &a);
            Models::Transaction tr1;
            qDebug() << dispatcher->Transaction().Add(tr1);

            Models::Category category_;
            category_.id = 33;
            category_.name = "testremovename33";
            category_.currency.id = 2;
            category_.icon.id = 2;
            qDebug() << "category add :" << dispatcher->Category().Add(category_);
            auto m1 = dispatcher->Category().Get(33);
            qDebug() << m1.id << m1.name << m1.currency.id;

            Models::CashAccount cash;
            cash.id = 33;
            cash.name = "testcashacc33";
            cash.icon.id = 2;
            cash.type.id = 2;
            cash.currency.id = 2;
            qDebug() << "cash acc add :" << dispatcher->CashAccount().Add(cash);

            Models::Transaction tr;
            tr.id = 33;
            tr.name = "testtransactionname33";
            tr.category.id = 33;
            tr.datetime = QDateTime::currentDateTime();
            tr.cashAccount.id = 33;
            qDebug() << "transaction add : " << dispatcher->Transaction().Add(tr);
            auto model = dispatcher->Transaction().Get(33);
            qDebug() << "transaction get : " << model.id << model.name << model.datetime << model.sum.getAsDouble() << model.category.id << model.cashAccount.id;

            auto ms = dispatcher->Transaction().GetAll();
            qDebug() << "FIRST : " << ms.at(0).id << ms.at(0).name << ms.at(0).datetime.toString() << ms.at(0).sum.getAsDouble() << ms.at(0).category.id << ms.at(0).cashAccount.id;

            dispatcher->Category().Remove(33);
            ms = dispatcher->Transaction().GetAll();
            qDebug() << std::size(ms);
            qDebug() << "SECOND REMOVE CATEGORY" << ms.at(0).id << ms.at(0).name << ms.at(0).datetime.toString() << ms.at(0).sum.getAsDouble() << ms.at(0).category.id << ms.at(0).cashAccount.id;

            dispatcher->CashAccount().Remove(33);
            ms = dispatcher->Transaction().GetAll();
            qDebug() << std::size(ms);
            qDebug() << "THIRD REMOVE CASH ACC" << ms.at(0).id << ms.at(0).name << ms.at(0).datetime.toString() << ms.at(0).sum.getAsDouble() << ms.at(0).category.id << ms.at(0).cashAccount.id;

            tr.id = 88;
            dispatcher->Transaction().Add(tr);

        } catch (const DB::ExceptionDB& err) {
            qDebug() << "ERR";
            qDebug() << err.what();
        }
    }

    return a.exec();
}
