#-------------------------------------------------
#
# Project created by QtCreator 2015-09-13T14:37:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION_MAJOR = 0
VERSION_MINOR = 2
VERSION_BUILD = 3

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

RC_ICONS += appIcon.ico

TARGET = RequirementsManager
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    richtextcontroller.cpp \
    requirementsview.cpp \
    descriptionview.cpp \
    requirementsmodel.cpp \
    requirement.cpp \
    uniqueidmanager.cpp \
    requirementfactory.cpp \
    projectfilecontroller.cpp \
    projectfilereader.cpp \
    projectfilewriter.cpp \
    filestatetracker.cpp \
    appsettings.cpp \
    attributecontext.cpp \
    attributeeditor.cpp \
    attributecontainer.cpp \
    attributecontainerfactory.cpp \
    requirementtomodelmapper.cpp \
    risktableview.cpp \
    preventiveactiontableview.cpp \
    riskdescriptionview.cpp \
    riskassessmenttable.cpp \
    riskassessmentdialog.cpp \
    riskassessmentmodel.cpp \
    preventiveactionmodel.cpp \
    riskassessment.cpp \
    riskmodel.cpp \
    riskassessmentfactory.cpp \
    preventiveaction.cpp \
    riskassessmenteditcontroller.cpp \
    preventiveactiondialog.cpp \
    htmlgenerator.cpp \
    htmltemplate.cpp \
    htmltemplatefactory.cpp \
    linktypeeditor.cpp \
    linkcontext.cpp \
    linkcontainer.cpp \
    linkcontainerfactory.cpp \
    linktorequirement.cpp \
    linkgroup.cpp \
    linkcontroller.cpp \
    linknode.cpp \
    isourcecodereader.cpp \
    sourcecodecontroller.cpp \
    sourcecodemodel.cpp \
    sourcenode.cpp \
    settingsdialog.cpp \
    sourcecodereaderprovider.cpp \
    directorylistmodel.cpp \
    cppreader.cpp \
    classnode.cpp \
    functionnode.cpp \
    testnode.cpp \
    designreference.cpp \
    automatedtestreference.cpp \
    preventiveactionfactory.cpp \
    textdocumentserializer.cpp \
    richtextresourcemanager.cpp \
    resizeimagedialog.cpp \
    reportgenerator.cpp \
    reportcontroller.cpp \
    htmlreportgenerator.cpp \
    reportgeneratorfactory.cpp \
    riskscenariotextedit.cpp \
    testnamelineedit.cpp \
    aboutbox.cpp \
    version.cpp \
    directorylister.cpp \
    appsettingsdialog.cpp \
    requirementreference.cpp \
    requirementrefcounter.cpp \
    requirementrefview.cpp \
    aerobasicreader.cpp \
    tagextractor.cpp \
    freeformreportgenerator.cpp \
    reporttypechooserdialog.cpp

HEADERS  += mainwindow.h \
    richtextcontroller.h \
    requirementsview.h \
    descriptionview.h \
    requirementsmodel.h \
    requirement.h \
    uniqueidmanager.h \
    requirementfactory.h \
    projectfilecontroller.h \
    projectfilereader.h \
    projectfilewriter.h \
    filestatetracker.h \
    appsettings.h \
    attributecontext.h \
    attributeeditor.h \
    attributecontainer.h \
    attributecontainerfactory.h \
    requirementtomodelmapper.h \
    risktableview.h \
    preventiveactiontableview.h \
    riskdescriptionview.h \
    riskassessmenttable.h \
    riskassessmentdialog.h \
    riskassessmentmodel.h \
    preventiveactionmodel.h \
    riskassessment.h \
    riskmodel.h \
    riskassessmentfactory.h \
    preventiveaction.h \
    riskassessmenteditcontroller.h \
    preventiveactiondialog.h \
    htmlgenerator.h \
    htmltemplate.h \
    htmltemplatefactory.h \
    linktypeeditor.h \
    linkcontext.h \
    linkcontainer.h \
    linkcontainerfactory.h \
    linktorequirement.h \
    linkgroup.h \
    linkcontroller.h \
    linknode.h \
    isourcecodereader.h \
    sourcecodecontroller.h \
    sourcecodemodel.h \
    sourcenode.h \
    settingsdialog.h \
    sourcecodereaderprovider.h \
    directorylistmodel.h \
    cppreader.h \
    classnode.h \
    functionnode.h \
    testnode.h \
    designreference.h \
    automatedtestreference.h \
    preventiveactionfactory.h \
    textdocumentserializer.h \
    richtextresourcemanager.h \
    resizeimagedialog.h \
    reportgenerator.h \
    reportcontroller.h \
    htmlreportgenerator.h \
    reportgeneratorfactory.h \
    riskscenariotextedit.h \
    testnamelineedit.h \
    aboutbox.h \
    version.h \
    directorylister.h \
    appsettingsdialog.h \
    requirementreference.h \
    requirementrefcounter.h \
    requirementrefview.h \
    aerobasicreader.h \
    tagextractor.h \
    freeformreportgenerator.h \
    reporttypechooserdialog.h

FORMS    += mainwindow.ui \
    attributeeditor.ui \
    riskassessmenttable.ui \
    riskassessmentdialog.ui \
    preventiveactiondialog.ui \
    linkeditor.ui \
    settingsdialog.ui \
    resizeimagedialog.ui \
    aboutbox.ui \
    appsettingsdialog.ui \
    reporttypechooserdialog.ui

RESOURCES += \
    resources.qrc



win32: LIBS += -L$$PWD/../QtTestTools/release/ -lQtTestTools

INCLUDEPATH += $$PWD/../QtTestTools
DEPENDPATH += $$PWD/../QtTestTools

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../QtTestTools/release/QtTestTools.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../QtTestTools/release/libQtTestTools.a
