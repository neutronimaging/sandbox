QT += testlib
QT -= gui

CONFIG += c++11

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_innerloop.cpp \
    loops.cpp

HEADERS += \
    loops.h
