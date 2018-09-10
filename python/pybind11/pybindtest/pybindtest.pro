#-------------------------------------------------
#
# Project created by QtCreator 2018-09-08T09:21:01
#
#-------------------------------------------------

QT       -= gui

TARGET = pybindtest.cpython-36m-darwin
#TARGET = pybindtest`python3.6m-config --extension-suffix` # doesn't seem to work
TEMPLATE = lib
CONFIG += c++11

DEFINES += PYBINDTEST_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -fPIC
#QMAKE_CXXFLAGS += `python3.6m -m pybind11 --includes` # doesn't seem to work
#QMAKE_CXXFLAGS += `python3.6m-config --libs` # doesn't seem to work

SOURCES += \
        pybindtest.cpp

HEADERS += \
        pybindtest.h \
        pybindtest_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../../../../imagingsuite/external/src/pybind11/2.2.3/include/

# these are from python config on the cmd line
INCLUDEPATH += /Users/kaestner/anaconda3/include/python3.6m -I/Users/kaestner/.local/include/python3.6m
LIBS += -L/Users/kaestner/anaconda3/lib -lpython3.6m -ldl -framework CoreFoundation
