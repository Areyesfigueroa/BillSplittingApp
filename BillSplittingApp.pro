#-------------------------------------------------
#
# Project created by QtCreator 2016-11-30T14:11:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BillSplittingApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    creategroupdialog.cpp \
    group.cpp \
    grouprecords.cpp

HEADERS  += mainwindow.h \
    creategroupdialog.h \
    group.h \
    grouprecords.h

FORMS    += mainwindow.ui \
    creategroupdialog.ui
