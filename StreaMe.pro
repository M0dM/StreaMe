#-------------------------------------------------
#
# Project created by QtCreator 2012-12-03T12:17:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StreaMe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    project.cpp \
    source.cpp \
    live.cpp \
    controller.cpp \

HEADERS  += mainwindow.h \
    project.h \
    source.h \
    live.h \
    controller.h

FORMS    += mainwindow.ui

LIBS     += libav-win64-20121113/usr/bin/avcodec.lib \
         libav-win64-20121113/usr/bin/avdevice.lib \
         libav-win64-20121113/usr/bin/avfilter.lib \
         libav-win64-20121113/usr/bin/avformat.lib \
         libav-win64-20121113/usr/bin/avresample.lib \
         libav-win64-20121113/usr/bin/avutil.lib \
         libav-win64-20121113/usr/bin/swscale.lib
LIBS     += -L"C:\Program Files (x86)\VideoLAN\VLC\sdk\lib\libvlc.lib" \
         -L"C:\Program Files (x86)\VideoLAN\VLC\sdk\lib\libvlccore.lib" \
         -lvlc

INCLUDEPATH += $$PWD/C:/Programes Files (x86)/VideoLAN/VLC/sdk/include

RESOURCES += \
    New.qrc
