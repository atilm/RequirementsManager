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
    eventlistener.cpp \
    appsettingstests.cpp \
    mockattributecontainerfactory.cpp

INCLUDEPATH += $$PWD/../

LIBS += $$PWD/../release/uniqueidmanager.o \
        $$PWD/../release/moc_uniqueidmanager.o \
        $$PWD/../release/requirement.o \
        $$PWD/../release/requirementfactory.o \
        $$PWD/../release/requirementsmodel.o \
        $$PWD/../release/moc_requirementsmodel.o \
        $$PWD/../release/projectfilecontroller.o \
        $$PWD/../release/moc_projectfilecontroller.o \
        $$PWD/../release/projectfilereader.o \
        $$PWD/../release/projectfilewriter.o \
        $$PWD/../release/appsettings.o \
        $$PWD/../release/filestatetracker.o \
        $$PWD/../release/moc_filestatetracker.o \
        $$PWD/../release/attributecontainer.o \
        $$PWD/../release/moc_attributecontainer.o \
        $$PWD/../release/requirementtomodelmapper.o \
        $$PWD/../release/attributecontainerfactory.o \
        $$PWD/../release/riskassessmentmodel.o \
        $$PWD/../release/moc_riskassessmentmodel.o \
        $$PWD/../release/linkcontainer.o \
        $$PWD/../release/moc_linkcontainer.o \
        $$PWD/../release/riskassessmentfactory.o \
        $$PWD/../release/linkcontainerfactory.o \
        $$PWD/../release/preventiveaction.o \
        $$PWD/../release/preventiveactionmodel.o \
        $$PWD/../release/moc_preventiveactionmodel.o \
        $$PWD/../release/linkgroup.o \
        $$PWD/../release/linknode.o \
        $$PWD/../release/linktorequirement.o \
        $$PWD/../release/riskmodel.o \
        $$PWD/../release/moc_riskmodel.o \
        $$PWD/../release/riskassessment.o \

unix:!macx: LIBS += -L$$PWD/../../../GMock/qt/ -lGMock

unix:!macx: INCLUDEPATH += $$PWD/../../../GMock/include
unix:!macx: DEPENDPATH += $$PWD/../../../GMock/include
unix:!macx: INCLUDEPATH += $$PWD/../../../GMock/gtest/include
unix:!macx: DEPENDPATH += $$PWD/../../../GMock/gtest/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../GMock/qt/libGMock.a


win32: LIBS += -L$$PWD/../../GTest/QtMingw/release/ -lgmock

INCLUDEPATH += $$PWD/../../GTest/googletest/include
DEPENDPATH += $$PWD/../../GTest/googletest/include
INCLUDEPATH += $$PWD/../../GTest/googlemock/include
DEPENDPATH += $$PWD/../../GTest/googlemock/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../GTest/QtMingw/release/gmock.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../GTest/QtMingw/release/libgmock.a


win32: LIBS += -L$$PWD/../../QtTestTools/release/ -lQtTestTools

INCLUDEPATH += $$PWD/../../QtTestTools
DEPENDPATH += $$PWD/../../QtTestTools

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../QtTestTools/release/QtTestTools.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../QtTestTools/release/libQtTestTools.a


HEADERS += \
    projectfilereadermock.h \
    projectfilewritermock.h \
    filestatetrackermock.h \
    appsettingsmock.h \
    randomdatagenerator.h \
    requirementsmodelmock.h \
    eventlistener.h \
    attributecontainermock.h \
    mockattributecontainerfactory.h \
    riskassessmentmodelmock.h \
    linkcontainermock.h
