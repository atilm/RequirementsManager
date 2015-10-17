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

void RiskAssessmentModel::add(const QModelIndex &beforeIndex)
{
    int beforeRow = 0;

    if(beforeIndex.isValid())
        beforeRow = beforeIndex.row();

    beginInsertRows(QModelIndex(), beforeRow, beforeRow);
    assessments.insert(beforeRow, factory->newAssessment());
    endInsertRows();
}

void RiskAssessmentModel::remove(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    assessments.remove(index.row());
    endRemoveRows();
}
