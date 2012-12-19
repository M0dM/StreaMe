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

LIBS     += $$PWD/libav-win64-20121113/usr/bin/avcodec.lib \
         $$PWD/libav-win64-20121113/usr/bin/avdevice.lib \
         $$PWD/libav-win64-20121113/usr/bin/avfilter.lib \
         $$PWD/libav-win64-20121113/usr/bin/avformat.lib \
         $$PWD/libav-win64-20121113/usr/bin/avresample.lib \
         $$PWD/libav-win64-20121113/usr/bin/avutil.lib \
         $$PWD/libav-win64-20121113/usr/bin/swscale.lib \
         -L*$$PWD/vlc/sdk/lib/libvlc.lib* \
         -L*$$PWD/vlc/sdk/lib/libvlccore.lib*

RESOURCES += \
    New.qrc
