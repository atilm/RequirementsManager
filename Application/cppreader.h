#ifndef CPPREADER_H
#define CPPREADER_H

#include "isourcecodereader.h"
#include "sourcecodemodel.h"
#include "qfileadapter.h"
#include "qtextstreamadapter.h"
#include "testnode.h"

class CppReader : public ISourceCodeReader
{
public:
    CppReader(QFileAdapter *file,
              QTextStreamAdapter *inStream);
    virtual ~CppReader();

    virtual QString language() const;
    virtual SourceCodeModel* parseSourceCode(DirectoryListModel *sourceDirs,
                                             DirectoryListModel *testDirs);
    virtual QStringList getFilePaths() const;

private:
    SourceCodeModel *model;
    QFileAdapter *file;
    QTextStreamAdapter *inStream;
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

    void nextLine();
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
