#include "sourcecodereaderprovider.h"

SourceCodeReaderProvider::SourceCodeReaderProvider()
{

}

SourceCodeReaderProvider::~SourceCodeReaderProvider()
{

}

void SourceCodeReaderProvider::addReader(ISourceCodeReader *reader)
{
    readers[reader->language()] = reader;
}

QStringList SourceCodeReaderProvider::availableLanguages() const
{
    QStringList languages;

    foreach(QString language, readers.keys())
        languages.append(language);

    return languages;
}

ISourceCodeReader *SourceCodeReaderProvider::getReader(const QString &language) const
{
    return readers[language];
}


