#ifndef SOURCECODEMODEL_H
#define SOURCECODEMODEL_H

#include <QAbstractItemModel>

#include "sourcenode.h"

class TestNode;

struct SourceAddress
{
    QString className;
    QString functionName;
    QString testCase;
    QString testName;
};

class SourceCodeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    SourceCodeModel();
    virtual ~SourceCodeModel();

    // required overriden functions
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QModelIndex	index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex &index) const;

    // additional overriden functions
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QModelIndex insertClassAlphabetically(SourceNode *node);
    virtual QModelIndex insertFunctionAlphabetically(const QModelIndex &classIndex,
                                                     SourceNode *functionNode);
    virtual QModelIndex appendClass(SourceNode *node);
    virtual QModelIndex appendFunction(const QModelIndex &classIndex,
                                       SourceNode *functionNode);
    virtual void appendTest(SourceAddress address,
                            SourceNode *testNode);
    virtual void insertTestIntoClass(const QModelIndex &classIndex,
                                     SourceAddress address,
                                     SourceNode *testNode);
    virtual void insertTestIntoFunction(const QModelIndex &functionIndex,
                                        SourceNode *testNode);

    virtual QString getDescription(const QModelIndex &index) const;
    virtual QString getDescription(SourceAddress address) const;
    virtual TestNode* getTestNode(const QModelIndex &index) const;
    virtual TestNode* getTestNode(SourceAddress address) const;
    virtual SourceAddress getAddress(const QModelIndex &index) const;

private:
    SourceNode *root;

    SourceNode *asSourceNode(const QModelIndex &index) const;
    SourceNode *getValidItem(const QModelIndex &index) const;
    QModelIndex indexOf(SourceAddress address) const;
    QModelIndex functionIndex(const QModelIndex &classIndex,
                              SourceAddress address) const;
    QModelIndex testIndex(const QModelIndex &functionIndex,
                          SourceAddress address) const;
    int getAlphabeticalInsertionIndex(SourceNode *parent,
                                      SourceNode *node);
};

#endif // SOURCECODEMODEL_H
