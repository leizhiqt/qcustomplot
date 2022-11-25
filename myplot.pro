buildDir = $$PWD/build/win64
TARGET_ARCH = x64

#-------------------------------------------------
#
# Project created by QtCreator 2020-06-10T14:42:44
#
#-------------------------------------------------
QT       += core gui
QT       += widgets printsupport concurrent
#QT       += multimedia

CONFIG += c++11
#CONFIG += c++11 console
CONFIG -= debug_and_release
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myplot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_MESSAGELOGCONTEXT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += 3rd/fftw-3.3.5-dll64
LIBS += -L3rd/fftw-3.3.5-dll64 -llibfftw3-3 -llibfftw3f-3  -llibfftw3l-3

HEADERS += \
        mainwindow.h \
        qcustomplot.h \
        FFTUtil.h

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp \
        FFTUtil.cpp

FORMS += \
        mainwindow.ui

DESTDIR = $$buildDir/bin
MOC_DIR = $$buildDir/temp
RCC_DIR = $$buildDir/temp
OBJECTS_DIR = $$buildDir/temp
UI_DIR = $$PWD/uimain

myplot.path=$${DESTDIR}
INSTALLS += myplot

message("INSTALLS SUCCESSFUL.....")
