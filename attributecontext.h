#ifndef ATTRIBUTECONTEXT_H
#define ATTRIBUTECONTEXT_H

#include <QAbstractTableModel>
#include <QVector>

class AttributeContext : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum DataType{
        BOOLEAN,
        INTEGER,
        TEXT
    };

    struct Attribute{
        QString name;
        DataType type;
    };

    AttributeContext();
    virtual ~AttributeContext();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual void addAttribute(const QString &name, DataType type);
    virtual void removeAttribute(int row);
    virtual QList<QString> names() const;
    virtual DataType type(const QString &name) const;
    virtual QString typeString(const QString &name) const;
    virtual QString typeString(DataType type) const;

signals:
    void newAttribute(const QString &name, DataType type);
    void removedAttribute(const QString &name);

private:
    QVector<Attribute> attributes;
};

#endif // ATTRIBUTECONTEXT_H
