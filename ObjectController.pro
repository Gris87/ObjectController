#-------------------------------------------------
#
# Project created by QtCreator 2012-08-02T10:06:29
#
#-------------------------------------------------

include (src/dump/dump.pri)

QT       += core gui

TARGET = ObjectController
TEMPLATE = app

RC_FILE = Resources.rc
RESOURCES += Resources.qrc

CONFIG (debug, debug|release) {
    DESTDIR = debug/
    OBJECTS_DIR = debug/gen
    MOC_DIR = debug/gen
    RCC_DIR = debug/gen
} else {
    DESTDIR = release/
    OBJECTS_DIR = release/gen
    MOC_DIR = release/gen
    RCC_DIR = release/gen
}

SOURCES +=  src/main.cpp\
            src/main/mainwindow.cpp \
            src/other/global.cpp

HEADERS  += src/main/mainwindow.h \
            src/other/global.h

FORMS    += src/main/mainwindow.ui
