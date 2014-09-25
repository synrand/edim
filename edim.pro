QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = edim
TEMPLATE = app

LIBS += \
    -ltesseract \
    -llept

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    documenthandler.cpp \
    settingsdialog.cpp

HEADERS += \
    mainwindow.h \
    documenthandler.h \
    settingsdialog.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    resources.qrc
