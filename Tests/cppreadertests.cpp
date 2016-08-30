#include "gtest/gtest.h"
#include "cppreader.h"
#include "directorylistermock.h"
#include "instreamprogrammer.h"
#include "QFileAdapterMock.h"
#include "QTextStreamAdapterMock.h"

#include <QDebug>

#include <memory>
using namespace std;
using ::testing::Return;
using ::testing::_;
using ::testing::Sequence;

class CppReaderTests : public ::testing::Test{
protected:
    QFileAdapterMock *file;
    QTextStreamAdapterMock *inStream;
    shared_ptr<DirectoryListerMock> dirLister;
    CppReader *reader;
    shared_ptr<FileStateTracker> state;
    DirectoryListModel *sourceDirs;
    DirectoryListModel *testDirs;
    QStringList files;
    QStringList headerFiles;

    CppReaderTests(){
        file = new QFileAdapterMock();
        inStream = new QTextStreamAdapterMock();
        dirLister = make_shared<DirectoryListerMock>();
        reader = new CppReader(file, inStream, dirLister);

        state = make_shared<FileStateTracker>();
        state->setFilePath(".");

        sourceDirs = new DirectoryListModel(state);
        testDirs = new DirectoryListModel(state);

        headerFiles << "C:/sourceDire/headerFile.h";

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
        EXPECT_CALL(*(dirLister.get()), listFiles(_,_))
                .WillRepeatedly(Return(files));
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

    EXPECT_CALL(*(dirLister.get()), listFiles(_,_))
            .WillOnce(Return(headerFiles))
            .WillRepeatedly(Return(files));

    fileContent << "class ExampleClass {"
                << "public:"
                << "    void publicFunction();"
                << ""
                << "private slots:"
                << "    void privateSlot();"
                << "};";

    Sequence s;
    InStreamProgrammer::prepareSream(inStream, fileContent, s, fileContent.count());

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
    QStringList fileContent;

    EXPECT_CALL(*(dirLister.get()), listFiles(_,_))
            .WillOnce(Return(headerFiles))
            .WillRepeatedly(Return(files));

    fileContent << "class ExampleClass {"
                << "private:"
                << "    void privateFunction();"
                << ""
                << "public slots:"
                << "    void publicSlot();"
                << "};";

    Sequence s;
    InStreamProgrammer::prepareSream(inStream, fileContent, s, fileContent.count());

    SourceCodeModel *model = reader->parseSourceCode(sourceDirs, testDirs);

    QModelIndex classIdx = model->index(0, 0, QModelIndex());
    QModelIndex funcIdx = model->index(1, 0, classIdx);

    EXPECT_EQ(1, model->rowCount(classIdx));
    EXPECT_EQ(QString("publicSlot"), model->data(funcIdx));
}
