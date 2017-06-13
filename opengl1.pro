#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -lglut32 \
            -lglu32 \
            -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengl1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp \
    ball.cpp \
    gameobject.cpp \
    flipper.cpp

HEADERS  += mainwindow.h \
    oglwidget.h \
    ball.h \
    gameobject.h \
    flipper.h

FORMS    += mainwindow.ui
