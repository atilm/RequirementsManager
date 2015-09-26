#ifndef PROJECTFILEREADER_H
#define PROJECTFILEREADER_H

#include "requirementsmodel.h"

class ProjectFileReader
{
public:
    ProjectFileReader();
    virtual ~ProjectFileReader();

    virtual void load(RequirementsModel *model, const QString &filePath);
};

#endif // PROJECTFILEREADER_H
