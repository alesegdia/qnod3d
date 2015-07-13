#-------------------------------------------------
#
# Project created by QtCreator 2015-07-13T02:11:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qnod3d
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customglwidget.cpp \
    geometryengine.cpp \
    nodefactory.cpp

HEADERS  += mainwindow.h \
    customglwidget.h \
    geometryengine.h \
    nodefactory.h

FORMS    += mainwindow.ui
