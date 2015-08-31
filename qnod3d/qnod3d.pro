QT       += core gui widgets

TARGET = qnod3d
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    customglwidget.cpp \
    geometryengine.cpp \
    nodefactory.cpp \
    itool.cpp \
    node.cpp \
    scenetransform.cpp \
    scenetransformtool.cpp \
    mousedragtool.cpp

HEADERS  += mainwindow.h \
    customglwidget.h \
    geometryengine.h \
    nodefactory.h \
    itool.h \
    node.h \
    scenetransform.h \
    scenetransformtool.h \
    mousedragtool.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    shaders.qrc \
    textures.qrc

CONFIG += c++11
