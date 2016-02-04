QT       += core gui opengl widgets
CONFIG   += C++14

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
