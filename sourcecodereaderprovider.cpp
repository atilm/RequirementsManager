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
    if(!readers.contains(language))
        throw std::runtime_error(QString("No reader for language %1").arg(language).toStdString());

    return readers[language];
}


