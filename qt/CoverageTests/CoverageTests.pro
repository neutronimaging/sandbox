#-------------------------------------------------
#
# Project created by QtCreator 2018-05-01T11:16:58
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_coverageteststest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

mac {
    QMAKE_CXXFLAGS += --coverage
    QMAKE_LFLAGS += --coverage
}

SOURCES += \
        tst_coverageteststest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-CoverageDummies-Desktop_Qt_5_10_1_clang_64bit-Debug/release/ -lCoverageDummies.1.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-CoverageDummies-Desktop_Qt_5_10_1_clang_64bit-Debug/debug/ -lCoverageDummies.1.0.0
else:unix: LIBS += -L$$PWD/../build-CoverageDummies-Desktop_Qt_5_10_1_clang_64bit-Debug/ -lCoverageDummies.1.0.0

INCLUDEPATH += $$PWD/../CoverageDummies
DEPENDPATH += $$PWD/../CoverageDummies

DISTFILES += \
    runCoverage.sh
