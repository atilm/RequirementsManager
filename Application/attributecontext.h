#ifndef ATTRIBUTECONTEXT_H
#define ATTRIBUTECONTEXT_H

#include <QAbstractTableModel>
#include <QVector>
#include "filestatetracker.h"

class AttributeContext : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum DataType{
        BOOLEAN,
        TEXT,
        INVALID
    };

    struct Attribute{
        QString name;
        DataType type;
    };

    AttributeContext(FileStateTracker *fileState);
    virtual ~AttributeContext();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual void clear();
    virtual void addAttribute(const QString &name, DataType type);
    virtual void addAttribute(const QString &name, const QString &typeString);
    virtual void removeAttribute(int row);
    virtual QString name(int index) const;
    virtual DataType type(int index) const;
    virtual QString typeString(int index) const;
    virtual QString typeString(DataType type) const;

signals:
    void newAttribute(int beforeIndex);
    void removedAttribute(int index);
    void attributeAboutToBeInserted(int index);
    void attributeInserted();
    void attributeAboutToBeRemoved(int index);
    void attributeRemoved();

private:
    FileStateTracker *fileState;
    QString booleanTypeString;
    QString textTypeString;
    QVector<Attribute> attributes;

    DataType stringToDataType(const QString &typeString);
};

#endif // ATTRIBUTECONTEXT_H
