#ifndef LINKCONTEXT_H
#define LINKCONTEXT_H

#include <QAbstractListModel>
#include <QVector>

class LinkContext : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LinkContext(QObject *parent = 0);
    virtual ~LinkContext();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual void addLinkType(const QString &name);
    virtual void removeLinkType(const QModelIndex &index);
    virtual void renameLinkType(const QModelIndex &index, const QString &newName);

signals:

public slots:

private:
    QVector<QString> linkTypes;
};

#endif // LINKCONTEXT_H
