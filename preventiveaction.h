#ifndef PREVENTIVEACTION_H
#define PREVENTIVEACTION_H

#include <QString>

class PreventiveAction
{
public:
    PreventiveAction();
    virtual ~PreventiveAction();

    virtual QString getShortAction() const;
};

#endif // PREVENTIVEACTION_H
