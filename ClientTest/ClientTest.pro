QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientTest
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        clienttest.cpp

HEADERS += \
        clienttest.h

FORMS += \
        clienttest.ui
