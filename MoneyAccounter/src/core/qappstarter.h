#ifndef QAPPSTARTER_H
#define QAPPSTARTER_H

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QStandardPaths>
#include <QDateTime>
#include <QTextStream>
#include <QQmlContext>
#include "qmiddlewareqml.h"

class QAppStarter : public QObject
{
    Q_OBJECT
public:
    explicit QAppStarter(QObject *parent = nullptr);
    ~QAppStarter() = default;

private:
    Scope<QQmlApplicationEngine> engine;
    Scope<QMiddlewareQML> middleware;

public slots:
    void saveQmlEngineWarnings(const QList<QQmlError> &listError);

};

#endif // QAPPSTARTER_H
