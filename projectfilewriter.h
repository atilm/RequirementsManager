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
    RequirementsModel *model;
    AttributeContext *attributeContext;
    QFileAdapter *file;

    void writeAttributeContext();
    void writeAttributeDeclaration(int index);
    void writeChildrenOf(QModelIndex parent);
    void writeRequirement(int row, QModelIndex parent);
    void writeAttribute(const QModelIndex &parent, int row, int attributeIndex);
};

#endif // PROJECTFILEWRITER_H
