#ifndef UNIQUEIDMANAGER_H
#define UNIQUEIDMANAGER_H

#include <QHash>
#include <exception>
using namespace std;

class Requirement;

class IDCollisionException : public exception{

};

class IDUnknownException : public exception{

};

class UniqueIDManager
{
public:
    UniqueIDManager();
    virtual ~UniqueIDManager();

    virtual bool hasID(unsigned int id) const;
    virtual void removeID(unsigned int id);
    virtual unsigned int newUniqueID();
    virtual unsigned int newUniqueID(unsigned int requestedId);
    virtual void setRequirement(unsigned int id, Requirement *req);
    virtual Requirement* getRequirement(unsigned int id) const;

private:
    QHash<unsigned int, Requirement*> ids;
    unsigned int maxID;

    void updateMax(unsigned int id);
};

#endif // UNIQUEIDMANAGER_H
