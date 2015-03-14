#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T10:52:41
#
#-------------------------------------------------

QT       += core webkitwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = curso-qt-osl-notepad.exe
TEMPLATE = app


SOURCES += main.cpp\
        notepadwindow.cpp \
    ventana_buscador.cpp

HEADERS  += notepadwindow.h \
    ventana_buscador.hpp

CONFIG += c++11

RC_ICONS = icono.ico
RESOURCES += \
    recursos.qrc

FORMS += \
    ventana_buscador.ui
