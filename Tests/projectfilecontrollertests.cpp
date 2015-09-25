#include "gtest/gtest.h"
#include "projectfilecontroller.h"
#include "qfiledialogadaptermock.h"
#include "QFileAdapterMock.h"
#include "projectfilereadermock.h"
#include "projectfilewritermock.h"
#include "filestatetrackermock.h"
#include "appsettingsmock.h"
#include "randomdatagenerator.h"
#include "requirementsmodelmock.h"
using ::testing::AtLeast;
using ::testing::_;
using ::testing::Return;

class ProjectFileControllerTests : public ::testing::Test{
protected:
    RandomDataGenerator rand;
    ProjectFileController *controller;
    QFileDialogAdapterMock *dialogMock;
    QFileAdapterMock *fileMock;
    ProjectFileReaderMock *readerMock;
    ProjectFileWriterMock *writerMock;
    FileStateTrackerMock *stateMock;
    AppSettingsMock *settingsMock;
    RequirementsModelMock *modelMock;

    QString filePath;

    ProjectFileControllerTests(){
        dialogMock = new QFileDialogAdapterMock();
        fileMock = new QFileAdapterMock();
        readerMock = new ProjectFileReaderMock();
        writerMock = new ProjectFileWriterMock();
        stateMock = new FileStateTrackerMock();
        settingsMock = new AppSettingsMock();
        modelMock = new RequirementsModelMock();

        controller = new ProjectFileController(dialogMock, fileMock,
                                               readerMock, writerMock,
                                               stateMock, settingsMock);

        init();

        setDefaultExpectations();
    }

    virtual ~ProjectFileControllerTests(){
        delete controller;
        delete stateMock;
        delete settingsMock;
        delete modelMock;
    }

    void init(){
        controller->setModel(modelMock);
        filePath = "./name.req";
    }

    void setDefaultExpectations(){
        EXPECT_CALL(*dialogMock, getOpenFileName(_, _, _, _, _))
                .WillRepeatedly(Return(filePath));
        EXPECT_CALL(*writerMock, save(_, _))
                .Times(AtLeast(0));
        EXPECT_CALL(*settingsMock, directory())
                .WillRepeatedly(Return(filePath));
        EXPECT_CALL(*stateMock, setFilePath(_));
    }
};

TEST_F(ProjectFileControllerTests, when_save_is_called_for_new_file_a_file_dialog_is_shown){
    EXPECT_CALL(*dialogMock, getOpenFileName(_, QString("Open file"), _, _, _))
            .WillOnce(Return(filePath));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_known_file_no_file_dialog_is_shown){
    EXPECT_CALL(*dialogMock, getOpenFileName(_, QString("Open file"), _, _, _))
            .WillOnce(Return(filePath));

    controller->save();
    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_the_set_model_is_saved){
    QString fPath = rand.getQString();
    EXPECT_CALL(*settingsMock, directory())
            .WillOnce(Return(fPath));

    EXPECT_CALL(*writerMock, save(modelMock, fPath));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_the_path_is_registered){
    QString fPath = rand.getQString();
    EXPECT_CALL(*settingsMock, directory())
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(fPath));

    controller->save();
}
