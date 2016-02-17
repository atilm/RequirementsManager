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
    void readTestSpecification(DirectoryListModel *testDirs);
    void extractClassesFromFile(const QString &filePath);
    bool openStream(const QString &filePath);
    void parseSourceLines();
    bool atClassBegin();
    void parseClass();
    QString extractClassName();
    void parseFunction(QModelIndex classIndex);
    QString extractFunctionName();
};

#endif // CPPREADER_H
