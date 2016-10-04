#ifndef REQUIREMENTSMODELITERATOR_H
#define REQUIREMENTSMODELITERATOR_H

#include "requirementsmodel.h"

class RequirementsModelIterator
{
public:
    RequirementsModelIterator(RequirementsModel *model);

    void toBegin();
    bool hasNext();
    bool next();
    Requirement* currentRequirement();

private:
    RequirementsModel *model;
    QModelIndex currentIndex;

    bool currentNodeHasChildNodes();
    void goToFirstChild();
    void goToParent();
    bool currentHasNextSibling();
    void goToNextSibling();
};

#endif // REQUIREMENTSMODELITERATOR_H
