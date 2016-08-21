#include "gtest/gtest.h"
#include "cppreader.h"
#include "instreamprogrammer.h"
#include "QFileAdapterMock.h"
#include "QTextStreamAdapterMock.h"

#include <QDebug>

#include <memory>
using namespace std;
using ::testing::Return;
using ::testing::_;

class CppReaderTests : public ::testing::Test{
protected:
    QFileAdapterMock *file;
    QTextStreamAdapterMock *inStream;
    CppReader *reader;
    shared_ptr<FileStateTracker> state;
    DirectoryListModel *sourceDirs;
    DirectoryListModel *testDirs;

    CppReaderTests(){
        file = new QFileAdapterMock();
        inStream = new QTextStreamAdapterMock();
        reader = new CppReader(file, inStream);

        state = make_shared<FileStateTracker>();
        state->setFilePath(".");

        sourceDirs = new DirectoryListModel(state);
        testDirs = new DirectoryListModel(state);

        defaultExpectations();
    }

    virtual ~CppReaderTests(){
        delete reader;
        delete sourceDirs;
        delete testDirs;
    }

    void defaultExpectations(){
        EXPECT_CALL(*file, open(_))
                .WillOnce(Return(true));
    }
};

class CppReader_scope : public CppReaderTests{
protected:

    CppReader_scope(){
        sourceDirs->add("C:/sourceDir");
    }
};

/*! TEST_SPEC CppReader::parseSourceCode()
SHORT
When the parser encounters the string "private slots:", it changes into private
parsing mode.
*/
TEST_F(CppReader_scope, when_private_slots_is_read_the_parsing_mode_becomes_private){

    QStringList fileContent;

    fileContent << "class ExampleClass {"
                << "public:"
                << "    void publicFunction();"
                << ""
                << "private slots:"
                << "    void privateSlot();"
                << "};";

    InStreamProgrammer::prepareSream(inStream, fileContent, fileContent.count());

    SourceCodeModel *model = reader->parseSourceCode(sourceDirs, testDirs);

    QModelIndex classIdx = model->index(0, 0, QModelIndex());
    QModelIndex funcIdx = model->index(1, 0, classIdx);

    EXPECT_EQ(1, model->rowCount(classIdx));
    EXPECT_EQ(QString("publicFunction"), model->data(funcIdx));
}

/*! TEST_SPEC CppReader::parseSourceCode()
SHORT
When the parser encounters the string "public slots:", it changes into public
parsing mode.
*/
TEST_F(CppReader_scope, when_public_slots_is_read_the_parsing_mode_becomes_public){
    EXPECT_TRUE(false);
}
