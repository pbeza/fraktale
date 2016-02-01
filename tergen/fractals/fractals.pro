QT       += core gui
CONFIG   +=C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fractals
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    algorithm.cpp

HEADERS  += mainwindow.h \
    algorithm.h

FORMS    += mainwindow.ui
