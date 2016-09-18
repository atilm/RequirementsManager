#ifndef AEROBASICREADER_H
#define AEROBASICREADER_H

#include "directorylister.h"
#include "isourcecodereader.h"
#include "sourcecodemodel.h"
#include "qfileadapter.h"
#include "qtextstreamadapter.h"
#include "testnode.h"

#include <memory>
using namespace std;

class AerobasicReader : public ISourceCodeReader
{
public:
    AerobasicReader(QFileAdapter *file,
                    QTextStreamAdapter *inStream,
                    shared_ptr<DirectoryLister> dirLister);
    virtual ~AerobasicReader();

    virtual QString language() const;

    virtual SourceCodeModel* parseSourceCode(DirectoryListModel *sourceDirs,
                                             DirectoryListModel *testDirs);
    virtual QStringList getFilePaths() const;

private:
    SourceCodeModel *model;
    QFileAdapter *file;
    QTextStreamAdapter *inStream;
    shared_ptr<DirectoryLister> dirLister;
    QStringList sourceFiles;
    QStringList testFiles;

    void readDesignSpecification(DirectoryListModel *sourceDirs);
    void parseSourceFilesInDirectory(const QString &dirPath);
    QStringList listSourceFiles(const QString &dirPath);
    void extractFunctionsFromFile(const QString &filePath);
    bool openStream(const QString &filePath);
    void parseSourceLines(const QString &filePath);
    QString extractModuleName(const QString &filePath);
    void parseFunctionDefinition(const QModelIndex &parent, const QString &definition);
};

#endif // AEROBASICREADER_H
