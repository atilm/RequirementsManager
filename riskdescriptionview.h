#ifndef RISKDESCRIPTIONVIEW_H
#define RISKDESCRIPTIONVIEW_H

#include <QTextEdit>

class RiskDescriptionView : public QTextEdit
{
    Q_OBJECT
public:
    explicit RiskDescriptionView(QWidget *parent = 0);
    virtual ~RiskDescriptionView();

signals:

public slots:

};

#endif // RISKDESCRIPTIONVIEW_H
