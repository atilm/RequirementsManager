#ifndef ATTRIBUTECONTEXT_H
#define ATTRIBUTECONTEXT_H

#include <QObject>
#include <QMap>

class AttributeContext : public QObject
{
    Q_OBJECT
public:

    enum DataType{
        BOOLEAN,
        INTEGER,
        TEXT
    };

    AttributeContext();
    virtual ~AttributeContext();

    virtual void addAttribute(const QString &name, DataType type);
    virtual void removeAttribute(const QString &name);
    virtual int count() const;
    virtual QList<QString> names() const;
    virtual DataType type(const QString &name) const;
    virtual QString typeString(const QString &name) const;

signals:
    void newAttribute(const QString &name, DataType type);
    void removedAttribute(const QString &name);

private:
    QMap<QString,DataType> attributes;
};

#endif // ATTRIBUTECONTEXT_H
