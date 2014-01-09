#-------------------------------------------------
#
# Project created by QtCreator 2013-12-10T21:01:11
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CubipixProject
TEMPLATE = app


SOURCES += main.cpp\
        cubipix.cpp \
    map.cpp \
    player.cpp \
    playertimer.cpp \
    mapeditor.cpp

HEADERS  += cubipix.h \
    map.h \
    player.h \
    playertimer.h \
    mapeditor.h

FORMS    += cubipix.ui \
    mapeditor.ui

RESOURCES += \
    ressources.qrc
