QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TEMPLATE = subdirs
SUBDIRS += tests/tests.pro

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    resources/data_resources.qrc \
    resources/icon_resources.qrc

SOURCES += \
    src/database/controllers/tablecontrollers.cpp \
    src/database/dbdispatcher.cpp \
    src/database/fillers/dbdefaultfillers.cpp \
    src/database/tables/basetable.cpp \
    src/database/tables/cashaccouttable.cpp \
    src/database/tables/categorytable.cpp \
    src/database/tables/currencytable.cpp \
    src/database/tables/icontable.cpp \
    src/main.cpp \
    src/utils/qparser.cpp

HEADERS += \
    src/core/base.h \
    src/core/cashaccountsnames.h \
    src/core/currencynames.h \
    src/core/iconsnames.h \
    src/database/controllers/tablecontrollers.h \
    src/database/dbdispatcher.h \
    src/database/fillers/dbdefaultfillers.h \
    src/database/tables/basetable.h \
    src/database/tables/cashaccouttable.h \
    src/database/tables/categorytable.h \
    src/database/tables/currencytable.h \
    src/database/tables/icontable.h \
    src/database/tables/tables.h \
    src/models/category.h \
    src/models/color.h \
    src/models/cashaccount.h \
    src/models/currency.h \
    src/models/icon.h \
    src/utils/qparser.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

