#ifndef UNIQUEIDMANAGER_H
#define UNIQUEIDMANAGER_H

#include <QObject>

#include <QHash>
#include <exception>
using namespace std;

class Requirement;

class IDCollisionException : public exception{

};

class IDUnknownException : public exception{

};

class UniqueIDManager : public QObject
{
    Q_OBJECT
public:
    UniqueIDManager(QObject *parent = 0);
    virtual ~UniqueIDManager();

    /*! Check if an id exists
     Returns true, if the given id exists.
     Returns false otherwise.
     */
    virtual bool hasID(unsigned int id) const;
    virtual void removeID(unsigned int id);
    virtual unsigned int newUniqueID();
    virtual unsigned int newUniqueID(unsigned int requestedId);
    virtual void setRequirement(unsigned int id, Requirement *req);
    virtual Requirement* getRequirement(unsigned int id) const;

signals:
    void idRemoved(unsigned int id);

private:
    QHash<unsigned int, Requirement*> ids;
    unsigned int maxID;

    void updateMax(unsigned int id);
};

#endif // UNIQUEIDMANAGER_H
