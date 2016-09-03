#ifndef PREVENTIVEACTIONTABLEVIEW_H
#define PREVENTIVEACTIONTABLEVIEW_H

#include <QTableView>
#include "requirementsmodel.h"
#include "riskassessmentmodel.h"
#include "risktableview.h"
#include "preventiveactionmodel.h"
#include "automatedtestreference.h"

class PreventiveActionTableView : public QTableView
{
    Q_OBJECT
public:
    explicit PreventiveActionTableView(QWidget *parent = 0);
    virtual ~PreventiveActionTableView();

    virtual void appendTestReference(shared_ptr<AutomatedTestReference> testRef);
};

#endif // PREVENTIVEACTIONTABLEVIEW_H
