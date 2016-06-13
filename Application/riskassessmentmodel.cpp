#include "riskassessmentmodel.h"
#include <stdexcept>
using namespace std;

RiskAssessmentModel::RiskAssessmentModel(FileStateTracker *fileState,
                                         RiskAssessmentFactory *factory)
{
    this->fileState = fileState;
    this->factory = factory;
}

RiskAssessmentModel::~RiskAssessmentModel()
{
    delete factory;

    foreach(RiskAssessment *ra, assessments)
        delete ra;
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
    if(index.isValid()){
        RiskAssessment *a = assessments[index.row()];

        switch(index.column()){
        case 0:
            if(role == Qt::DisplayRole)
                return a->shortScenario();
            break;
        case 1:
            return a->initialRisk(role);
        case 2:
            return a->finalRisk(role);
        }
    }

    return QVariant();
}

RiskAssessment *RiskAssessmentModel::appendAssessment()
{
    add(rowCount());
    return getRiskAssessment(index(rowCount()-1,0));
}

void RiskAssessmentModel::add(int beforeRowIndex)
{
    int beforeRow = 0;

    if(beforeRowIndex >= 0 && beforeRowIndex <= rowCount())
        beforeRow = beforeRowIndex;

    beginInsertRows(QModelIndex(), beforeRow, beforeRow);
    assessments.insert(beforeRow, factory->newAssessment());
    endInsertRows();
    fileState->setChanged(true);
}

void RiskAssessmentModel::remove(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    assessments.remove(index.row());
    endRemoveRows();
    fileState->setChanged(true);
}

RiskAssessment *RiskAssessmentModel::getRiskAssessment(const QModelIndex &index)
{
    if(!index.isValid())
        throw runtime_error("Invalid risk assessment index");

    return assessments[index.row()];
}

PreventiveActionModel *RiskAssessmentModel::getPreventiveActions(const QModelIndex &index)
{
    if(!index.isValid())
        throw runtime_error("Invalid risk assessment index");

    return assessments[index.row()]->getPreventiveActions();
}

