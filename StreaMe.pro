#-------------------------------------------------
#
# Project created by QtCreator 2012-12-03T12:17:05
#
#-------------------------------------------------

QT       += core gui
QT       += phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StreaMe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    project.cpp \
    source.cpp \
    live.cpp \
    controller.cpp \
    winavtools.cpp \
    streamtools.cpp \
    camera.cpp \
    microphone.cpp \
    platformselectionwindow.cpp \
    streamingparametersconfigurationwindow.cpp \
    streamthread.cpp \
    newprojectassistant.cpp \
    renameprojectwindow.cpp \
    choosecreateopenproject.cpp

HEADERS  += mainwindow.h \
    project.h \
    source.h \
    live.h \
    controller.h \
    winavtools.h \
    streamtools.h \
    camera.h \
    microphone.h \
    platformselectionwindow.h \
    streamingparametersconfigurationwindow.h \
    streamthread.h \
    newprojectassistant.h \
    renameprojectwindow.h \
    choosecreateopenproject.h

FORMS    += mainwindow.ui \
    platformselectionwindow.ui \
    streamingparametersconfigurationwindow.ui \
    newprojectassistant.ui \
    renameprojectwindow.ui \
    choosecreateopenproject.ui

RESOURCES += \
    New.qrc
    win32:RC_FILE = streame.rc
