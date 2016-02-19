#include "gtest/gtest.h"
#include "filestatetracker.h"
#include "eventlistener.h"

class FileStateTrackerTests : public ::testing::Test{
protected:
    FileStateTracker *tracker;
    EventListener *listener;
    QString oldPath;
    QString newPath;

    FileStateTrackerTests(){
        oldPath = "C:/startPath/file.req";
        newPath = "C:/newPath/newFile.req";

        tracker = new FileStateTracker();
        listener = new EventListener();

        tracker->setFilePath(oldPath);
        tracker->setChanged(true);

        QObject::connect(tracker, SIGNAL(filePathChanged(QString)),
                         listener, SLOT(setFilePathChanged(QString)));
        QObject::connect(tracker, SIGNAL(changedStateChanged(bool)),
                         listener, SLOT(setChangedStateChanged(bool)));
    }

    virtual ~FileStateTrackerTests(){
        delete tracker;
        delete listener;
    }
};

/*! TEST_SPEC: FileStateTracker::setFilePath()
 PREPARATION

 ACTION

 RESULT


 */
TEST_F(FileStateTrackerTests, when_file_path_changed_signal_is_emitted){
    tracker->setFilePath(newPath);
    EXPECT_TRUE(listener->filePathChanged_called);
}

/*! TEST_SPEC: FileStateTracker::setFilePath()
 PREPARATION

 ACTION

 RESULT


 */
TEST_F(FileStateTrackerTests, when_file_path_did_not_change_no_signal_is_emitted){
    tracker->setFilePath(oldPath);
    EXPECT_FALSE(listener->filePathChanged_called);
}

/*! TEST_SPEC: FileStateTracker::setChanged()
 PREPARATION

 ACTION

 RESULT


 */
TEST_F(FileStateTrackerTests, when_changedState_changed_signal_is_emitted){
    tracker->setChanged(false);
    EXPECT_TRUE(listener->changeStateChanged_called);
}

/*! TEST_SPEC: FileStateTracker::setChanged()
 PREPARATION

 ACTION

 RESULT


 */
TEST_F(FileStateTrackerTests, when_changedState_did_not_change_no_signal_is_emitted){
    tracker->setChanged(true);
    EXPECT_FALSE(listener->changeStateChanged_called);
}
