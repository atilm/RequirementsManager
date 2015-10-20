#ifndef RISKTABLEVIEW_H
#define RISKTABLEVIEW_H

#include <QTableView>
#include "requirementsmodel.h"
#include "riskassessmentmodel.h"
#include "riskassessmenteditcontroller.h"

class RiskTableView : public QTableView
{
    Q_OBJECT
public:
    explicit RiskTableView(RiskAssessmentEditController *editController,
                           QWidget *parent = 0);
    virtual ~RiskTableView();

    virtual void setRequirementsModel(RequirementsModel *requirements);
    virtual void setEditController(RiskAssessmentEditController *editController);

signals:

public slots:
    virtual void currentRequirementChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void insertBeforeCurrent();
    virtual void removeCurrent();

private:
    RequirementsModel *requirements;
    RiskAssessmentEditController *editController;

    RiskAssessmentModel* riskAssessmentModel();
};

#endif // RISKTABLEVIEW_H
