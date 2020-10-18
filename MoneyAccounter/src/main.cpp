#include <QApplication>

#include "database/dbdispatcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);{
        Scope<DB::QDispatcher> dispatcher;
        try {

            dispatcher = CreateScope<DB::QDispatcher>("db_money_accounter.db", &a);
//            auto list = dispetcher->Currency()->GetAll();

//            for (auto l : list) {
//                qDebug() << l.id << l.name;
//            }


        } catch (const DB::ExceptionDB& err) {
            qDebug() << "ERR";
            qDebug() << err.what();
        }
    }

    return a.exec();
}
