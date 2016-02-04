QT       += core gui opengl
CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fractals
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        algorithm.cpp \
        myglwidget.cpp \
    fract.cpp

HEADERS += mainwindow.h \
        algorithm.h \
        myglwidget.h \
    fract.h

FORMS    += mainwindow.ui

DISTFILES += \
    fragmentshader.glsl \
    vertexshader.glsl
