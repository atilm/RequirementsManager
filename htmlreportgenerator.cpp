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

    documentTemplate->initialize("./Templates/ValidationDocumentTemplate.html");
    srsTemplate->initialize("./Templates/srsLineTemplate.html");
    frsTemplate->initialize("./Templates/frsLineTemplate.html");
}

QString HtmlReportGenerator::generateHtml()
{
    documentTemplate->setField("SRS", generateSRS());
    documentTemplate->setField("FRS", generateFRS());
    return documentTemplate->getHtml();
}

QString HtmlReportGenerator::generateSRS()
{
    QString lines;

    for(int i=0;i < model->rowCount();i++)
        lines.append(buildSRSString(model->index(i,0)));

    return lines;
}

QString HtmlReportGenerator::generateFRS()
{
    QString lines;

    for(int i=0;i < model->rowCount();i++){
        QModelIndex srsIdx = model->index(i,0);

        lines.append(buildFRSString(srsIdx));

        for(int j=0;j < model->rowCount(srsIdx);j++){
            QModelIndex frsIdx = model->index(j, 0, srsIdx);
            lines.append(buildFRSString(frsIdx));
        }
    }

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

QString HtmlReportGenerator::idString(const QString &s)
{
    return QString("id=\"%1\"").arg(refString(s));
}

QString HtmlReportGenerator::refString(QString s)
{
    return s.replace(".", "_");
}

