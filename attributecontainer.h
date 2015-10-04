#ifndef ATTRIBUTECONTAINER_H
#define ATTRIBUTECONTAINER_H

#include <QVector>
#include <QVariant>
#include "attributecontext.h"

class AttributeContainer : public QObject
{
    Q_OBJECT
public:
    AttributeContainer(AttributeContext *context);
    virtual ~AttributeContainer();

    virtual int count() const;
    virtual void setField(int index, const QVariant &value);
    virtual QVariant getField(int index) const;

private:
    AttributeContext *context;
    QVector<QVariant> attributes;

private slots:
    void attributeAdded(int beforeIndex);
    void attributeRemoved(int index);

};

#endif // ATTRIBUTECONTAINER_H
