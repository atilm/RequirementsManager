#include "requirementsmodeliterator.h"

RequirementsModelIterator::RequirementsModelIterator(RequirementsModel *model)
{
    this->model = model;
    toBegin();
}

void RequirementsModelIterator::toBegin()
{
    currentIndex = QModelIndex();

    if(currentNodeHasChildNodes()){
        goToFirstChild();
    }
}

bool RequirementsModelIterator::hasNext()
{
    QModelIndex previous = currentIndex;

    if(next()){
        currentIndex = previous;
        return true;
    }
    else{
        return false;
    }
}

bool RequirementsModelIterator::next()
{
    if(currentIndex.isValid())
    {
        if(currentNodeHasChildNodes())
        {
            goToFirstChild();
        }
        else
        {
            while(!currentHasNextSibling() && currentIndex.isValid())
            {
                goToParent();
            }
            goToNextSibling();
        }

        if(currentIndex.isValid())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

Requirement *RequirementsModelIterator::currentRequirement()
{
    if(!currentIndex.isValid()){
        return nullptr;
    }
    else{
        return model->getRequirement(currentIndex);
    }
}

bool RequirementsModelIterator::currentNodeHasChildNodes()
{
    return ( model->getRequirement(currentIndex)->childCount() > 0 );
}

void RequirementsModelIterator::goToFirstChild()
{
    currentIndex = model->index(0, 0, currentIndex);
}

void RequirementsModelIterator::goToParent()
{
    currentIndex = currentIndex.parent();
}

bool RequirementsModelIterator::currentHasNextSibling()
{
    QModelIndex parent = currentIndex.parent();

    if(parent.isValid()){
        int siblingCount = model->getRequirement(parent)->childCount();
        return currentIndex.row() + 1 < siblingCount;
    }
    else{
        return false;
    }
}

void RequirementsModelIterator::goToNextSibling()
{
    if(currentHasNextSibling()){
        QModelIndex parent = currentIndex.parent();
        currentIndex = model->index(currentIndex.row()+1, 0, parent);
    }
    else{
        currentIndex = QModelIndex();
    }
}
