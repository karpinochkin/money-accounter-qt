#include <QApplication>
#include "core/qappstarter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("ikespil");
    QCoreApplication::setApplicationName("Money Accounter");
    QGuiApplication app(argc, argv);

#ifdef Q_OS_ANDROID
    qApp->setQuitOnLastWindowClosed(false);
#endif

    QAppStarter appSterter;

    return app.exec();
}
