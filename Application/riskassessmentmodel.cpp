#include "riskassessmentmodel.h"
#include <stdexcept>
using namespace std;

RiskAssessmentModel::RiskAssessmentModel(shared_ptr<FileStateTracker> fileState,
                                         shared_ptr<RiskAssessmentFactory> factory)
{
    this->fileState = fileState;
    this->factory = factory;
}

RiskAssessmentModel::~RiskAssessmentModel()
{
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
        else if(section == 3)
            return tr("Tests");
    }

    return QVariant();
}

int RiskAssessmentModel::rowCount(const QModelIndex &parent) const
{
    return assessments.count();
}

int RiskAssessmentModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant RiskAssessmentModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()){
        shared_ptr<RiskAssessment> a = assessments[index.row()];

        switch(index.column()){
        case 0:
            if(role == Qt::DisplayRole)
                return a->shortScenario();
            break;
        case 1:
            return a->initialRisk(role);
        case 2:
            return a->finalRisk(role);
        case 3:
            if(role == Qt::DisplayRole)
                return a->preventiveActionCount();
            break;
        }
    }

    return QVariant();
}

shared_ptr<RiskAssessment> RiskAssessmentModel::appendAssessment()
{
    add(rowCount());
    return getRiskAssessment(index(rowCount()-1,0));
}

void RiskAssessmentModel::add(int beforeRowIndex)
{
    int beforeRow = 0;

    if(beforeRowIndex >= 0 && beforeRowIndex <= rowCount())
        beforeRow = beforeRowIndex;

    shared_ptr<RiskAssessment> assessment = factory->newAssessment();
    connect(assessment->getPreventiveActions().get(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            this, SLOT(handleTestModelChanged()));
    connect(assessment->getPreventiveActions().get(), SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this, SLOT(handleTestModelChanged()));

    beginInsertRows(QModelIndex(), beforeRow, beforeRow);
    assessments.insert(beforeRow, assessment);
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

shared_ptr<RiskAssessment> RiskAssessmentModel::getRiskAssessment(const QModelIndex &index)
{
    if(!index.isValid())
        throw runtime_error("Invalid risk assessment index");

    return assessments[index.row()];
}

shared_ptr<PreventiveActionModel> RiskAssessmentModel::getPreventiveActions(const QModelIndex &index)
{
    if(!index.isValid())
        throw runtime_error("Invalid risk assessment index");

    return assessments[index.row()]->getPreventiveActions();
}

void RiskAssessmentModel::handleTestModelChanged()
{
    emit dataChanged(index(0, 3), index(rowCount()-1, 3));
}

