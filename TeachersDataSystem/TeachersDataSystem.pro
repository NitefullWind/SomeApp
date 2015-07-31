#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T09:00:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql

TARGET = TeachersDataSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    connection.h \
    logindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui

RESOURCES += \
    file.qrc
