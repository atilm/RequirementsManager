#ifndef CPPREADER_H
#define CPPREADER_H

#include "isourcecodereader.h"
#include "sourcecodemodel.h"
#include "qfileadapter.h"
#include "qtextstreamadapter.h"

class CppReader : public ISourceCodeReader
{
public:
    CppReader(QFileAdapter *file,
              QTextStreamAdapter *inStream);
    virtual ~CppReader();

    virtual QString language() const;
    virtual SourceCodeModel* parseSourceCode(DirectoryListModel *sourceDirs,
                                             DirectoryListModel *testDirs);

private:
    SourceCodeModel *model;
    QFileAdapter *file;
    QTextStreamAdapter *inStream;
    QString currentLine;

    void readDesignSpecification(DirectoryListModel *sourceDirs);
    void parseSourceFilesInDirectory(const QString &dirPath);
    QStringList listHeaderFiles(const QString &dirPath);
    void extractClassesFromFile(const QString &filePath);
    bool openStream(const QString &filePath);
    void parseSourceLines();
    bool atClassBegin();
    void parseClass();
    QString extractClassName();
    void parseFunction(QModelIndex classIndex);
    QString extractFunctionName();

    void readTestSpecification(DirectoryListModel *testDirs);
    void parseTestFilesInDirectory(const QString &dirPath);
    QStringList listCppFiles(const QString &dirPath);
    void extractTestsFromFile(const QString &dirPath);
    void parseTestDefinitionFile();
    bool atTestBegin();
    void parseTest();
};

#endif // CPPREADER_H
