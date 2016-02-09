#ifndef SOURCECODEREADERPROVIDER_H
#define SOURCECODEREADERPROVIDER_H

#include <QStringList>

class SourceCodeReaderProvider
{
public:
    SourceCodeReaderProvider();
    virtual ~SourceCodeReaderProvider();

    virtual QStringList availableLanguages() const;
};

#endif // SOURCECODEREADERPROVIDER_H
