#ifndef RISKASSESSMENTMODEL_H
#define RISKASSESSMENTMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "riskassessmentfactory.h"
#include "riskassessment.h"

class RiskAssessmentModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    RiskAssessmentModel(RiskAssessmentFactory *factory);
    virtual ~RiskAssessmentModel();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual void add(int beforeIndex);
    virtual void remove(int index);

private:
    RiskAssessmentFactory *factory;
    QVector<RiskAssessment*> assessments;
};

#endif // RISKASSESSMENTMODEL_H
