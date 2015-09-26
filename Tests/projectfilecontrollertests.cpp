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

    QString currentDir;
    QString defaultfilePath;

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
        currentDir = "C:/directory/";
        defaultfilePath = currentDir + "name.req";
    }

    void setDefaultExpectations(){
        EXPECT_CALL(*dialogMock, getSaveFileName(_, _, _, _, _))
                .WillRepeatedly(Return(defaultfilePath));
        EXPECT_CALL(*dialogMock, getOpenFileName(_, _, _, _, _))
                .WillRepeatedly(Return(defaultfilePath));
        EXPECT_CALL(*writerMock, save(_, _))
                .Times(AtLeast(0));
        EXPECT_CALL(*settingsMock, directory())
                .WillRepeatedly(Return(currentDir));
        EXPECT_CALL(*stateMock, setFilePath(_))
                .Times(AtLeast(0));
        EXPECT_CALL(*stateMock, filePath())
                .WillRepeatedly(Return(defaultfilePath));
        EXPECT_CALL(*stateMock, setChanged(_))
                .Times(AtLeast(0));
        EXPECT_CALL(*readerMock, load(_, _))
                .Times(AtLeast(0));
        EXPECT_CALL(*fileMock, setFileName(_))
                .Times(AtLeast(0));
    }
};


TEST_F(ProjectFileControllerTests, when_saveAs_is_called_for_new_file_a_file_dialog_is_shown){
    EXPECT_CALL(*stateMock, filePath())
            .WillRepeatedly(Return(QString()));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(defaultfilePath));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_saveAs_is_called_for_known_file_the_file_dialog_is_shown){
    EXPECT_CALL(*stateMock, filePath())
            .WillRepeatedly(Return(defaultfilePath));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(defaultfilePath));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_saveAs_is_called_the_files_path_is_set){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*fileMock, setFileName(fPath));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_saveAs_is_called_the_set_model_is_saved){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*writerMock, save(modelMock, fileMock));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_saveAs_is_called_the_path_is_registered){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(fPath));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_saveAs_is_called_the_file_state_is_set_to_unchanged){
    EXPECT_CALL(*stateMock, setChanged(false));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_new_file_a_file_dialog_is_shown){
    EXPECT_CALL(*stateMock, filePath())
            .WillOnce(Return(QString()));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(defaultfilePath));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_known_file_no_file_dialog_is_shown){
    EXPECT_CALL(*stateMock, filePath())
            .WillOnce(Return(defaultfilePath));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, _, _, _, _))
            .Times(0);

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_the_files_path_is_set){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*stateMock, filePath())
            .WillOnce(Return(fPath));

    EXPECT_CALL(*fileMock, setFileName(fPath));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_the_set_model_is_saved){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*stateMock, filePath())
            .WillOnce(Return(fPath));

    EXPECT_CALL(*writerMock, save(modelMock, fileMock));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_known_file_no_path_is_registered){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*stateMock, filePath())
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(_))
            .Times(0);

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_new_file_the_path_is_registered){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*stateMock, filePath())
            .WillOnce(Return(QString()));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(fPath));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_known_file_the_file_state_is_set_to_unchanged){
    EXPECT_CALL(*stateMock, setChanged(false));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_load_is_called_a_file_dialog_is_shown){
    EXPECT_CALL(*dialogMock, getOpenFileName(_, QString("Open file"), currentDir, _, _))
            .WillOnce(Return(defaultfilePath));

    controller->load();
}

TEST_F(ProjectFileControllerTests, when_load_is_called_the_files_path_is_set){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*dialogMock, getOpenFileName(_, QString("Open file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*fileMock, setFileName(fPath));

    controller->load();
}

TEST_F(ProjectFileControllerTests, when_load_is_called_the_selected_file_is_loaded_to_the_model){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*dialogMock, getOpenFileName(_, QString("Open file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*readerMock, load(modelMock, fileMock));

    controller->load();
}

TEST_F(ProjectFileControllerTests, when_load_is_called_the_selected_path_is_registered){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*dialogMock, getOpenFileName(_, QString("Open file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(fPath));

    controller->load();
}

TEST_F(ProjectFileControllerTests, when_load_is_called_the_file_state_is_set_to_unchanged){
    EXPECT_CALL(*stateMock, setChanged(false));

    controller->load();
}
