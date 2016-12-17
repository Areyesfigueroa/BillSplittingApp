#-------------------------------------------------
#
# Project created by QtCreator 2016-11-30T14:11:55
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BillSplittingApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    creategroupdialog.cpp \
    group.cpp \
    grouprecords.cpp \
    editgroupdialog.cpp \
    friendsdialog.cpp \
    person.cpp \
    peoplerecords.cpp \
    billoptionsdialog.cpp \
    testfunctions.cpp \
    dbmanager.cpp

HEADERS  += mainwindow.h \
    creategroupdialog.h \
    group.h \
    grouprecords.h \
    editgroupdialog.h \
    friendsdialog.h \
    person.h \
    records.h \
    peoplerecords.h \
    billoptionsdialog.h \
    testfunctions.h \
    dbmanager.h

FORMS    += mainwindow.ui \
    creategroupdialog.ui \
    editgroupdialog.ui \
    friendsdialog.ui \
    billoptionsdialog.ui
