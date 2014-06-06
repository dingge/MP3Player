#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T15:28:32
#
#-------------------------------------------------

QT       += core gui multimedia winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = basic
TEMPLATE = app


SOURCES += main.cpp \
    customwindow.cpp \
    windowtitlebar.cpp \
    windowbutton.cpp \
    musicplayer.cpp \
    volumebutton.cpp \
    playlist.cpp

HEADERS  += \
    customwindow.h \
    windowtitlebar.h \
    windowbutton.h \
    musicplayer.h \
    volumebutton.h \
    playlist.h

FORMS    += mainwindow.ui
