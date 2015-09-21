QT       += core
QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    RequirementTests.cpp \
    uniqueidmanagertests.cpp \
    projectfilecontrollertests.cpp

INCLUDEPATH += $$PWD/../

LIBS += $$PWD/../../build-RequirementsManager-Desktop-Release/uniqueidmanager.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/requirement.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/projectfilecontroller.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/moc_projectfilecontroller.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/projectfilereader.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/projectfilewriter.o


unix:!macx: LIBS += -L$$PWD/../../../GMock/qt/ -lGMock

INCLUDEPATH += $$PWD/../../../GMock/include
DEPENDPATH += $$PWD/../../../GMock/include
INCLUDEPATH += $$PWD/../../../GMock/gtest/include
DEPENDPATH += $$PWD/../../../GMock/gtest/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../GMock/qt/libGMock.a




unix:!macx: LIBS += -L$$PWD/../../../QtTestTools/ -lQtTestTools

INCLUDEPATH += $$PWD/../../../QtTestTools
DEPENDPATH += $$PWD/../../../QtTestTools

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../QtTestTools/libQtTestTools.a

HEADERS += \
    projectfilereadermock.h \
    projectfilewritermock.h
