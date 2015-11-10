#ifndef PREVENTIVEACTIONTABLEVIEW_H
#define PREVENTIVEACTIONTABLEVIEW_H

#include <QTableView>
#include "requirementsmodel.h"
#include "riskassessmentmodel.h"
#include "risktableview.h"
#include "preventiveactionmodel.h"

class PreventiveActionTableView : public QTableView
{
    Q_OBJECT
public:
    explicit PreventiveActionTableView(QWidget *parent = 0);
    virtual ~PreventiveActionTableView();

};

#endif // PREVENTIVEACTIONTABLEVIEW_H
