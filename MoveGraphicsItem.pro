#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T09:49:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MoveGraphicsItem
TEMPLATE = app


SOURCES += main.cpp\
    dijkstra_algorithm.cpp \
    lineitem.cpp \
    sender.cpp \
    widget.cpp \
    moveitem.cpp

HEADERS  += widget.h \
    dijkstra_algorithm.h \
    lineitem.h \
    moveitem.h \
    sender.h

FORMS    += widget.ui \
    sender.ui
