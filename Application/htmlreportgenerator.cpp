#include "htmlreportgenerator.h"

HtmlReportGenerator::HtmlReportGenerator(HtmlTemplateFactory *templateFactory,
                                         TextDocumentSerializer *documentSerializer, HtmlGenerator *html)
{
    model = nullptr;
    this->templateFactory = templateFactory;
    this->documentSerializer = documentSerializer;
    this->html = html;

    initializeTemplates();
}

HtmlReportGenerator::~HtmlReportGenerator()
{
    delete templateFactory;
    delete documentSerializer;
    delete html;
}

QString HtmlReportGenerator::getTypeString()
{
    return "Structured Html";
}

QString HtmlReportGenerator::getDescription()
{
    return "Generates a html report with a fixed structure. A SRS table"
           "contains all SRS nodes. A FRS table contains all SRS and FRS nodes."
           "A DS table contains SRS, FRS and DS nodes.";
}

void HtmlReportGenerator::setModel(shared_ptr<RequirementsModel> model)
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
    sectionHeaderTemplate = templateFactory->newTemplate();
    raTemplate = templateFactory->newTemplate();
    tpTemplate = templateFactory->newTemplate();

    documentTemplate->initialize("./Templates/ValidationDocumentTemplate.html");
    srsTemplate->initialize("./Templates/srsLineTemplate.html");
    frsTemplate->initialize("./Templates/frsLineTemplate.html");
    dsTemplate->initialize("./Templates/dsLineTemplate.html");
    sectionHeaderTemplate->initialize("./Templates/sectionHeaderTemplate.html");
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

    int riskCount = req->getRiskAssessment()->rowCount();
    QString message = riskCount != 0 ? "Risks:" : "N/A";
    lines.append(sectionHeader(req->number(), "RA", "DRS",
                               riskCount + 1, 5,
                               message));
    lines.append(getRARows(req));

    return lines;
}

QString HtmlReportGenerator::getRARows(Requirement *req)
{
    QString lines;

    shared_ptr<RiskAssessmentModel> ram = req->getRiskAssessment();

    for(int r=0; r < ram->rowCount(); r++){
        shared_ptr<RiskAssessment> ra = ram->getRiskAssessment(ram->index(r, 0));
        QString raNumber = constructRANumber(req->number(), r);

        raTemplate->setField("NUMBER", raNumber);
        raTemplate->setField("SCENARIO", html->toHtml(ra->scenario()));
        raTemplate->setField("INITIAL_RISK", ra->initialRisk(Qt::DisplayRole).toString());
        raTemplate->setField("ACTION", html->toHtml(ra->mitigationStrategy()));
        raTemplate->setField("FINAL_RISK", ra->finalRisk(Qt::DisplayRole).toString());
        raTemplate->setField("REF_ID", idString(raNumber, "RA"));
        raTemplate->setField("HREF", refString(raNumber, "TP"));

        lines.append(raTemplate->getHtml());
    }

    return lines;
}

QString HtmlReportGenerator::buildTPSection(const QModelIndex &index)
{
    QString lines;

    Requirement *req = model->getRequirement(index);

    lines.append(getTPRows(req));

    return lines;
}

QString HtmlReportGenerator::getTPRows(Requirement *req)
{
    QString lines;

    shared_ptr<RiskAssessmentModel> ram = req->getRiskAssessment();

    for(int r=0; r < ram->rowCount(); r++){
        shared_ptr<RiskAssessment> ra = ram->getRiskAssessment(ram->index(r, 0));
        QString raNumber = constructRANumber(req->number(), r);
        int testCount = ra->getPreventiveActions()->rowCount();
        QString message = testCount != 0 ? "Tests:" : "N/A";
        lines.append(sectionHeader(raNumber, "TP", "RA",
                                   testCount * 2 + 1, 3,
                                   message));
        lines.append(getTestPlan(ra, raNumber));
    }

    return lines;
}

QString HtmlReportGenerator::getTestPlan(shared_ptr<RiskAssessment> ra, const QString &raNumber)
{
    QString lines;

    shared_ptr<PreventiveActionModel> actions = ra->getPreventiveActions();

    for(int r=0; r < actions->rowCount(); r++){
        shared_ptr<PreventiveAction> action = actions->getAction(actions->index(r, 0));
        QString testNumber = constructTestNumber(raNumber, r);

        tpTemplate->setField("NUMBER", testNumber);
        tpTemplate->setField("IDENTIFIER", QString("%1::%2")
                             .arg(action->getTestCase())
                             .arg(action->getTestName()));
        tpTemplate->setField("SHORT_DESCRIPTION", action->getShortDescription());
        tpTemplate->setField("PREPARATION", html->toHtml(action->getPreparation()));
        tpTemplate->setField("ACTION", html->toHtml(action->getAction()));
        tpTemplate->setField("RESULT", html->toHtml(action->getExpectedResult()));

        lines.append(tpTemplate->getHtml());
    }

    return lines;
}

QString HtmlReportGenerator::sectionHeader(const QString &number,
                                           const QString &section,
                                           const QString &previousSection,
                                           int rowSpan, int colSpan,
                                           const QString &content)
{
    sectionHeaderTemplate->setField("REF_ID", idString(number, section));
    sectionHeaderTemplate->setField("BACK_REF", refString(number, previousSection));
    sectionHeaderTemplate->setField("NUMBER",number);
    sectionHeaderTemplate->setField("ROW_SPAN", rowSpan);
    sectionHeaderTemplate->setField("COL_SPAN", colSpan);
    sectionHeaderTemplate->setField("CONTENT", content);

    return sectionHeaderTemplate->getHtml();
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

