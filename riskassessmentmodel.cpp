#include "riskassessmentmodel.h"

RiskAssessmentModel::RiskAssessmentModel(RiskAssessmentFactory *factory)
{
    this->factory = factory;
}

RiskAssessmentModel::~RiskAssessmentModel()
{
    delete factory;
}

QVariant RiskAssessmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        if(section == 0)
            return tr("Scenario");
        else if(section == 1)
            return tr("Initial Risk");
        else if(section == 2)
            return tr("Final Risk");
    }

    return QVariant();
}

int RiskAssessmentModel::rowCount(const QModelIndex &parent) const
{
    return assessments.count();
}

int RiskAssessmentModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant RiskAssessmentModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole){
        RiskAssessment *a = assessments[index.row()];

        switch(index.column()){
        case 0:
            return a->shortScenario();
        case 1:
            return a->initialRisk();
        case 2:
            return a->finalRisk();
        }
    }

    return QVariant();
}

void RiskAssessmentModel::add(int beforeIndex)
{
    if(beforeIndex < 0 || beforeIndex > assessments.count())
        return;

    beginInsertRows(QModelIndex(), beforeIndex, beforeIndex);
    assessments.insert(beforeIndex, factory->newAssessment());
    endInsertRows();
}

void RiskAssessmentModel::remove(int index)
{
    if(index < 0 || index >= assessments.count())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    assessments.remove(index);
    endRemoveRows();
}
