#ifndef ISOURCECODEREADER_H
#define ISOURCECODEREADER_H

#include <QString>

#include "sourcecodemodel.h"
#include "directorylistmodel.h"

class ISourceCodeReader
{
public:
    virtual ~ISourceCodeReader() {}

    virtual QString language() const = 0;
    virtual SourceCodeModel* parseSourceCode(DirectoryListModel *sourceDirs,
                                             DirectoryListModel *testDirs) = 0;
};

#endif // ISOURCECODEREADER_H
