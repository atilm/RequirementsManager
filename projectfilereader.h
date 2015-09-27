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
    QFileAdapter *file;
    RequirementsModel *model;

    void readContents();
    void parseRequirement(QModelIndex item);
    QString getAttribute(const QString &name);
};

#endif // PROJECTFILEREADER_H
