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
