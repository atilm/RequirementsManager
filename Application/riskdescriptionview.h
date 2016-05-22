#ifndef RISKDESCRIPTIONVIEW_H
#define RISKDESCRIPTIONVIEW_H

#include <QTextEdit>

#include "preventiveaction.h"
#include "riskassessment.h"
#include "htmlgenerator.h"
#include "testnode.h"

class RiskDescriptionView : public QTextEdit
{
    Q_OBJECT
public:
    explicit RiskDescriptionView(HtmlGenerator *html,
                                 QWidget *parent = 0);
    virtual ~RiskDescriptionView();

    virtual void displayTestReference(TestNode *test);
    virtual void displayAction(PreventiveAction *action);
    virtual void displayRisk(RiskAssessment *risk);
    virtual void clearDisplay();

signals:

public slots:

private:
    HtmlGenerator *html;
};

#endif // RISKDESCRIPTIONVIEW_H
