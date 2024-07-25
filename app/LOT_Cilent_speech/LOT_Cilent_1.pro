#-------------------------------------------------
#
# Project created by QtCreator 2024-05-12T18:39:41
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LOT_Cilent_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    http.cpp \
    speech.cpp \
    audio.cpp

HEADERS  += widget.h \
    http.h \
    speech.h \
    audio.h

FORMS    += widget.ui

# LIBS += D:\Embedded_learning\smart_home_Project\build-qtmqtt-Desktop_Qt_5_8_0_MinGW_32bit-Debug\lib\lib*.a
LIBS += D:\Embedded_learning\smart_home_Project\build-qtmqtt-Desktop_Qt_5_8_0_MinGW_32bit-Debug\lib\Qt*.dll
