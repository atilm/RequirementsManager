#ifndef RISKMODEL_H
#define RISKMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class RiskModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RiskModel(QObject *parent = 0);
    virtual ~RiskModel();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

signals:

public slots:

private:
    QStringList probabilities;
    QStringList damageExtents;
    QStringList resultingRisks;

    int resultingRisk(int probability, int damageExtent) const;
    void initTable();
};

#endif // RISKMODEL_H