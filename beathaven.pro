#-------------------------------------------------
#
# Project created by QtCreator 2011-11-25T23:06:13
#
#-------------------------------------------------

QT       += core gui phonon

CONFIG  += qxt
QXT     += core gui

INCLUDEPATH += /usr/include/qxt/QxtCore
INCLUDEPATH += /usr/include/qxt/QxtGui

LIBS += /usr/lib/libQxtCore.so
LIBS += /usr/lib/libQxtGui.so

TARGET = beathaven
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    data/track.cpp

HEADERS  += mainwindow.h \
    data/track.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
