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
    playlist.cpp \
    optionbar.cpp \
    audioengine.cpp

HEADERS  += \
    customwindow.h \
    windowtitlebar.h \
    windowbutton.h \
    musicplayer.h \
    volumebutton.h \
    playlist.h \
    optionbar.h \
    audioengine.h


LIBS += "C:/MinGW/msys/1.0/home/anobis/taglib-1.9.1/taglib/libtag.dll.a"
LIBS += "C:/MinGW/msys/1.0/home/anobis/mpg123-1.20.0/src/libmpg123/.libs/libmpg123.dll.a"
LIBS += "C:/MinGW/msys/1.0/home/anobis/libao-1.1.0/src/.libs/libao.dll.a"

INCLUDEPATH += c:/MinGw/msys/1.0/home/anobis/taglib-1.9.1 c:/MinGw/msys/1.0/home/anobis/taglib-1.9.1/taglib
INCLUDEPATH += c:/MinGW/msys/1.0/home/anobis/mpg123-1.20.0/src c:/MinGW/msys/1.0/home/anobis/mpg123-1.20.0/src/libmpg123
INCLUDEPATH += c:/MinGw/msys/1.0/home/anobis/libao-1.1.0/include