#ifndef ISOURCECODEREADER_H
#define ISOURCECODEREADER_H

#include <QStringList>

class ISourceCodeReader
{
public:
    virtual ~ISourceCodeReader() {}

    virtual QStringList availableLanguages() const = 0;
    // virtual CodeContainer* parseSourceCode() const = 0;

};

#endif // ISOURCECODEREADER_H
