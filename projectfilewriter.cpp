#include "projectfilewriter.h"
#include "requirementsmodel.h"
#include "projectfilecontroller.h"
#include <stdexcept>
#include <QString>
#include <QObject>
using namespace std;

ProjectFileWriter::ProjectFileWriter(QXmlStreamWriter *xml)
{
    this->xml = xml;
}

ProjectFileWriter::~ProjectFileWriter()
{
    delete xml;
}

void ProjectFileWriter::save(ProjectFileController *fileController,
                             QFileAdapter *file)
{
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
        throw runtime_error(QObject::tr("Could not open file.").toStdString());

    this->file = file;
    this->fileController = fileController;
    this->model = fileController->getRequirementsModel();
    this->attributeContext = model->getAttributeContext();
    this->linkContext = model->getLinkContext();

    xml->setDevice(file);
    xml->setAutoFormatting(true);
    xml->writeStartDocument();
    xml->writeStartElement("RequirementSpecification");
    xml->writeAttribute("version", "1.0");

    writeProgrammingLanguage();
    writeSourceDirectories();
    writeTestDirectories();
    writeAttributeContext();
    writeLinkContext();
    writeRequirementSpecification();

    xml->writeEndElement(); // RequirementSpecification
    xml->writeEndDocument();

    this->file->close();
    this->model = NULL;
    this->file = NULL;
}

void ProjectFileWriter::writeProgrammingLanguage()
{
    xml->writeTextElement("Language",
                          fileController
                          ->getProgrammingLanguage());
}

void ProjectFileWriter::writeSourceDirectories()
{
    DirectoryListModel *model = fileController->sourceDirModel();

    for(int i=0;i<model->rowCount();i++){
        QString text = model->data(model->index(i),
                                   Qt::DisplayRole).toString();
        xml->writeTextElement("SourceDir", text);
    }
}

void ProjectFileWriter::writeTestDirectories()
{
    DirectoryListModel *model = fileController->testDirModel();

    for(int i=0;i<model->rowCount();i++){
        QString text = model->data(model->index(i),
                                   Qt::DisplayRole).toString();
        xml->writeTextElement("TestDir", text);
    }
}

void ProjectFileWriter::writeAttributeContext()
{
    xml->writeStartElement("AttributeContext");

    for(int a=0;a < attributeContext->rowCount();a++)
        writeAttributeDeclaration(a);

    xml->writeEndElement(); // AttributeContext
}

void ProjectFileWriter::writeLinkContext()
{
    xml->writeStartElement("LinkContext");

    for(int i=0;i < linkContext->rowCount();i++)
        writeLinkGroupDeclaration(i);

    xml->writeEndElement();
}

void ProjectFileWriter::writeLinkGroupDeclaration(int index)
{
    xml->writeStartElement("LinkDeclaration");
    xml->writeAttribute("index", QString("%1").arg(index));
    xml->writeAttribute("name", linkContext->typeName(index));
    xml->writeEndElement();
}

void ProjectFileWriter::writeAttributeDeclaration(int index)
{
    xml->writeStartElement("AttributeDeclaration");
    xml->writeAttribute("index", QString("%1").arg(index));
    xml->writeAttribute("name", attributeContext->name(index));
    xml->writeAttribute("type", attributeContext->typeString(index));
    xml->writeEndElement(); // Attribute
}

void ProjectFileWriter::writeRequirementSpecification()
{
    xml->writeStartElement("RequirementSpecification");
    writeChildrenOf(QModelIndex());
    xml->writeEndElement();
}

void ProjectFileWriter::writeChildrenOf(QModelIndex parent)
{
    int rowCount = model->rowCount(parent);
    for(int row=0;row < rowCount;row++){
        writeRequirement(row, parent);
    }
}

void ProjectFileWriter::writeRequirement(int row, QModelIndex parent)
{
    xml->writeStartElement("Requirement");

    QModelIndex itemIdx = model->index(row, 0, parent);
    QString title = model->getRequirement(itemIdx)->getTitle();
    QString id = QString("%1").arg(model->getID(itemIdx));
    QString type = Requirement::typeToString(model->getType(itemIdx));
    QTextDocument *description = model->getDescription(itemIdx);

    xml->writeAttribute("id", id);
    xml->writeAttribute("type", type);
    xml->writeAttribute("name", title);

    xml->writeStartElement("description");
    xml->writeCDATA(description->toHtml());
    xml->writeEndElement(); // description

    for(int a=0;a < attributeContext->rowCount();a++)
        writeAttribute(parent, row, a);

    writeLinks(itemIdx);

    writeRiskAssessmentModel(model->getRiskAssessment(itemIdx));

    writeChildrenOf(itemIdx);

    xml->writeEndElement(); // Requirement
}

void ProjectFileWriter::writeAttribute(const QModelIndex &parent, int row, int attributeIndex)
{
    QString value = getAttributeValue(parent, row, attributeIndex);

    xml->writeStartElement("Attribute");
    xml->writeAttribute("index", QString("%1").arg(attributeIndex));
    xml->writeAttribute("value", value);
    xml->writeEndElement();
}

void ProjectFileWriter::writeLinks(const QModelIndex &itemIdx)
{
    LinkContainer *links = model->getLinkContainer(itemIdx);
    for(int g=0; g<links->rowCount(); g++){
        LinkGroup *group = links->getLinkGroup(g);
        for(int c=0; c<group->childCount(); c++){
            LinkToRequirement *link = group->getLink(c);
            xml->writeStartElement("Link");
            xml->writeAttribute("group", QString("%1").arg(g));
            xml->writeAttribute("id", QString("%1").arg(link->getID()));
            xml->writeEndElement();
        }
    }
}

void ProjectFileWriter::writeRiskAssessmentModel(RiskAssessmentModel *risks)
{
    for(int r=0;r<risks->rowCount();r++)
        writeRiskAssessment(risks->getRiskAssessment(risks->index(r,0)));
}

void ProjectFileWriter::writeRiskAssessment(RiskAssessment *risk)
{
    xml->writeStartElement("RiskAssessment");
    xml->writeAttribute("initialProbability",
                        intToString(risk->initialRiskModel()->getCurrentRisk().column()));
    xml->writeAttribute("initialDamage",
                        intToString(risk->initialRiskModel()->getCurrentRisk().row()));
    xml->writeAttribute("finalProbability",
                        intToString(risk->finalRiskModel()->getCurrentRisk().column()));
    xml->writeAttribute("finalDamage",
                        intToString(risk->finalRiskModel()->getCurrentRisk().row()));
    xml->writeTextElement("scenario", risk->scenario());
    xml->writeTextElement("mitigationStrategy", risk->mitigationStrategy());
    writePreventiveActions(risk->getPreventiveActions());

    xml->writeEndElement();
}

void ProjectFileWriter::writePreventiveActions(PreventiveActionModel *actions)
{
    for(int r=0;r<actions->rowCount();r++)
        writePreventiveAction(actions->getAction(actions->index(r,0)));
}

void ProjectFileWriter::writePreventiveAction(PreventiveAction *action)
{
    xml->writeStartElement("Action");
    xml->writeAttribute("case", action->getTestCase());
    xml->writeAttribute("name", action->getTestName());
    xml->writeTextElement("short", action->getShortDescription());
    xml->writeTextElement("preparation", action->getPreparation());
    xml->writeTextElement("action", action->getAction());
    xml->writeTextElement("result", action->getExpectedResult());
    xml->writeEndElement();
}

QString ProjectFileWriter::getAttributeValue(const QModelIndex &parent, int row, int attributeIndex)
{
    QModelIndex itemIdx = model->index(row, attributeIndex+1, parent);

    switch(attributeContext->type(attributeIndex)){
    case AttributeContext::BOOLEAN:
        return checkStateToString(model->data(itemIdx, Qt::CheckStateRole));
    case AttributeContext::TEXT:
        return model->data(itemIdx, Qt::DisplayRole).toString();
    }
}

QString ProjectFileWriter::checkStateToString(const QVariant &value)
{
    switch(value.toInt()){
    case Qt::Checked:
        return "yes";
    case Qt::Unchecked:
        return "no";
    default:
        return "";
    }
}

QString ProjectFileWriter::intToString(int n)
{
    return QString("%1").arg(n);
}

