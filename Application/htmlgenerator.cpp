#include "htmlgenerator.h"

#include <QStringList>

HtmlGenerator::HtmlGenerator(HtmlTemplateFactory *_templateFactory)
{
    templateFactory = _templateFactory;
    actionTemplate = NULL;
    riskAssessmentTemplate = NULL;
}

HtmlGenerator::~HtmlGenerator()
{
    delete templateFactory;
    delete actionTemplate;
    delete riskAssessmentTemplate;
}

void HtmlGenerator::initTemplates(QString riskPath, QString actionPath)
{
    if(!templateFactory)
        return;

    actionTemplate = templateFactory->newTemplate();
    riskAssessmentTemplate = templateFactory->newTemplate();

    actionTemplate->initialize(actionPath);
    riskAssessmentTemplate->initialize(riskPath);
}

QString HtmlGenerator::toHtml(const TestNode &test)
{
    if(!actionTemplate)
        return QString();

    actionTemplate->setField("CASE", test.getTestCase());
    actionTemplate->setField("NAME", test.getTestName());
    actionTemplate->setField("DESCRIPTION", test.getShortDescription());
    actionTemplate->setField("PREPARATION", toHtml(test.getPreparation()));
    actionTemplate->setField("ACTION", toHtml(test.getAction()));
    actionTemplate->setField("RESULT", toHtml(test.getExpectedResult()));

    return actionTemplate->getHtml();
}

QString HtmlGenerator::toHtml(PreventiveAction &action)
{
    if(!actionTemplate)
        return QString();

    actionTemplate->setField("CASE", action.getTestCase());
    actionTemplate->setField("NAME", action.getTestName());
    actionTemplate->setField("DESCRIPTION", action.getShortDescription());
    actionTemplate->setField("PREPARATION", toHtml(action.getPreparation()));
    actionTemplate->setField("ACTION", toHtml(action.getAction()));
    actionTemplate->setField("RESULT", toHtml(action.getExpectedResult()));

    return actionTemplate->getHtml();
}

QString HtmlGenerator::toHtml(const RiskAssessment &risk)
{
    if(!riskAssessmentTemplate)
        return QString();

    riskAssessmentTemplate->setField("SCENARIO", toHtml(risk.scenario()));
    riskAssessmentTemplate->setField("MITIGATION_STRATEGY", toHtml(risk.mitigationStrategy()));

    riskAssessmentTemplate->setField("INITIAL_PROBABILITY", risk.initialRiskModel()->probability());
    riskAssessmentTemplate->setField("INITIAL_DAMAGE", risk.initialRiskModel()->damageExtent());
    riskAssessmentTemplate->setField("INITIAL_RISK", risk.initialRisk(Qt::DisplayRole).toString());

    riskAssessmentTemplate->setField("FINAL_PROBABILITY", risk.finalRiskModel()->probability());
    riskAssessmentTemplate->setField("FINAL_DAMAGE", risk.finalRiskModel()->damageExtent());
    riskAssessmentTemplate->setField("FINAL_RISK", risk.finalRisk(Qt::DisplayRole).toString());

    return riskAssessmentTemplate->getHtml();
}

QString HtmlGenerator::toHtml(const QString &markupText, HeaderType headingType)
{
    QStringList lines = markupText.split("\n");
    QStringList nLines;
    bool inList = false;

    if(headingType == FIRST_LINE && lines.count() > 0)
        lines[0] = QString("<b>%1</b>").arg(lines[0]);

    foreach(QString line, lines){

        if(line.contains("\\param")){
            QStringList fields = line.split(QRegExp("\\s"), QString::SkipEmptyParts);
            QString paramName = fields[1];
            fields.pop_front();
            fields.pop_front();
            QString description = fields.join(" ");

            line = QString("<b>Parameter</b> <i>%1</i> %2")
                    .arg(paramName)
                    .arg(description);
        }

        QString trimmed = line.trimmed();

        if(trimmed.startsWith("-") && trimmed.mid(1,1) != ">"){
            if(!inList){
                nLines.append("<ul>");
                inList = true;
            }
            else{
                line += "</li>";
            }
            line = QString("<li>%1").arg(trimmed.mid(1));
        }
        else if(line.isEmpty()){
            if(inList){
                nLines.append("</li></ul>");
                inList = false;
            }
        }
        else
            line = trimmed;

        line = line.replace("->", "&#8658;");
        line = line.replace("\\return", "<b>Returns: </b>");
        line = line.replace("\\throws", "<b>Throws: </b>");
        line = line.replace("\\todo", "<b>To Do: </b>");
        line = line.replace("\\note", "<b>Note: </b>");

        if(!inList)
            line.append("<br>");

        nLines.append(line);
    }

    return nLines.join("\r\n");
}

QString HtmlGenerator::escape(QString s)
{
    s.replace("\n", "<br>\n")
            .replace(" ", "&nbsp;");

    return s;
}
