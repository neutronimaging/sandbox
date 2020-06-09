QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

unix:!macx {
    QMAKE_CXXFLAGS += -fopenmp -fPIC -O2
    QMAKE_LFLAGS += -lgomp
    LIBS += -lgomp
}

unix:macx {
    QMAKE_CXXFLAGS += -fPIC -O2
    INCLUDEPATH += /opt/local/include
    QMAKE_LIBDIR += /opt/local/lib

}

INCLUDEPATH += $$PWD/../../../imagingsuite/external/src/armadillo-9.800.2/include/
SOURCES +=  tst_armadillotests.cpp

LIBS += -L$$PWD/../../../imagingsuite/external/lib64
LIBS += -larmadillo -lblas -llapack
