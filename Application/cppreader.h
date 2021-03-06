#ifndef CPPREADER_H
#define CPPREADER_H

#include "directorylister.h"
#include "isourcecodereader.h"
#include "sourcecodemodel.h"
#include "qfileadapter.h"
#include "qtextstreamadapter.h"
#include "testnode.h"

#include <memory>
using namespace std;

class CppReader : public ISourceCodeReader
{
public:
    CppReader(QFileAdapter *file,
              QTextStreamAdapter *inStream,
              shared_ptr<DirectoryLister> dirLister);
    virtual ~CppReader();

    /*! Get the reader's programming language name

     \return A QString, representing the programming language.
     */
    virtual QString language() const;

    virtual SourceCodeModel* parseSourceCode(DirectoryListModel *sourceDirs,
                                             DirectoryListModel *testDirs);
    virtual QStringList getFilePaths() const;

private:
    SourceCodeModel *model;
    QFileAdapter *file;
    QTextStreamAdapter *inStream;
    shared_ptr<DirectoryLister> dirLister;
    QString currentLine;
    QString lineBuffer;
    QStringList headerFiles;
    QStringList testFiles;

    enum TestParsingMode {
        ADDRESS,
        SHORT,
        PREPARATION,
        ACTION,
        RESULT,
        CODE
    };

    TestParsingMode testParsingMode;

    enum Scope{
        PUBLIC,
        PRIVATE,
        PROTECTED
    };

    Scope currentScope;
    bool insideComment;

    void nextLine(bool removeComments = true);
    QString removeInlineComment(const QString &s);
    void updateBlockCommentState(const QString &s);
    void readDesignSpecification(DirectoryListModel *sourceDirs);
    void parseSourceFilesInDirectory(const QString &dirPath);
    QStringList listHeaderFiles(const QString &dirPath);
    void extractClassesFromFile(const QString &filePath);
    bool openStream(const QString &filePath);
    void parseSourceLines();
    bool atClassBegin();
    void parseClass();
    bool atClassEnd();
    QString extractClassName();
    void parseFunction(QModelIndex classIndex);
    QString extractFunctionName();
    void parseDesignSpecBlock();

    void readTestSpecification(DirectoryListModel *testDirs);
    void parseTestFilesInDirectory(const QString &dirPath);
    QStringList listCppFiles(const QString &dirPath);
    void extractTestsFromFile(const QString &dirPath);
    void parseTestDefinitionFile();
    bool atTestBegin();
    void parseTest();
    void parseTestID(TestNode *test);
    SourceAddress extractTestSourceAddress();
    bool atTestEnd();
    void parseTestLine(TestNode *test);
    void skipDeclaration();

    QString extractBetween(const QString &start,
                           const QString &end,
                           const QString &s); 
};

#endif // CPPREADER_H
