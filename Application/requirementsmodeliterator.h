#ifndef REQUIREMENTSMODELITERATOR_H
#define REQUIREMENTSMODELITERATOR_H

#include "requirementsmodel.h"

class RequirementsModelIterator
{
public:
    RequirementsModelIterator(shared_ptr<RequirementsModel> model);

    void toBegin();
    bool hasNext();
    bool next();
    bool previous();
    Requirement* currentRequirement();
    int getCurrentDepth();

private:
    shared_ptr<RequirementsModel> model;
    QModelIndex previousIndex;
    QModelIndex currentIndex;
    int previousDepth;
    int currentDepth;

    bool currentNodeHasChildNodes();
    void goToFirstChild();
    void goToParent();
    bool currentHasNextSibling();
    void goToNextSibling();
    void increaseDepth();
    void decreaseDepth();
};

#endif // REQUIREMENTSMODELITERATOR_H
