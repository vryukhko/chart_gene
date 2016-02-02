#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T10:33:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gene_chart
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    record.cpp \
    graphwidget.cpp

HEADERS  += mainwindow.h \
    record.h \
    data.h \
    graphwidget.hpp

FORMS    += mainwindow.ui
