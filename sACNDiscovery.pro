#-------------------------------------------------
#
# Project created by QtCreator 2014-09-06T11:22:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sACNDiscovery
TEMPLATE = app

CONFIG    += link_pkgconfig
PKGCONFIG += "libola libolaacn libolae131conf"

SOURCES += main.cpp\
        mainwindow.cpp \
        olaworker.cpp \
    treeitem.cpp \
    treemodel.cpp

HEADERS  += mainwindow.h \
            olaworker.h \
    treeitem.h \
    treeitem.h \
    treemodel.h

FORMS    += mainwindow.ui
