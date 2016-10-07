#include <QDebug>

#include "requirementsmodeliterator.h"

RequirementsModelIterator::
RequirementsModelIterator(shared_ptr<RequirementsModel> model)
{
    this->model = model;
    toBegin();
}

void RequirementsModelIterator::toBegin()
{
    previousIndex = QModelIndex();
    currentIndex = QModelIndex();
    previousDepth = 0;
    currentDepth = 0;

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
    if(currentIndex.isValid()){
        previousIndex = currentIndex;

        if(currentNodeHasChildNodes()){
            goToFirstChild();
        }
        else{
            while(!currentHasNextSibling() && currentIndex.isValid()){
                goToParent();
            }
            goToNextSibling();
        }

        return currentIndex.isValid();
    }
    else{
        return false;
    }
}

bool RequirementsModelIterator::previous()
{
    currentDepth = previousDepth;
    currentIndex = previousIndex;
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

int RequirementsModelIterator::getCurrentDepth()
{
    return currentDepth;
}

bool RequirementsModelIterator::currentNodeHasChildNodes()
{
    return ( model->rowCount(currentIndex) > 0 );
}

void RequirementsModelIterator::goToFirstChild()
{
    currentIndex = model->index(0, 0, currentIndex);
    increaseDepth();
}

void RequirementsModelIterator::goToParent()
{
    currentIndex = currentIndex.parent();
    decreaseDepth();
}

bool RequirementsModelIterator::currentHasNextSibling()
{
    QModelIndex parent = currentIndex.parent();

    if(currentIndex.isValid()){
        int siblingCount = model->rowCount(parent);
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

void RequirementsModelIterator::increaseDepth()
{
    previousDepth = currentDepth;
    currentDepth++;
}

void RequirementsModelIterator::decreaseDepth()
{
    previousDepth = currentDepth;
    currentDepth--;
}
