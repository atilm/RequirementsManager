#ifndef RISKASSESSMENTEDITCONTROLLER_H
#define RISKASSESSMENTEDITCONTROLLER_H

#include <QObject>

#include "riskassessmentmodel.h"
#include "risktableview.h"
#include "riskassessmentdialog.h"

class RiskAssessmentEditController : public QObject
{
    Q_OBJECT
public:
    RiskAssessmentEditController(RiskAssessmentDialog *dialog);
    virtual ~RiskAssessmentEditController();

    virtual void setModel(RiskAssessmentModel *model);
    virtual void setView(RiskTableView *view);

public slots:
    virtual void insertBeforeCurrent();
    virtual void removeCurrent();
    virtual void editCurrent();

private:
    RiskAssessmentModel *model;
    RiskTableView *view;
    RiskAssessmentDialog *dialog;
};

#endif // RISKASSESSMENTEDITCONTROLLER_H
