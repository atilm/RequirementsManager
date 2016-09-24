#include "uniqueidmanager.h"
#include <QDebug>

UniqueIDManager::UniqueIDManager(QObject *parent)
    : QObject(parent)
{
    maxID = 0;
}

UniqueIDManager::~UniqueIDManager()
{

}

void UniqueIDManager::reset()
{
    // UniqueIDManager still contains the requirement
    // model's root requirement.

    if(ids.count() != 1){
        throw IDNotRemovedException();
    }

    maxID = 1;
}

bool UniqueIDManager::hasID(unsigned int id) const
{
    return ids.contains(id);
}

void UniqueIDManager::removeID(unsigned int id)
{
    if(ids.contains(id)){
        ids.remove(id);
        emit idRemoved(id);
    }
    else
        throw IDUnknownException();
}

unsigned int UniqueIDManager::newUniqueID()
{
    maxID += 1;
    ids.insert(maxID, nullptr);
    return maxID;
}

unsigned int UniqueIDManager::newUniqueID(unsigned int requestedId)
{
    if(!ids.contains(requestedId)){
        ids.insert(requestedId, nullptr);
        updateMax(requestedId);
        return requestedId;
    }
    else
        throw IDCollisionException();
}

void UniqueIDManager::setRequirement(unsigned int id, Requirement *req)
{
    if(ids.contains(id))
        ids[id] = req;
    else
        throw IDUnknownException();
}

Requirement *UniqueIDManager::getRequirement(unsigned int id) const
{
    if(ids.contains(id))
        return ids[id];
    else
        throw IDUnknownException();
}

void UniqueIDManager::updateMax(unsigned int id)
{
    if(id >= maxID)
        maxID = id;
}
