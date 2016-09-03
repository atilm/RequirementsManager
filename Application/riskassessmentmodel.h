#ifndef RISKASSESSMENTMODEL_H
#define RISKASSESSMENTMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "riskassessmentfactory.h"
#include "riskassessment.h"
#include "preventiveactionmodel.h"
#include "filestatetracker.h"

class RiskAssessmentModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    RiskAssessmentModel(shared_ptr<FileStateTracker> fileState,
                        shared_ptr<RiskAssessmentFactory> factory);
    virtual ~RiskAssessmentModel();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual shared_ptr<RiskAssessment> appendAssessment();
    virtual void add(int beforeRowIndex);
    virtual void remove(const QModelIndex &index);

    virtual shared_ptr<RiskAssessment>  getRiskAssessment(const QModelIndex &index);

    virtual shared_ptr<PreventiveActionModel> getPreventiveActions(const QModelIndex &index);

private slots:
    void handleTestModelChanged();

private:
    shared_ptr<FileStateTracker> fileState;
    shared_ptr<RiskAssessmentFactory> factory;
    QVector<shared_ptr<RiskAssessment>> assessments;

};

#endif // RISKASSESSMENTMODEL_H
