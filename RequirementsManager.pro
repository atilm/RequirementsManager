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
    requirement.cpp

HEADERS  += mainwindow.h \
    richtextcontroller.h \
    requirementsview.h \
    descriptionview.h \
    requirementsmodel.h \
    requirement.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

unix:!macx: LIBS += -L$$PWD/../../QtTestTools/ -lQtTestTools

INCLUDEPATH += $$PWD/../../QtTestTools
DEPENDPATH += $$PWD/../../QtTestTools

unix:!macx: PRE_TARGETDEPS += $$PWD/../../QtTestTools/libQtTestTools.a
