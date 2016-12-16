#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T01:09:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dz_reader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tree.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    tree.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
