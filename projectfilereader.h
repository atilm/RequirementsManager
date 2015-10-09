#ifndef PROJECTFILEREADER_H
#define PROJECTFILEREADER_H

#include "requirementsmodel.h"
#include "qfileadapter.h"
#include <QXmlStreamReader>
#include <stdexcept>

class ParsingError : public runtime_error{
public:
    ParsingError(const string &arg) : runtime_error(arg) {}
};

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
    AttributeContext *attributeContext;

    void readContents();
    void parseAttributeDeclaration();
    void parseRequirement(QModelIndex parent);
    QString getAttribute(const QString &name);
};

#endif // PROJECTFILEREADER_H
