#ifndef REQUIREMENTREFCOUNTER_H
#define REQUIREMENTREFCOUNTER_H

#include <QList>
#include <QMap>
#include <QSet>

#include "uniqueidmanager.h"

class Requirement;
class RequirementReference;

class RequirementRefCounter
{
public:
    RequirementRefCounter();
    virtual ~RequirementRefCounter();

    void reset();

    void addReference(uint reqIdx, uint refIdx);
    void removeReference(uint reqIdx, uint refIdx);

    QSet<uint> getReferences(uint reqId) const;

private:
    QMap<uint, QSet<uint>> linkMap;
};

#endif // REQUIREMENTREFCOUNTER_H
