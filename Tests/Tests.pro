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
    projectfilecontrollertests.cpp \
    randomdatagenerator.cpp \
    filestatetrackertests.cpp \
    eventlistener.cpp

INCLUDEPATH += $$PWD/../

LIBS += $$PWD/../../build-RequirementsManager-Desktop-Release/uniqueidmanager.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/requirement.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/requirementfactory.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/requirementsmodel.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/moc_requirementsmodel.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/projectfilecontroller.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/moc_projectfilecontroller.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/projectfilereader.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/projectfilewriter.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/appsettings.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/filestatetracker.o \
        $$PWD/../../build-RequirementsManager-Desktop-Release/moc_filestatetracker.o


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
    projectfilewritermock.h \
    filestatetrackermock.h \
    appsettingsmock.h \
    randomdatagenerator.h \
    requirementsmodelmock.h \
    eventlistener.h
