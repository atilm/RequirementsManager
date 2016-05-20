#include "htmlreportgenerator.h"

HtmlReportGenerator::HtmlReportGenerator(HtmlTemplateFactory *templateFactory,
                                         TextDocumentSerializer *documentSerializer)
{
    model = nullptr;
    this->templateFactory = templateFactory;
    this->documentSerializer = documentSerializer;

    initializeTemplates();
}

HtmlReportGenerator::~HtmlReportGenerator()
{
    delete templateFactory;
    delete documentSerializer;
}

void HtmlReportGenerator::setModel(RequirementsModel *model)
{
    this->model = model;
}

void HtmlReportGenerator::generate(const QString &filePath)
{
    file.setFileName(filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        out.setDevice(&file);

        out << generateHtml();
    }
    file.close();
}

void HtmlReportGenerator::initializeTemplates()
{
    documentTemplate = templateFactory->newTemplate();
    srsTemplate = templateFactory->newTemplate();
    frsTemplate = templateFactory->newTemplate();
    dsTemplate = templateFactory->newTemplate();

    documentTemplate->initialize("./Templates/ValidationDocumentTemplate.html");
    srsTemplate->initialize("./Templates/srsLineTemplate.html");
    frsTemplate->initialize("./Templates/frsLineTemplate.html");
    dsTemplate->initialize("./Templates/dsLineTemplate.html");
}

QString HtmlReportGenerator::generateHtml()
{
    documentTemplate->setField("SRS", generateSRS(QModelIndex()));
    documentTemplate->setField("FRS", generateFRS(QModelIndex()));
    documentTemplate->setField("DS", generateDS(QModelIndex()));
    return documentTemplate->getHtml();
}

QString HtmlReportGenerator::generateSRS(const QModelIndex &index)
{
    QString lines;

    if(isUserRequirement(index))
        lines.append(buildSRSString(index));

    for(int i=0;i < model->rowCount(index);i++)
        lines.append(generateSRS(model->index(i,0,index)));

    return lines;
}

QString HtmlReportGenerator::generateFRS(const QModelIndex &index)
{
    QString lines;

    if(isUserOrFunctionalRequirement(index))
        lines.append(buildFRSString(index));

    for(int i=0;i < model->rowCount(index);i++)
        lines.append(generateFRS(model->index(i,0,index)));

    return lines;
}

QString HtmlReportGenerator::generateDS(const QModelIndex &index)
{
    QString lines;

    if(index.isValid())
        lines.append(buildDSString(index));

    for(int i=0;i < model->rowCount(index);i++)
        lines.append(generateDS(model->index(i,0,index)));

    return lines;
}

QString HtmlReportGenerator::buildSRSString(const QModelIndex &index)
{
    Requirement *req = model->getRequirement(index);

    srsTemplate->setField("NUMBER", req->number());
    srsTemplate->setField("HREF", refString(req->number()));
    srsTemplate->setField("NAME", req->getTitle());
    QString description = documentSerializer->toSimpleHtml(req->getDescription());
    srsTemplate->setField("DESC", description);

    return srsTemplate->getHtml();
}

QString HtmlReportGenerator::buildFRSString(const QModelIndex &index)
{
    Requirement *req = model->getRequirement(index);

    frsTemplate->setField("REF_ID", idString(req->number()));
    frsTemplate->setField("NUMBER", req->number());
    frsTemplate->setField("HREF", refString(req->number()));
    frsTemplate->setField("NAME", req->getTitle());
    QString description = documentSerializer->toSimpleHtml(req->getDescription());
    frsTemplate->setField("DESC", description);

    return frsTemplate->getHtml();
}

QString HtmlReportGenerator::buildDSString(const QModelIndex &index)
{
    Requirement *req = model->getRequirement(index);

    dsTemplate->setField("REF_ID", idString(req->number()));
    dsTemplate->setField("NUMBER", req->number());
    dsTemplate->setField("HREF", refString(req->number()));
    dsTemplate->setField("NAME", req->getTitle());

    QString description;
    if(isDesignSpecification(index))
        description = documentSerializer->toSimpleHtml(req->getDescription());
    else
        description = "see above";

    dsTemplate->setField("DESC", description);

    return dsTemplate->getHtml();
}

QString HtmlReportGenerator::idString(const QString &s)
{
    return QString("id=\"%1\"").arg(refString(s));
}

QString HtmlReportGenerator::refString(QString s)
{
    return s.replace(".", "_");
}

bool HtmlReportGenerator::isUserRequirement(const QModelIndex &index)
{
    if(!index.isValid())
        return false;
    else
        return model->getType(index) == Requirement::UserRequirement;
}

bool HtmlReportGenerator::isDesignSpecification(const QModelIndex &index)
{
    if(!index.isValid())
        return false;
    else
        return model->getType(index) == Requirement::DesignRequirement;
}

bool HtmlReportGenerator::isUserOrFunctionalRequirement(const QModelIndex &index)
{
    if(!index.isValid())
        return false;
    else
        return !isDesignSpecification(index);
}

