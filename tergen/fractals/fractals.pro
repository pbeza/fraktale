QT       += core gui opengl widgets
CONFIG   += C++14

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
