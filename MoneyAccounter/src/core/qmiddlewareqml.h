#ifndef QMIDDLEWAREQML_H
#define QMIDDLEWAREQML_H

#include <QObject>
#include <QQmlPropertyMap>
#include <QGuiApplication>
#include <QSettings>
#include "base.h"
#include "../database/dbdispatcher.h"

class QMiddlewareQML : public QObject
{
    Q_OBJECT
public:
    explicit QMiddlewareQML(QObject *parent = nullptr);
    ~QMiddlewareQML() = default;

    Scope<QQmlPropertyMap> qmlProperty;
private:
    Scope<DB::QDispatcher> dispatcher;

    void createObjects();
    void connects();

public slots:
    bool isAndroid();
    void exitApp();
    void loadAllCashAccount();

signals:
    void signalErrorResponse();
    void signalCashAccountLoaded();

};

#endif // QMIDDLEWAREQML_H
