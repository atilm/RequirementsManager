#-------------------------------------------------
#
# Project created by QtCreator 2015-09-13T14:37:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RequirementsManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    richtextcontroller.cpp \
    requirementsview.cpp \
    descriptionview.cpp \
    requirementsmodel.cpp \
    requirement.cpp \
    uniqueidmanager.cpp \
    requirementattribute.cpp \
    requirementlink.cpp \
    requirementfactory.cpp \
    projectfilecontroller.cpp \
    projectfilereader.cpp \
    projectfilewriter.cpp \
    filestatetracker.cpp \
    appsettings.cpp \
    attributecontext.cpp \
    attributeeditor.cpp

HEADERS  += mainwindow.h \
    richtextcontroller.h \
    requirementsview.h \
    descriptionview.h \
    requirementsmodel.h \
    requirement.h \
    uniqueidmanager.h \
    requirementattribute.h \
    requirementlink.h \
    requirementfactory.h \
    projectfilecontroller.h \
    projectfilereader.h \
    projectfilewriter.h \
    filestatetracker.h \
    appsettings.h \
    attributecontext.h \
    attributeeditor.h

FORMS    += mainwindow.ui \
    attributeeditor.ui

RESOURCES += \
    resources.qrc

unix:!macx: LIBS += -L$$PWD/../../QtTestTools/ -lQtTestTools

INCLUDEPATH += $$PWD/../../QtTestTools
DEPENDPATH += $$PWD/../../QtTestTools

unix:!macx: PRE_TARGETDEPS += $$PWD/../../QtTestTools/libQtTestTools.a
