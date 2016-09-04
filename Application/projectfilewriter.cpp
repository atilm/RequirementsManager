#include "projectfilewriter.h"
#include "requirementreference.h"
#include "requirementsmodel.h"
#include "projectfilecontroller.h"
#include "automatedtestreference.h"
#include <stdexcept>
#include <QDebug>
#include <QObject>
#include <QString>
using namespace std;

ProjectFileWriter::ProjectFileWriter(QXmlStreamWriter *xml,
                                     TextDocumentSerializer *serializer,
                                     RichTextResourceManager *resourceManger)
{
    this->xml = xml;
    this->serializer = serializer;
    this->resourceManger = resourceManger;
}

ProjectFileWriter::~ProjectFileWriter()
{
    delete xml;
    delete serializer;
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
    resourceManger->beginSavingResources();
    xml->writeStartElement("RequirementSpecification");
    writeChildrenOf(QModelIndex());
    xml->writeEndElement();
    resourceManger->endSavingResources();
}

void ProjectFileWriter::writeChildrenOf(QModelIndex parent)
{
    int rowCount = model->rowCount(parent);
    for(int row=0;row < rowCount;row++){
        writeRequirement(row, parent);
    }
}

void ProjectFileWriter::writeRequirement(int row, QModelIndex &parent)
{
    QModelIndex itemIdx = model->index(row, 0, parent);

    Requirement *requirement = model->getRequirement(itemIdx);

    RequirementReference *reqRef = dynamic_cast<RequirementReference*>(requirement);

    if(reqRef)
    {
        xml->writeStartElement("RequirementReference");
        writeReqReferenceContent(itemIdx, reqRef);
    }
    else if(requirement->isReference())
    {
        xml->writeStartElement("DesignReference");
        writeReferenceContent(itemIdx, requirement);
    }
    else
    {
        xml->writeStartElement("Requirement");
        writeRequirementContent(itemIdx, requirement);
    }

    for(int a=0;a < attributeContext->rowCount();a++){
        writeAttribute(parent, row, a);
    }

    writeLinks(itemIdx);

    writeRiskAssessmentModel(model->getRiskAssessment(itemIdx));

    writeChildrenOf(itemIdx);

    xml->writeEndElement(); // Requirement / DesignReference / RequirementReference
}

void ProjectFileWriter::writeReqReferenceContent(const QModelIndex &index,
                                                 RequirementReference *reqRef)
{
    write_ID_and_Type(index);

    xml->writeAttribute("linkID", QString::number(reqRef->getTargetID()));
}

void ProjectFileWriter::writeReferenceContent(const QModelIndex &index,
                                              Requirement *requirement)
{
    write_ID_and_Type(index);

    DesignReference *ref = static_cast<DesignReference*>(requirement);
    SourceAddress address = ref->getAddress();

    xml->writeAttribute("class", address.className);
    xml->writeAttribute("func", address.functionName);
}

void ProjectFileWriter::writeRequirementContent(const QModelIndex &index,
                                                Requirement *requirement)
{
    write_ID_and_Type(index);

    QString title = requirement->getTitle();
    QTextDocument *description = model->getDescription(index);

    xml->writeAttribute("name", title);

    xml->writeStartElement("description");
    xml->writeCDATA(serializer->toSimpleHtml(description));
    xml->writeEndElement(); // description
}

void ProjectFileWriter::write_ID_and_Type(const QModelIndex &itemIdx)
{
    QString id = QString("%1").arg(model->getID(itemIdx));
    QString type = Requirement::typeToString(model->getType(itemIdx));
    xml->writeAttribute("id", id);
    xml->writeAttribute("type", type);
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

void ProjectFileWriter::writeRiskAssessmentModel(shared_ptr<RiskAssessmentModel> risks)
{
    for(int r=0;r<risks->rowCount();r++)
        writeRiskAssessment(risks->getRiskAssessment(risks->index(r,0)));
}

void ProjectFileWriter::writeRiskAssessment(shared_ptr<RiskAssessment> risk)
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

void ProjectFileWriter::writePreventiveActions(shared_ptr<PreventiveActionModel> actions)
{
    for(int r=0;r<actions->rowCount();r++)
        writePreventiveAction(actions->getAction(actions->index(r,0)));
}

void ProjectFileWriter::writePreventiveAction(shared_ptr<PreventiveAction> action)
{
    if(action->isReference())
        writeTestReference(action);
    else
        writePreventiveActionContent(action);
}

void ProjectFileWriter::writeTestReference(shared_ptr<PreventiveAction> action)
{
    shared_ptr<AutomatedTestReference> ref = static_pointer_cast<AutomatedTestReference>(action);
    SourceAddress address = ref->getAddress();

    xml->writeStartElement("TestReference");
    xml->writeAttribute("class", address.className);
    xml->writeAttribute("func", address.functionName);
    xml->writeAttribute("case", address.testCase);
    xml->writeAttribute("name", address.testName);
    xml->writeEndElement();
}

void ProjectFileWriter::writePreventiveActionContent(shared_ptr<PreventiveAction> action)
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
    default:
        return QString();
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

