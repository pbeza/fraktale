QT       += core gui
CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fractals
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        algorithm.cpp \
        myglwidget.cpp

HEADERS += mainwindow.h \
        algorithm.h \
        myglwidget.h

FORMS    += mainwindow.ui

DISTFILES += \
    fragmentshader.glsl \
    vertexshader.glsl
