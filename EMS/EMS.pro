#-------------------------------------------------
#
# Project created by QtCreator 2015-07-21T09:11:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EMS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sellfirst.cpp \
    sellsecond.cpp \
    login.cpp \
    userpwd.cpp \
    userlimit.cpp \
    core/dataOp.cpp \
    core/fileOp.cpp \
    core/tablegoods.cpp \
    core/tableusers.cpp \
    core/tablevip.cpp \
    buygoods.cpp \
    core/sellManage.cpp \
    core/tableSell.cpp \
    core/tableSellList.cpp \
    SaleInfo.cpp \
    ProAdiministration.cpp \
    ProInfo.cpp \
    VIPAdministration.cpp \
    VIPInfo.cpp

HEADERS  += mainwindow.h \
    sellfirst.h \
    sellsecond.h \
    login.h \
    userpwd.h \
    userlimit.h \
    core/dataOp.h \
    core/fileOp.h \
    core/tablegoods.h \
    core/tableusers.h \
    core/tablevip.h \
    buygoods.h \
    ProAdiministration.h \
    ProInfo.h \
    VIPAdministration.h \
    VIPInfo.h \
    core/sellManage.h \
    core/tableSell.h \
    core/tableSellList.h \
    SaleInfo.h

FORMS    += mainwindow.ui \
    sellfirst.ui \
    sellsecond.ui \
    login.ui \
    userpwd.ui \
    userlimit.ui \
    buygoods.ui \
    ProAdiministration.ui \
    ProInfo.ui \
    VIPAdministration.ui \
    VIPInfo.ui \
    SaleInfo.ui
