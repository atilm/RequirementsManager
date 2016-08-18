#include "gtest/gtest.h"
#include "directorylistmodelmock.h"
#include "projectfilecontroller.h"
#include "qfiledialogadaptermock.h"
#include "QFileAdapterMock.h"
#include "projectfilereadermock.h"
#include "projectfilewritermock.h"
#include "filestatetrackermock.h"
#include "appsettingsmock.h"
#include "randomdatagenerator.h"
#include "requirementsmodelmock.h"
#include "QMessageBoxProviderMock.h"

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
    shared_ptr<FileStateTrackerMock> stateMock;
    AppSettingsMock *settingsMock;
    shared_ptr<RequirementsModelMock> modelMock;
    QMessageBoxProviderMock *msgMock;
    DirectoryListModelMock *sourceDirsMock;
    DirectoryListModelMock *testDirsMock;

    QString currentDir;
    QString defaultfilePath;

    ProjectFileControllerTests(){
        dialogMock = new QFileDialogAdapterMock();
        fileMock = new QFileAdapterMock();
        readerMock = new ProjectFileReaderMock();
        writerMock = new ProjectFileWriterMock();
        stateMock = make_shared<FileStateTrackerMock>();
        settingsMock = new AppSettingsMock();
        modelMock = make_shared<RequirementsModelMock>();
        msgMock = new QMessageBoxProviderMock();
        sourceDirsMock = new DirectoryListModelMock();
        testDirsMock = new DirectoryListModelMock();

        controller = new ProjectFileController(dialogMock, fileMock,
                                               readerMock, writerMock,
                                               stateMock, settingsMock, msgMock);

        controller->injectDirectoryModels(sourceDirsMock, testDirsMock);

        init();

        setDefaultExpectations();
    }

    virtual ~ProjectFileControllerTests(){
        delete controller;
        delete settingsMock;
        delete sourceDirsMock;
        delete testDirsMock;
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
        EXPECT_CALL(*(stateMock.get()), setFilePath(_))
                .Times(AtLeast(0));
        EXPECT_CALL(*(stateMock.get()), filePath())
                .WillRepeatedly(Return(defaultfilePath));
        EXPECT_CALL(*(stateMock.get()), setChanged(_))
                .Times(AtLeast(0));
        EXPECT_CALL(*(stateMock.get()), unsavedChanges())
                .WillRepeatedly(Return(false));
        EXPECT_CALL(*readerMock, load(_, _))
                .Times(AtLeast(0));
        EXPECT_CALL(*fileMock, setFileName(_))
                .Times(AtLeast(0));
        EXPECT_CALL(*(modelMock.get()), clearModel())
                .Times(AtLeast(0));
        EXPECT_CALL(*settingsMock, setDirectory(_))
                .Times(AtLeast(0));
        EXPECT_CALL(*sourceDirsMock, clear())
                .Times(AtLeast(0));
        EXPECT_CALL(*testDirsMock, clear())
                .Times(AtLeast(0));
    }
};

/*! TEST_SPEC ProjectFileController::saveAs()
SHORT

PREPARATION


ACTION


RESULT

*/
TEST_F(ProjectFileControllerTests, when_saveAs_is_called_for_new_file_a_file_dialog_is_shown){
    EXPECT_CALL(*(stateMock.get()), filePath())
            .WillRepeatedly(Return(QString()));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(defaultfilePath));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_saveAs_is_called_for_known_file_the_file_dialog_is_shown){
    EXPECT_CALL(*(stateMock.get()), filePath())
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

TEST_F(ProjectFileControllerTests, when_saveAs_is_called_the_path_is_registered){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(fPath));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_saveAs_is_called_the_file_state_is_set_to_unchanged){
    EXPECT_CALL(*(stateMock.get()), setChanged(false));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_file_is_savedAs_the_start_directory_is_set){
    QString dirPath = "C:/directory";
    QString fileName = "file.req";
    QString filePath = dirPath + "/" + fileName;

    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(filePath));

    EXPECT_CALL(*settingsMock, setDirectory(dirPath));

    controller->saveAs();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_new_file_a_file_dialog_is_shown){
    EXPECT_CALL(*(stateMock.get()), filePath())
            .WillOnce(Return(QString()));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(defaultfilePath));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_known_file_no_file_dialog_is_shown){
    EXPECT_CALL(*(stateMock.get()), filePath())
            .WillOnce(Return(defaultfilePath));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, _, _, _, _))
            .Times(0);

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_the_files_path_is_set){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*(stateMock.get()), filePath())
            .WillOnce(Return(fPath));

    EXPECT_CALL(*fileMock, setFileName(fPath));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_known_file_no_path_is_registered){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*(stateMock.get()), filePath())
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(_))
            .Times(0);

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_new_file_the_path_is_registered){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*(stateMock.get()), filePath())
            .WillOnce(Return(QString()));
    EXPECT_CALL(*dialogMock, getSaveFileName(_, QString("Save file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(fPath));

    controller->save();
}

TEST_F(ProjectFileControllerTests, when_save_is_called_for_known_file_the_file_state_is_set_to_unchanged){
    EXPECT_CALL(*(stateMock.get()), setChanged(false));

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

TEST_F(ProjectFileControllerTests, when_load_is_called_the_selected_path_is_registered){
    QString fPath = rand.getQString(20,1);
    EXPECT_CALL(*dialogMock, getOpenFileName(_, QString("Open file"), currentDir, _, _))
            .WillOnce(Return(fPath));

    EXPECT_CALL(*stateMock, setFilePath(fPath));

    controller->load();
}

TEST_F(ProjectFileControllerTests, when_load_is_called_the_file_state_is_set_to_unchanged){
    EXPECT_CALL(*(stateMock.get()), setChanged(false));

    controller->load();
}

TEST_F(ProjectFileControllerTests, when_file_is_loaded_the_start_directory_is_set){
    QString dirPath = "C:/directory";
    QString fileName = "file.req";
    QString filePath = dirPath + "/" + fileName;

    EXPECT_CALL(*dialogMock, getOpenFileName(_, QString("Open file"), currentDir, _, _))
            .WillOnce(Return(filePath));

    EXPECT_CALL(*settingsMock, setDirectory(dirPath));

    controller->load();
}
