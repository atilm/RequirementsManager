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
    mockattributecontainerfactory.cpp \
    cppreadertests.cpp

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
    linkcontainermock.h \
    directorylistmodelmock.h

INCLUDEPATH += $$PWD/../Application/

LIBS += $$PWD/../Application/release/uniqueidmanager.o \
        $$PWD/../Application/release/moc_uniqueidmanager.o \
        $$PWD/../Application/release/requirement.o \
        $$PWD/../Application/release/requirementfactory.o \
        $$PWD/../Application/release/requirementsmodel.o \
        $$PWD/../Application/release/moc_requirementsmodel.o \
        $$PWD/../Application/release/projectfilecontroller.o \
        $$PWD/../Application/release/moc_projectfilecontroller.o \
        $$PWD/../Application/release/projectfilereader.o \
        $$PWD/../Application/release/projectfilewriter.o \
        $$PWD/../Application/release/appsettings.o \
        $$PWD/../Application/release/filestatetracker.o \
        $$PWD/../Application/release/moc_filestatetracker.o \
        $$PWD/../Application/release/attributecontainer.o \
        $$PWD/../Application/release/moc_attributecontainer.o \
        $$PWD/../Application/release/requirementtomodelmapper.o \
        $$PWD/../Application/release/attributecontainerfactory.o \
        $$PWD/../Application/release/riskassessmentmodel.o \
        $$PWD/../Application/release/moc_riskassessmentmodel.o \
        $$PWD/../Application/release/linkcontainer.o \
        $$PWD/../Application/release/moc_linkcontainer.o \
        $$PWD/../Application/release/riskassessmentfactory.o \
        $$PWD/../Application/release/linkcontainerfactory.o \
        $$PWD/../Application/release/preventiveaction.o \
        $$PWD/../Application/release/preventiveactionmodel.o \
        $$PWD/../Application/release/moc_preventiveactionmodel.o \
        $$PWD/../Application/release/linkgroup.o \
        $$PWD/../Application/release/linknode.o \
        $$PWD/../Application/release/linktorequirement.o \
        $$PWD/../Application/release/riskmodel.o \
        $$PWD/../Application/release/moc_riskmodel.o \
        $$PWD/../Application/release/riskassessment.o \
        $$PWD/../Application/release/designreference.o \
        $$PWD/../Application/release/directorylistmodel.o \
        $$PWD/../Application/release/moc_directorylistmodel.o \
        $$PWD/../Application/release/cppreader.o \
        $$PWD/../Application/release/sourcenode.o \
        $$PWD/../Application/release/functionnode.o \
        $$PWD/../Application/release/testnode.o \
        $$PWD/../Application/release/classnode.o \
        $$PWD/../Application/release/sourcecodemodel.o \
        $$PWD/../Application/release/moc_sourcecodemodel.o \

win32: LIBS += -L$$PWD/../gtest/ -lgmock

INCLUDEPATH += $$PWD/../gtest/include
DEPENDPATH += $$PWD/../gtest/include
INCLUDEPATH += $$PWD/../gtest/include
DEPENDPATH += $$PWD/../gtest/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../gtest/gmock.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../gtest/libgmock.a


win32: LIBS += -L$$PWD/../QtTestTools/release/ -lQtTestTools

INCLUDEPATH += $$PWD/../QtTestTools
DEPENDPATH += $$PWD/../QtTestTools

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../QtTestTools/release/QtTestTools.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../QtTestTools/release/libQtTestTools.a
