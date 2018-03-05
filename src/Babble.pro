#-------------------------------------------------
#
# Project created by QtCreator 2018-03-02T22:43:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Babble
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        babblemainwindow.cpp \
        cryptoutils.cpp \
        settingsdialog.cpp

HEADERS += \
        babblemainwindow.h \
        cryptoutils.h \
        settingsdialog.h

FORMS += \
        babblemainwindow.ui \
        settingsdialog.ui

LIBS += -lsodium
