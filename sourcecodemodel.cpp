#include "sourcecodemodel.h"
#include <QDebug>

SourceCodeModel::SourceCodeModel()
{
    root = new SourceNode();
}

SourceCodeModel::~SourceCodeModel()
{

}

int SourceCodeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int SourceCodeModel::rowCount(const QModelIndex &parent) const
{
    return getValidItem(parent)->childCount();
}

QVariant SourceCodeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
        return asSourceNode(index)->getName();
    else
        return QVariant();
}

QModelIndex SourceCodeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    try{
        SourceNode *parentItem = getValidItem(parent);
        SourceNode *childItem = parentItem->getChild(row);

        return createIndex(row, column, childItem);
    }
    catch(...){
        return QModelIndex();
    }
}

QModelIndex SourceCodeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
        return QModelIndex();

    SourceNode *childItem = asSourceNode(index);
    SourceNode *parentItem = childItem->getParent();

    if(parentItem == nullptr || parentItem == root)
        return QModelIndex();
    else
        return createIndex(parentItem->getRow(), 0, parentItem);
}

QVariant SourceCodeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

Qt::ItemFlags SourceCodeModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex SourceCodeModel::appendClass(SourceNode *node)
{
    int rowIdx = root->childCount();

    beginInsertRows(QModelIndex(), rowIdx, rowIdx);
    root->appendChild(node);
    endInsertRows();

    return index(rowIdx, 0);
}

QModelIndex SourceCodeModel::appendFunction(const QModelIndex &classIndex,
                                            SourceNode *functionNode)
{
    SourceNode *classNode = asSourceNode(classIndex);
    int rowIdx = classNode->childCount();

    beginInsertRows(classIndex, rowIdx, rowIdx);
    classNode->appendChild(functionNode);
    endInsertRows();

    return index(rowIdx, 0, classIndex);
}

void SourceCodeModel::appendTest(SourceAddress address, SourceNode *testNode)
{   
    for(int c=0;c < root->childCount(); c++){
        SourceNode *classNode = root->getChild(c);

        if(address.className == classNode->getName()){
            insertTestIntoClass(index(c, 0), address, testNode);
            return;
        }
    }

    orphanTests.append(testNode);
}

void SourceCodeModel::insertTestIntoClass(const QModelIndex &classIndex,
                                          SourceAddress address,
                                          SourceNode *testNode)
{
    SourceNode *classNode = asSourceNode(classIndex);

    for(int f=0;f < classNode->childCount(); f++){
        SourceNode *functionNode = classNode->getChild(f);

        if(address.functionName == functionNode->getName()){
            insertTestIntoFunction(index(f, 0, classIndex), testNode);
            return;
        }
    }

    orphanTests.append(testNode);
}

void SourceCodeModel::insertTestIntoFunction(const QModelIndex &functionIndex,
                                             SourceNode *testNode)
{
    SourceNode *functionNode = asSourceNode(functionIndex);
    int rowIdx = functionNode->childCount();

    beginInsertRows(functionIndex, rowIdx, rowIdx);
    functionNode->appendChild(testNode);
    endInsertRows();
}

QString SourceCodeModel::getDescription(const QModelIndex &index) const
{
    if(!index.isValid())
        return QString();
    else
        return asSourceNode(index)->getDescription();
}

QString SourceCodeModel::getDescription(SourceAddress address) const
{
    QModelIndex index = indexOf(address);

    if(index.isValid())
        return getDescription(index);
    else
        return QString("Unresolved reference to source code element.");
}

SourceAddress SourceCodeModel::getAddress(const QModelIndex &index) const
{
    SourceNode *node = getValidItem(index);

    QStringList fields;

    while(node->getParent()){
        fields.push_back(node->getName());
        node = node->getParent();
    }

    SourceAddress address;

    if(!fields.isEmpty()){
        address.className = fields.last();
        fields.pop_back();
    }

    if(!fields.isEmpty()){
        address.functionName = fields.last();
        fields.pop_back();
    }

    return address;
}

SourceNode *SourceCodeModel::asSourceNode(const QModelIndex &index) const
{
    return static_cast<SourceNode*>(index.internalPointer());
}

SourceNode *SourceCodeModel::getValidItem(const QModelIndex &index) const
{
    if(!index.isValid())
        return root;
    else
        return asSourceNode(index);
}

QModelIndex SourceCodeModel::indexOf(SourceAddress address) const
{
    for(int c=0;c < root->childCount(); c++){
        SourceNode *classNode = root->getChild(c);

        if(address.className == classNode->getName()){

            if(address.functionName.isEmpty())
                return index(c, 0);
            else
                return functionIndex(index(c,0), address);
        }
    }
}

QModelIndex SourceCodeModel::functionIndex(const QModelIndex &classIndex,
                                           SourceAddress address) const
{
    SourceNode *classNode = asSourceNode(classIndex);

    for(int f=0;f < classNode->childCount(); f++){
        SourceNode *functionNode = classNode->getChild(f);

        if(address.functionName == functionNode->getName())
            return index(f, 0, classIndex);
    }

    return QModelIndex();
}

