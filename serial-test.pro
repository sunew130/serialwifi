#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T16:05:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = serial-test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    thread.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp \
    qprocessdata.cpp \
    thread2.cpp \
    thread3.cpp \
    thread4.cpp \
    thread5.cpp

HEADERS += \
    thread.h \
    qextserialport.h \
    qextserialbase.h \
    posix_qextserialport.h \
    qprocessdata.h \
    thread2.h \
    thread3.h \
    thread4.h \
    thread5.h
