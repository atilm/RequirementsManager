#include "riskdescriptionview.h"
#include <iostream>
using namespace std;

RiskDescriptionView::RiskDescriptionView(HtmlGenerator *html,
                                         QWidget *parent) :
    QTextEdit(parent)
{
    this->html = html;
    html->initTemplates(QString("./Templates/riskAssessmentDisplay.html"),
                        QString("./Templates/preventiveActionDisplay.html"));
}

RiskDescriptionView::~RiskDescriptionView()
{
    delete html;
}

void RiskDescriptionView::displayTestReference(TestNode *test)
{
    document()->setHtml(html->toHtml(*test));
}

void RiskDescriptionView::displayAction(shared_ptr<PreventiveAction> action)
{
    document()->setHtml(html->toHtml(*action));
}

void RiskDescriptionView::displayRisk(shared_ptr<RiskAssessment> risk)
{
    document()->setHtml(html->toHtml(*risk));
}

void RiskDescriptionView::clearDisplay()
{
    document()->clear();
}
