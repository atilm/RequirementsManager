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
    QStringList headerFiles;
    QStringList testFiles;

    void readDesignSpecification(DirectoryListModel *sourceDirs);
};

#endif // AEROBASICREADER_H
