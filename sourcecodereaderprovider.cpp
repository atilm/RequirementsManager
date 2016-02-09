#include "sourcecodereaderprovider.h"

SourceCodeReaderProvider::SourceCodeReaderProvider()
{

}

SourceCodeReaderProvider::~SourceCodeReaderProvider()
{

}

QStringList SourceCodeReaderProvider::availableLanguages() const
{
    QStringList languages;

    languages << "C++" << "Aerobasic" << "Python";

    return languages;
}

