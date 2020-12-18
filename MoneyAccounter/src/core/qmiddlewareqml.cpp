#include "qmiddlewareqml.h"

QMiddlewareQML::QMiddlewareQML(QObject *parent) : QObject(parent)
{
    createObjects();
    connects();
}

void QMiddlewareQML::createObjects()
{
    try {
        dispatcher = CreateScope<DB::QDispatcher>("db_money_accounter.db", this);
        qmlProperty = CreateScope<QQmlPropertyMap>(this);
    }
    catch (const DB::ExceptionDB& err) {
        qmlProperty->insert("error", QVariant(err.what()));
        emit (signalErrorResponse());
    }
}

void QMiddlewareQML::connects()
{
    //    connect(routers->QuestionControllers(), &QQuestionController::signalGetRandom,
    //            this, &QMiddlewareQML::randomQuestionLoaded);
    //    connect(routers, &QRouters::ErrorResponse, this, [=](QString err) {
    //        try {
    //            int index = err.toStdString().find("server replied");
    //            auto errorDisplayText = QString::fromStdString(err.toStdString().substr(index, err.size()));
    //            qmlProperty->insert("errorResponse", QVariant(errorDisplayText));
    //            emit (signalErrorResponse());
    //        } catch(...) {
    //            auto errorDisplayText = "Отказано в соединении";
    //            qmlProperty->insert("errorResponse", QVariant(errorDisplayText));
    //            emit (signalErrorResponse());
    //        }
    //    });
}

bool QMiddlewareQML::isAndroid()
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

void QMiddlewareQML::exitApp()
{
    qGuiApp->quit();
}

void QMiddlewareQML::loadAllCashAccount()
{
    auto cashAccs = dispatcher->CashAccount().GetAll();
    std::sort(std::begin(cashAccs), std::end(cashAccs), [](const MCashAcc& acc1, const MCashAcc& acc2) {
        return acc1.type.id > acc2.type.id;
    });
    std::for_each(std::begin(cashAccs), std::end(cashAccs), [=](const MCashAcc& acc) {
        qDebug() << acc.id << acc.name << acc.color.hex();
        qmlProperty->insert("idCashAcc", acc.id);
        qmlProperty->insert("nameCashAcc", acc.name);
        qmlProperty->insert("descriptionCashAcc", acc.description);
        qmlProperty->insert("debtCashAcc", acc.debt.getAsDouble());
        qmlProperty->insert("iconIdCashAcc", acc.icon.id);
        qmlProperty->insert("iconPathCashAcc", acc.icon.path);
        qmlProperty->insert("typeIdCashAcc", acc.type.id);
        qmlProperty->insert("typeNameCashAcc", acc.type.name);
        qmlProperty->insert("typeDescriptionCashAcc", acc.type.description);
        qmlProperty->insert("typeIsIncludeDebtCashAcc", acc.type.settings.isIncludeDebt);
        qmlProperty->insert("typeIsIncludeRefundCashAcc", acc.type.settings.isIncludeRefund);
        qmlProperty->insert("typeIsIncludePruposeCashAcc", acc.type.settings.isIncludePurpose);
        qmlProperty->insert("colorCashAcc", acc.color.hex());
        qmlProperty->insert("refundCashAcc", acc.refund.getAsDouble());
        qmlProperty->insert("balanceCashAcc", acc.balance.getAsDouble());
        qmlProperty->insert("purposeCashAcc", acc.purpose.getAsDouble());
        qmlProperty->insert("currencyIdCashAcc", acc.currency.id);
        qmlProperty->insert("currencyNameCashAcc", acc.currency.name);
        qmlProperty->insert("currencySymbolCashAcc", acc.currency.symbol);
        qmlProperty->insert("displayInExpensesCashAcc", acc.settings.displayInExpenses);
        qmlProperty->insert("displayInOverallBalanceCashAcc", acc.settings.displayInOverallBalance);


        emit (signalCashAccountLoaded());
    });
}
