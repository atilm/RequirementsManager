#include "gtest/gtest.h"
#include "projectfilecontroller.h"
#include "qfiledialogadaptermock.h"
#include "QFileAdapterMock.h"
#include "projectfilereadermock.h"
#include "projectfilewritermock.h"


class ProjectFileControllerTests : public ::testing::Test{
protected:
    ProjectFileController *controller;
    QFileDialogAdapterMock *dialogMock;
    QFileAdapterMock *fileMock;
    ProjectFileReaderMock *readerMock;
    ProjectFileWriterMock *writerMock;

    ProjectFileControllerTests(){
        dialogMock = new QFileDialogAdapterMock();
        fileMock = new QFileAdapterMock();
        readerMock = new ProjectFileReaderMock();
        writerMock = new ProjectFileWriterMock();

        controller = new ProjectFileController(dialogMock, fileMock,
                                               readerMock, writerMock);
    }

    virtual ~ProjectFileControllerTests(){
        delete controller;
    }
};
