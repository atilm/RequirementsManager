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
    requirementTemplate = templateFactory->newTemplate();
    raTemplate = templateFactory->newTemplate();
    tpTemplate = templateFactory->newTemplate();

    documentTemplate->initialize("./Templates/ValidationDocumentTemplate.html");
    srsTemplate->initialize("./Templates/srsLineTemplate.html");
    frsTemplate->initialize("./Templates/frsLineTemplate.html");
    dsTemplate->initialize("./Templates/dsLineTemplate.html");
    requirementTemplate->initialize("./Templates/requirementLineTemplate.html");
    raTemplate->initialize("./Templates/raLineTemplate.html");
    tpTemplate->initialize("./Templates/tpLineTemplate.html");
}

QString HtmlReportGenerator::generateHtml()
{
    documentTemplate->setField("SRS", generateSRS(QModelIndex()));
    documentTemplate->setField("FRS", generateFRS(QModelIndex()));
    documentTemplate->setField("DS", generateDS(QModelIndex()));
    documentTemplate->setField("RA", generateRA(QModelIndex()));
    documentTemplate->setField("TP", generateTP(QModelIndex()));
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

QString HtmlReportGenerator::generateRA(const QModelIndex &index)
{
    QString lines;

    if(index.isValid())
        lines.append(buildRASection(index));

    for(int i=0;i < model->rowCount(index);i++)
        lines.append(generateRA(model->index(i,0,index)));

    return lines;
}

QString HtmlReportGenerator::generateTP(const QModelIndex &index)
{
    QString lines;

    if(index.isValid())
        lines.append(buildTPSection(index));

    for(int i=0;i < model->rowCount(index);i++)
        lines.append(generateTP(model->index(i,0,index)));

    return lines;
}

QString HtmlReportGenerator::buildSRSString(const QModelIndex &index)
{
    Requirement *req = model->getRequirement(index);

    srsTemplate->setField("NUMBER", req->number());
    srsTemplate->setField("HREF", refString(req->number(), "FRS"));
    srsTemplate->setField("NAME", req->getTitle());
    QString description = documentSerializer->toSimpleHtml(req->getDescription());
    srsTemplate->setField("DESC", description);

    return srsTemplate->getHtml();
}

QString HtmlReportGenerator::buildFRSString(const QModelIndex &index)
{
    Requirement *req = model->getRequirement(index);

    frsTemplate->setField("REF_ID", idString(req->number(), "FRS"));
    frsTemplate->setField("NUMBER", req->number());
    frsTemplate->setField("HREF", refString(req->number(), "DRS"));
    frsTemplate->setField("NAME", req->getTitle());
    QString description = documentSerializer->toSimpleHtml(req->getDescription());
    frsTemplate->setField("DESC", description);

    return frsTemplate->getHtml();
}

QString HtmlReportGenerator::buildDSString(const QModelIndex &index)
{
    Requirement *req = model->getRequirement(index);

    dsTemplate->setField("REF_ID", idString(req->number(), "DRS"));
    dsTemplate->setField("NUMBER", req->number());
    dsTemplate->setField("HREF", refString(req->number(), "RA"));
    dsTemplate->setField("NAME", req->getTitle());

    QString description;
    if(isDesignSpecification(index))
        description = documentSerializer->toSimpleHtml(req->getDescription());
    else
        description = "see above";

    dsTemplate->setField("DESC", description);

    return dsTemplate->getHtml();
}

QString HtmlReportGenerator::buildRASection(const QModelIndex &index)
{
    QString lines;

    Requirement *req = model->getRequirement(index);

    lines.append(getRepeatedRequirementRow(req, "RA", 4));
    lines.append(getRARows(req));

    return lines;
}

QString HtmlReportGenerator::getRARows(Requirement *req)
{
    QString lines;

    RiskAssessmentModel *ram = req->getRiskAssessment();

    for(int r=0; r < ram->rowCount(); r++){
        RiskAssessment *ra = ram->getRiskAssessment(ram->index(r, 0));
        QString raNumber = constructRANumber(req->number(), r);

        raTemplate->setField("NUMBER", raNumber);
        raTemplate->setField("SCENARIO", ra->scenario());
        raTemplate->setField("INITIAL_RISK", ra->initialRisk(Qt::DisplayRole).toString());
        raTemplate->setField("ACTION", ra->mitigationStrategy());
        raTemplate->setField("FINAL_RISK", ra->finalRisk(Qt::DisplayRole).toString());
        raTemplate->setField("REF_ID", idString(raNumber, "RA"));
        raTemplate->setField("HREF", refString(req->number(), "TP"));
        raTemplate->setField("BACK_REF", refString(req->number(), "DRS"));

        lines.append(raTemplate->getHtml());
    }

    return lines;
}

QString HtmlReportGenerator::buildTPSection(const QModelIndex &index)
{
    QString lines;

    Requirement *req = model->getRequirement(index);

    lines.append(getRepeatedRequirementRow(req, "TP", 4));
    lines.append(getTPRows(req));

    return lines;
}

QString HtmlReportGenerator::getTPRows(Requirement *req)
{
    QString lines;

    RiskAssessmentModel *ram = req->getRiskAssessment();

    for(int r=0; r < ram->rowCount(); r++){
        RiskAssessment *ra = ram->getRiskAssessment(ram->index(r, 0));
        QString raNumber = constructRANumber(req->number(), r);
        lines.append(getTestPlan(ra, raNumber));
    }

    return lines;
}

QString HtmlReportGenerator::getTestPlan(RiskAssessment *ra, const QString &raNumber)
{
    QString lines;

    PreventiveActionModel *actions = ra->getPreventiveActions();

    for(int r=0; r < actions->rowCount(); r++){
        PreventiveAction *action = actions->getAction(actions->index(r, 0));
        QString testNumber = constructTestNumber(raNumber, r);

        tpTemplate->setField("NUMBER", testNumber);
        tpTemplate->setField("IDENTIFIER", QString("%1::%2")
                             .arg(action->getTestCase())
                             .arg(action->getTestName()));
        tpTemplate->setField("SHORT_DESCRIPTION", action->getShortDescription());
        tpTemplate->setField("PREPARATION", action->getPreparation());
        tpTemplate->setField("ACTION", action->getAction());
        tpTemplate->setField("RESULT", action->getExpectedResult());
        tpTemplate->setField("BACK_REF", refString("raNumber", "RA"));

        lines.append(tpTemplate->getHtml());
    }

    return lines;
}

QString HtmlReportGenerator::getRepeatedRequirementRow(Requirement *req,
                                                       const QString &section,
                                                       int colSpan)
{
    requirementTemplate->setField("REF_ID", idString(req->number(), section));
    requirementTemplate->setField("BACK_REF", refString(req->number(), "DRS"));
    requirementTemplate->setField("NUMBER", req->number());
    requirementTemplate->setField("NAME", req->getTitle());
    requirementTemplate->setField("COL_SPAN", colSpan);

    return requirementTemplate->getHtml();
}

QString HtmlReportGenerator::idString(const QString &s, const QString &section)
{
    return QString("id=\"%1_%2\"").arg(section).arg(underscored(s));
}

QString HtmlReportGenerator::refString(const QString &s, const QString &section)
{
    return QString("href=\"#%1_%2\"").arg(section).arg(underscored(s));
}

QString HtmlReportGenerator::underscored(QString s)
{
    return s.replace(".", "_");
}

QString HtmlReportGenerator::constructRANumber(const QString &reqNumber, int raModelIndex)
{
    return reqNumber + QString("-RA%1").arg(raModelIndex+1);
}

QString HtmlReportGenerator::constructTestNumber(const QString &raNumber, int testModelIndex)
{
    return raNumber + QString("-T%1").arg(testModelIndex+1);
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

