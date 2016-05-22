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

    virtual void clear();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual QString typeName(int index) const;
    virtual void addLinkType(const QString &name);
    virtual void removeLinkType(const QModelIndex &index);
    virtual void renameLinkType(const QModelIndex &index, const QString &newName);

signals:
    void newLinkType(int beforeIndex);
    void linkTypeRemoved(int index);

public slots:

private:
    QVector<QString> linkTypes;

    bool isValidIndex(int index) const;
};

#endif // LINKCONTEXT_H
