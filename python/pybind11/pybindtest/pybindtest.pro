#-------------------------------------------------
#
# Project created by QtCreator 2018-09-08T09:21:01
#
#-------------------------------------------------

QT       -= gui #core

#TARGET = pybindtest.cpython-27-darwin
TARGET = pybindtest.cpython-36m-darwin
CONFIG += plugin
QMAKE_LFLAGS_PLUGIN -= -dynamiclib
QMAKE_LFLAGS_PLUGIN += -bundle
QMAKE_EXTENSION_SHLIB = so
CONFIG += no_plugin_name_prefix
#QMAKE_PREFIX_SHLIB = ""

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
# Settings for mac port python 3.6
QMAKE_CXXFLAGS += -I/opt/local/Library/Frameworks/Python.framework/Versions/3.6/include/python3.6m -I/Users/kaestner/Library/Python/3.6/include/python3.6m -Wno-unused-result -Wsign-compare -Wunreachable-code -fno-common -dynamic -DNDEBUG -g -fwrapv -O3 -Wall -pipe -Os
LIBS += -L/opt/local/Library/Frameworks/Python.framework/Versions/3.6/lib/python3.6/config-3.6m-darwin -lpython3.6m -ldl -framework CoreFoundation

# Settings for anaconda python 3.6
#QMAKE_CXXFLAGS += -I/anaconda3/include/python3.6m -Wno-unused-result -Wsign-compare -Wunreachable-code -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes -I/anaconda3/include -arch x86_64
#LIBS += -L/anaconda3/lib/python3.6/config-3.6m-darwin -lpython3.6m -ldl -framework CoreFoundation

# Setting work with default python 2.7
#QMAKE_CXXFLAGS += -I/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -fno-strict-aliasing -fno-common -dynamic -arch x86_64 -arch i386 -g -Os -pipe -fno-common -fno-strict-aliasing -fwrapv -DENABLE_DTRACE -DMACOSX -DNDEBUG -Wall -Wstrict-prototypes -Wshorten-64-to-32 -DNDEBUG -g -fwrapv -Os -Wall -Wstrict-prototypes -DENABLE_DTRACE
#LIBS += -L/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config -lpython2.7 -ldl -framework CoreFoundation

DISTFILES += \
    tester.py
