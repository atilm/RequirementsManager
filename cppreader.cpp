#include "cppreader.h"

CppReader::CppReader()
{

}

CppReader::~CppReader()
{

}

QString CppReader::language() const
{
    return "C++";
}

SourceCodeModel *CppReader::parseSourceCode(const QStringList &sourceDirs,
                                            const QStringList &testDirs) const
{
    return nullptr;
}

