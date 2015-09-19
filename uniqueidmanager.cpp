#include "uniqueidmanager.h"

UniqueIDManager::UniqueIDManager()
{
    maxID = 0;
}

UniqueIDManager::~UniqueIDManager()
{

}

bool UniqueIDManager::hasID(unsigned int id) const
{
    return ids.contains(id);
}

void UniqueIDManager::removeID(unsigned int id)
{
    if(ids.contains(id))
        ids.remove(id);
    else
        throw IDCollisionException();
}

unsigned int UniqueIDManager::newUniqueID()
{
    maxID += 1;
    ids.insert(maxID);
    return maxID;
}

unsigned int UniqueIDManager::newUniqueID(unsigned int requestedId)
{
    if(!ids.contains(requestedId)){
        ids.insert(requestedId);
        updateMax(requestedId);
        return requestedId;
    }
    else
        throw IDCollisionException();
}

void UniqueIDManager::updateMax(unsigned int id)
{
    if(id >= maxID)
        maxID = id;
}
