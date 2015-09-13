QT       += core
QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET += Tests
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp



unix:!macx: LIBS += -L$$PWD/../../../GMock/qt/ -lGMock

INCLUDEPATH += $$PWD/../../../GMock/include
DEPENDPATH += $$PWD/../../../GMock/include
INCLUDEPATH += $$PWD/../../../GMock/gtest/include
DEPENDPATH += $$PWD/../../../GMock/gtest/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../GMock/qt/libGMock.a
