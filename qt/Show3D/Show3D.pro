QT       += core gui datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG(release, debug|release): DESTDIR = $$PWD/../../../lib
else:CONFIG(debug, debug|release): DESTDIR = $$PWD/../../../lib/debug

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    volumedisplaywidget.cpp

HEADERS += \
    mainwindow.h \
    volumedisplaywidget.h

FORMS += \
    mainwindow.ui \
    volumedisplaywidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /opt/local/include/libxml2

unix:macx {
    INCLUDEPATH += /opt/local/include
    QMAKE_LIBDIR += /opt/local/lib
}

LIBS += -lm -lz -ltiff -lxml2
LIBS += -L"../../../lib" -lkipl -lqtaddons

INCLUDEPATH += "../../../imagingsuite/core/kipl/kipl/include"
INCLUDEPATH += "../../../imagingsuite/GUI/qt/QtAddons"
INCLUDEPATH += "../../../imagingsuite/core/modules/ReaderConfig"

