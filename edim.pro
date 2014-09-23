QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = edim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    documenthandler.cpp

HEADERS  += mainwindow.h \
    documenthandler.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
