#-------------------------------------------------
#
# Project created by QtCreator 2020-07-12T10:15:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RegExp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linkdialog.cpp

HEADERS  += mainwindow.h \
    linkdialog.h

FORMS    += mainwindow.ui \
    linkdialog.ui

RESOURCES += \
    bin/res.qrc
