QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += C++20

TEMPLATE = app

SOURCES +=  tst_strfmt.cpp
