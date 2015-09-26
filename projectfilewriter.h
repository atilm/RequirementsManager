#ifndef PROJECTFILEWRITER_H
#define PROJECTFILEWRITER_H

#include "requirementsmodel.h"
#include "qfileadapter.h"
#include <QString>
#include <QXmlStreamWriter>

class ProjectFileWriter
{
public:
    ProjectFileWriter(QXmlStreamWriter *xml);
    virtual ~ProjectFileWriter();

    virtual void save(RequirementsModel *model, QFileAdapter *file);

private:
    QXmlStreamWriter *xml;
};

#endif // PROJECTFILEWRITER_H
