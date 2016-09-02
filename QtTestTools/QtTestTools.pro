#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T11:31:25
#
#-------------------------------------------------

QT       += gui widgets network

TARGET = QtTestTools
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    qtextstreamadapter.cpp \
    qfileadapter.cpp \
    qdiradapter.cpp \
    qfiledialogadapter.cpp \
    qsettingsadapter.cpp \
    qtimeradapter.cpp \
    qlocalsocketadapter.cpp \
    qapplicationadapter.cpp \
    qmessageboxprovider.cpp \
    qcoreapplicationadapter.cpp \
    qxmlstreamwriteradapter.cpp \
    qplaintexteditadapter.cpp \
    qlineeditadapter.cpp \
    instreamprogrammer.cpp \
    qtextstreamfake.cpp

HEADERS += \
    qtextstreamadapter.h \
    qfileadapter.h \
    QTextStreamAdapterMock.h \
    QFileAdapterMock.h \
    qdiradapter.h \
    QDirAdapterMock.h \
    qfiledialogadapter.h \
    qfiledialogadaptermock.h \
    qsettingsadapter.h \
    QSettingsAdapterMock.h \
    qtimeradapter.h \
    QTimerAdapterMock.h \
    qlocalsocketadapter.h \
    QLocalSocketAdapterMock.h \
    qapplicationadapter.h \
    QApplicationAdapterMock.h \
    qmessageboxprovider.h \
    QMessageBoxProviderMock.h \
    qcoreapplicationadapter.h \
    QCoreApplicationAdapterMock.h \
    qxmlstreamwriteradapter.h \
    QXmlStreamWriterMock.h \
    qplaintexteditadapter.h \
    qlineeditadapter.h \
    instreamprogrammer.h \
    qtextstreamfake.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32: LIBS += -L$$PWD/../gtest/ -lgmock

INCLUDEPATH += $$PWD/../gtest/include
DEPENDPATH += $$PWD/../gtest/include
INCLUDEPATH += $$PWD/../gtest/include
DEPENDPATH += $$PWD/../gtest/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../gtest/gmock.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../gtest/libgmock.a
