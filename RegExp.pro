#-------------------------------------------------
#
# Project created by QtCreator 2020-07-12T10:15:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RegExp
TEMPLATE = app

win32: RC_ICONS = $$PWD/bin/images/app.ico

QMAKE_TARGET_COMPANY = BearWin
QMAKE_TARGET_PRODUCT = RegExp search
QMAKE_TARGET_DESCRIPTION = RegExp
QMAKE_TARGET_COPYRIGHT = BearWin


SOURCES += main.cpp\
                     mainwindow.cpp \
                     linkdialog.cpp

HEADERS  += mainwindow.h \
                      linkdialog.h

FORMS    += mainwindow.ui \
                     linkdialog.ui

RESOURCES += \
                    bin/res.qrc
