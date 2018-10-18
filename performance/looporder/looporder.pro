QT += testlib
QT -= gui



CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++11

CONFIG(release, debug|release): DESTDIR = $$PWD/../../../lib
else:CONFIG(debug, debug|release): DESTDIR = $$PWD/../../../lib/debug

TEMPLATE = app

SOURCES +=  tst_loops.cpp \
    looper.cpp

HEADERS += \
    looper.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../lib/release/ -lkipl.1.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../lib/debug/ -lkipl.1.0.0
else:unix: LIBS += -L$$PWD/../../../lib/ -lkipl.1.0.0

INCLUDEPATH += $$PWD/../../../imagingsuite/core/kipl/kipl/include
DEPENDPATH += $$PWD/../../../imagingsuite/core/kipl/kipl/include
