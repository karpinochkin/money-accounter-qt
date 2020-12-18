QT       += core gui sql
QT += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#TEMPLATE = subdirs
#SUBDIRS += tests/tests.pro

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    resources/data_resources.qrc \
    resources/icon_resources.qrc \
    src/gui/qml/qml.qrc

SOURCES += \
    src/core/qappstarter.cpp \
    src/core/qmiddlewareqml.cpp \
    src/database/controllers/tablecontrollers.cpp \
    src/database/dbdispatcher.cpp \
    src/database/fillers/dbdefaultfillers.cpp \
    src/database/tables/basetable.cpp \
    src/database/tables/cashaccouttable.cpp \
    src/database/tables/categorytable.cpp \
    src/database/tables/currencytable.cpp \
    src/database/tables/icontable.cpp \
    src/database/tables/transactiontable.cpp \
    src/main.cpp \
    src/utils/qparser.cpp

HEADERS += \
    src/core/base.h \
    src/core/qappstarter.h \
    src/core/qmiddlewareqml.h \
    src/database/controllers/tablecontrollers.h \
    src/database/dbdispatcher.h \
    src/database/fillers/dbdefaultfillers.h \
    src/database/tables/basetable.h \
    src/database/tables/cashaccouttable.h \
    src/database/tables/categorytable.h \
    src/database/tables/currencytable.h \
    src/database/tables/icontable.h \
    src/database/tables/tables.h \
    src/database/tables/transactiontable.h \
    src/models/basemodel.h \
    src/models/category.h \
    src/models/color.h \
    src/models/cashaccount.h \
    src/models/currency.h \
    src/models/icon.h \
    src/models/transaction.h \
    src/utils/qparser.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/gui/qml/Delegates/TabsDelegate.qml \
    src/gui/qml/main.qml

