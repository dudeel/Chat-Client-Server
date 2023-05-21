QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerTest
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
s
SOURCES += \
        main.cpp \
        servertest.cpp \
    serverhandler.cpp \
    imageform.cpp

HEADERS += \
        servertest.h \
    serverhandler.h \
    imageform.h

FORMS += \
        servertest.ui \
    imageform.ui
