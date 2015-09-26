#ifndef PROJECTFILEREADER_H
#define PROJECTFILEREADER_H

#include "requirementsmodel.h"
#include "qfileadapter.h"
#include <QXmlStreamReader>

class ProjectFileReader
{
public:
    ProjectFileReader(QXmlStreamReader *xml);
    virtual ~ProjectFileReader();

    virtual void load(RequirementsModel *model, QFileAdapter *file);

private:
    QXmlStreamReader *xml;
};

#endif // PROJECTFILEREADER_H
