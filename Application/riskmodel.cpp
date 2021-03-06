#include "riskmodel.h"
#include <QColor>

RiskModel::RiskModel(shared_ptr<FileStateTracker> fileState, QObject *parent) :
    QAbstractTableModel(parent)
{
    initTable();
    this->fileState = fileState;
    currentRisk = index(3,3);
}

RiskModel::~RiskModel()
{

}

QVariant RiskModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal)
            return probabilities[section];
        else
            return damageExtents[section];
    }

    return QVariant();
}

int RiskModel::rowCount(const QModelIndex &parent) const
{
    return damageExtents.count();
}

int RiskModel::columnCount(const QModelIndex &parent) const
{
    return probabilities.count();
}

QVariant RiskModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int risk = resultingRisk(index.column(), index.row());

    if(role == Qt::DisplayRole){
        return resultingRisks[risk];
    }
    else if(role == Qt::BackgroundRole){
        switch(risk){
        case 0:
            return QColor(Qt::green);
        case 1:
            return QColor(Qt::yellow);
        case 2:
            return QColor(Qt::red);
        }
    }

    return QVariant();
}

void RiskModel::setCurrentRisk(const QModelIndex &index)
{
    if(index != currentRisk){
        currentRisk = index;
        fileState->setChanged(true);
    }
}

QModelIndex RiskModel::getCurrentRisk() const
{
    return currentRisk;
}

QString RiskModel::damageExtent() const
{
    return damageExtents[currentRisk.row()];
}

QString RiskModel::probability() const
{
    return probabilities[currentRisk.column()];
}

int RiskModel::resultingRisk(int probability, int damageExtent) const
{
    int riskIndex = (probability+1) * (damageExtent+1);

    if(riskIndex < 4 && damageExtent < 2)
        return 0;
    else if(riskIndex > 9 || (riskIndex == 8 && damageExtent > 2))
        return 2;
    else
        return 1;
}

void RiskModel::initTable()
{
    probabilities.append(tr("Unthinkable"));
    probabilities.append(tr("Low"));
    probabilities.append(tr("Middle"));
    probabilities.append(tr("High"));

    damageExtents.append(tr("Marginal"));
    damageExtents.append(tr("Low"));
    damageExtents.append(tr("Middle"));
    damageExtents.append(tr("High"));

    resultingRisks.append(tr("Acceptable"));
    resultingRisks.append(tr("Reasonable"));
    resultingRisks.append(tr("Unacceptable"));
}
