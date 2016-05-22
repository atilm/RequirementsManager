#ifndef RISKMODEL_H
#define RISKMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include "filestatetracker.h"

class RiskModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RiskModel(FileStateTracker *fileState, QObject *parent = 0);
    virtual ~RiskModel();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual void setCurrentRisk(const QModelIndex &index);
    virtual QModelIndex getCurrentRisk() const;
    virtual QString damageExtent() const;
    virtual QString probability() const;

signals:

public slots:

private:
    FileStateTracker *fileState;
    QModelIndex currentRisk;
    QStringList probabilities;
    QStringList damageExtents;
    QStringList resultingRisks;

    int resultingRisk(int probability, int damageExtent) const;
    void initTable();
};

#endif // RISKMODEL_H
