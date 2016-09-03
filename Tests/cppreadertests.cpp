#include "gtest/gtest.h"
#include "cppreader.h"
#include "directorylistermock.h"
#include "instreamprogrammer.h"
#include "QFileAdapterMock.h"
#include "qtextstreamfake.h"

#include <QDebug>

#include <memory>
using namespace std;
using ::testing::Return;
using ::testing::_;
using ::testing::Sequence;

class CppReaderTests : public ::testing::Test{
protected:
    QFileAdapterMock *file;
    QTextStreamFake *inStream;
    shared_ptr<DirectoryListerMock> dirLister;
    CppReader *reader;
    shared_ptr<FileStateTracker> state;
    DirectoryListModel *sourceDirs;
    DirectoryListModel *testDirs;
    QStringList files;
    QStringList headerFiles;

    CppReaderTests(){
        file = new QFileAdapterMock();
        inStream = new QTextStreamFake();
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

    inStream->setLines(fileContent);

    SourceCodeModel *model = reader->parseSourceCode(sourceDirs, testDirs);

    QModelIndex classIdx = model->index(0, 0, QModelIndex());
    QModelIndex funcIdx = model->index(0, 0, classIdx);

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

    inStream->setLines(fileContent);

    SourceCodeModel *model = reader->parseSourceCode(sourceDirs, testDirs);

    QModelIndex classIdx = model->index(0, 0, QModelIndex());
    QModelIndex funcIdx = model->index(0, 0, classIdx);

    EXPECT_EQ(1, model->rowCount(classIdx));
    EXPECT_EQ(QString("publicSlot"), model->data(funcIdx));
}

class CppReader_comments : public CppReaderTests{
protected:

    CppReader_comments(){
        sourceDirs->add("C:/sourceDir");
    }
};

/*! TEST_SPEC CppReader::parseSourceCode()
SHORT
When the parser encounters are commented line, it does
not extract function definitions from it.
*/
TEST_F(CppReader_comments, commented_functions_are_not_extracted){
    QStringList fileContent;

    EXPECT_CALL(*(dirLister.get()), listFiles(_,_))
            .WillOnce(Return(headerFiles))
            .WillRepeatedly(Return(files));

    fileContent << "/*! Short description"
                << "Longer description"
                << "*/"
                << "class ExampleClass {"
                << "public:"
                << "    void publicFunctionA();"
                << " // void commentedFunctionA();"
                << "    void publicFunctionB();"
                << " /*"
                << "    void commentedFunctionB();"
                << " */"
                << "    void publicFunctionC();"
                << "};";

    inStream->setLines(fileContent);

    SourceCodeModel *model = reader->parseSourceCode(sourceDirs, testDirs);

    QModelIndex classIdx = model->index(0, 0, QModelIndex());

    EXPECT_EQ(3, model->rowCount(classIdx));

    EXPECT_EQ(QString("publicFunctionA"), model->data(model->index(0, 0, classIdx)).toString());
    EXPECT_EQ(QString("publicFunctionB"), model->data(model->index(1, 0, classIdx)).toString());
    EXPECT_EQ(QString("publicFunctionC"), model->data(model->index(2, 0, classIdx)).toString());
}

/*! TEST_SPEC CppReader::parseSourceCode()
SHORT
When the parser encounters are commented line, it does
not extract class definitions from it.
*/
TEST_F(CppReader_comments, commented_classes_are_not_extracted){
    QStringList fileContent;

    EXPECT_CALL(*(dirLister.get()), listFiles(_,_))
            .WillOnce(Return(headerFiles))
            .WillRepeatedly(Return(files));

    fileContent << "/*! Short description"
                << "Longer description"
                << "*/"
                << "class ClassA {"
                << "};"
                << " "
                << "/*"
                << "class CommentedClassA{"
                << "};"
                << "*/"
                << "/*! Short description"
                << "Longer description"
                << "*/"
                << "class ClassB{"
                << "};"
                << " "
                << "// class CommentedClassB{"
                << "// };";

    inStream->setLines(fileContent);

    SourceCodeModel *model = reader->parseSourceCode(sourceDirs, testDirs);

    EXPECT_EQ(2, model->rowCount());
    EXPECT_EQ(QString("ClassA"), model->data(model->index(0, 0)).toString());
    EXPECT_EQ(QString("ClassB"), model->data(model->index(1, 0)).toString());
}

/*! TEST_SPEC CppReader::parseSourceCode()
SHORT
When a specification string contains code elements,
the specification string is extracted correctly.
*/
TEST_F(CppReader_comments, when_a_specification_contains_code_it_is_extracted_correctly){
    QStringList fileContent;

    EXPECT_CALL(*(dirLister.get()), listFiles(_,_))
            .WillOnce(Return(headerFiles))
            .WillRepeatedly(Return(files));

    fileContent << "/*! Description of class ClassA {};"
                << "void function();"
                << "*/"
                << "class ClassA {"
                << "public:"
                << "/*! void function(int a);"
                << "Description of function(int a)."
                << "*/"
                << "void function(int a);"
                << "};";

    inStream->setLines(fileContent);

    SourceCodeModel *model = reader->parseSourceCode(sourceDirs, testDirs);

    QModelIndex classIdx = model->index(0, 0);
    QModelIndex funcIdx = model->index(0, 0, classIdx);

    QString classDescription = "Description of class ClassA {};\n"
                               "void function();\n";

    QString funcDescription = "void function(int a);\n"
                              "Description of function(int a).\n";

    EXPECT_EQ(classDescription, model->getDescription(classIdx));
    EXPECT_EQ(funcDescription, model->getDescription(funcIdx));
}

/*! TEST_SPEC CppReader::parseSourceCode()
SHORT
When a specification string contains an empty first line,
the specification string is extracted correctly.
*/
TEST_F(CppReader_comments, a_specification_without_first_line_is_extracted_correctly){
    QStringList fileContent;

    EXPECT_CALL(*(dirLister.get()), listFiles(_,_))
            .WillOnce(Return(headerFiles))
            .WillRepeatedly(Return(files));

    fileContent << "/*!"
                << "Class Spec"
                << "*/"
                << "class ClassA {"
                << "public:"
                << "/*!"
                << "Function Spec"
                << "*/"
                << "void function(int a);"
                << "};";

    inStream->setLines(fileContent);

    SourceCodeModel *model = reader->parseSourceCode(sourceDirs, testDirs);

    QModelIndex classIdx = model->index(0, 0);
    QModelIndex funcIdx = model->index(0, 0, classIdx);

    QString classDescription = "\n"
                               "Class Spec\n";

    QString funcDescription = "\n"
                              "Function Spec\n";

    EXPECT_EQ(classDescription, model->getDescription(classIdx));
    EXPECT_EQ(funcDescription, model->getDescription(funcIdx));
}
