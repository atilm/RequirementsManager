#ifndef UNIQUEIDMANAGER_H
#define UNIQUEIDMANAGER_H

#include <QSet>
#include <exception>
using namespace std;

class IDCollisionException : public exception{

};

class UniqueIDManager
{
public:
    UniqueIDManager();
    virtual ~UniqueIDManager();

    virtual bool hasID(unsigned int id) const;
    virtual void removeID(unsigned int id);
    unsigned int newUniqueID();
    unsigned int newUniqueID(unsigned int requestedId);

private:
    QSet<unsigned int> ids;
    unsigned int maxID;

    void updateMax(unsigned int id);
};

#endif // UNIQUEIDMANAGER_H
