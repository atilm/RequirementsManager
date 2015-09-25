#ifndef PROJECTFILEWRITER_H
#define PROJECTFILEWRITER_H

#include "requirementsmodel.h"
#include <QString>

class ProjectFileWriter
{
public:
    ProjectFileWriter();
    virtual ~ProjectFileWriter();

    virtual void save(RequirementsModel *model, const QString &filePath);
};

#endif // PROJECTFILEWRITER_H
