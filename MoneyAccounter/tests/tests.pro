include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += thread
CONFIG += core
QT += sql
QT += core

HEADERS += \
        ../src/database/controllers/tablecontrollers.h \
        ../src/database/tables/basetable.h \
    ../src/database/tables/cashaccouttable.h \
    ../src/database/tables/categorytable.h \
        ../src/database/tables/currencytable.h \
    ../src/database/tables/icontable.h \
        ../src/database/tables/tables.h \ \
    ../src/models/color.h \
    ../src/models/currency.h \
    ../src/utils/qparser.h \
    database/controllers/tst_cntrls.h \
    database/tables/tst_tbls.h \
    models/tst_models.h \
    utils/db_utils.h \
    utils/models_utils.h \
    utils/tables_utils.h \
    utils/tst_parser.h

SOURCES += \
        ../src/database/controllers/tablecontrollers.cpp \
        ../src/database/tables/basetable.cpp \
        ../src/database/tables/cashaccouttable.cpp \
        ../src/database/tables/categorytable.cpp \
        ../src/database/tables/currencytable.cpp \
        ../src/database/tables/icontable.cpp \
        ../src/utils/qparser.cpp \
        main.cpp
