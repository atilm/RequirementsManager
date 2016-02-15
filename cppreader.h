#ifndef CPPREADER_H
#define CPPREADER_H

#include "isourcecodereader.h"

class CppReader : public ISourceCodeReader
{
public:
    CppReader();
    virtual ~CppReader();

    virtual QString language() const;
    virtual SourceCodeModel* parseSourceCode(const QStringList &sourceDirs,
                                             const QStringList &testDirs) const;
};

#endif // CPPREADER_H
