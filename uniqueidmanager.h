#ifndef UNIQUEIDMANAGER_H
#define UNIQUEIDMANAGER_H

#include <exception>
using namespace std;

class IDCollisionException : public exception{

};

class UniqueIDManager
{
public:
    UniqueIDManager();
    virtual ~UniqueIDManager();

    bool hasID(unsigned int id) const;
    void addID(unsigned int id);
    unsigned int newUniqueID();

};

#endif // UNIQUEIDMANAGER_H
