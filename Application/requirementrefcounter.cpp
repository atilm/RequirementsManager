#include "requirementrefcounter.h"

#include "requirement.h"
#include "requirementreference.h"

#include <QDebug>

RequirementRefCounter::RequirementRefCounter()
{
}

RequirementRefCounter::~RequirementRefCounter()
{

}

void RequirementRefCounter::reset()
{
    linkMap.clear();
}

void RequirementRefCounter::addReference(uint reqIdx, uint refIdx)
{
    linkMap[reqIdx].insert(refIdx);
}

void RequirementRefCounter::removeReference(uint reqIdx, uint refIdx)
{
    if(linkMap.contains(reqIdx))
    {
        linkMap[reqIdx].remove(refIdx);
    }
}

QSet<uint> RequirementRefCounter::getReferences(uint reqId) const
{
    if(linkMap.contains(reqId))
    {
        return linkMap[reqId];
    }
    else
    {
        throw runtime_error("RequirementRefCounter::getReferences(): unknown sourceId");
    }
}
