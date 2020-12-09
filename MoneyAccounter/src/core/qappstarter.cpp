#include "qappstarter.h"

QAppStarter::QAppStarter(QObject *parent) : QObject(parent)
{
    engine = CreateScope<QQmlApplicationEngine>(this);
    middleware = CreateScope<QMiddlewareQML>(this);
    connect(engine.get(), &QQmlApplicationEngine::warnings,
            this, &QAppStarter::saveQmlEngineWarnings);

    engine->rootContext()->setContextProperty("middlewareQML", middleware.get());
    engine->rootContext()->setContextProperty("qmlProperty", middleware->qmlProperty.get());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine->load(url);

    if (engine->rootObjects().isEmpty())
        qApp->exit(-1);
}

void QAppStarter::saveQmlEngineWarnings(const QList<QQmlError> &listError)
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QFile file(folder + "/qmlEngineError.txt");

    for (auto err : listError) {
        if (file.open(QIODevice::Append)) {
            QTextStream stream( &file );
            stream << "\n" << QDateTime::currentDateTime().toString()
                   << ": " << err.toString() << "\n";
        }
    }

    file.close();
}
