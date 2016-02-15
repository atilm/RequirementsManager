#ifndef SOURCECODEREADERPROVIDER_H
#define SOURCECODEREADERPROVIDER_H

#include <QStringList>
#include <QMap>

#include "isourcecodereader.h"

class SourceCodeReaderProvider
{
public:
    SourceCodeReaderProvider();
    virtual ~SourceCodeReaderProvider();

    virtual void addReader(ISourceCodeReader *reader);
    virtual QStringList availableLanguages() const;
    virtual ISourceCodeReader* getReader(const QString &language) const;

private:
    QMap<QString, ISourceCodeReader*> readers;
};

#endif // SOURCECODEREADERPROVIDER_H
