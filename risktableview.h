#ifndef RISKTABLEVIEW_H
#define RISKTABLEVIEW_H

#include <QTableView>

class RiskTableView : public QTableView
{
    Q_OBJECT
public:
    explicit RiskTableView(QWidget *parent = 0);
    virtual ~RiskTableView();

signals:

public slots:

};

#endif // RISKTABLEVIEW_H
