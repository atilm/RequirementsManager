#ifndef ISOURCECODEREADER_H
#define ISOURCECODEREADER_H

#include <QString>

#include "sourcecodemodel.h"

class ISourceCodeReader
{
public:
    virtual ~ISourceCodeReader() {}

    virtual QString language() const = 0;
    virtual SourceCodeModel* parseSourceCode(const QStringList &sourceDirs,
                                             const QStringList &testDirs) const = 0;
};

#endif // ISOURCECODEREADER_H
