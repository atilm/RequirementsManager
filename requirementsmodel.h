#ifndef REQUIREMENTSMODEL_H
#define REQUIREMENTSMODEL_H

#include <QAbstractItemModel>

class RequirementsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit RequirementsModel(QObject *parent = 0);

    // required overriden functions
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex & index) const;

    // additional overriden functions
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
    virtual bool insertColumns(int column, int count, const QModelIndex & parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
    virtual bool removeColumns(int column, int count, const QModelIndex & parent = QModelIndex());
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

signals:

public slots:

};

#endif // REQUIREMENTSMODEL_H
