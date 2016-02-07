#include "gtest/gtest.h"
#include "uniqueidmanager.h"
#include <random>
#include <QList>

class UniqueIDManagerTests : public ::testing::Test{
protected:
    std::random_device rd;
    std::mt19937 rng;
    QList<uint> unusedIds;
    QList<uint> usedIds;
    UniqueIDManager *manager;

    UniqueIDManagerTests(){
        rng = std::mt19937(rd());
        manager = new UniqueIDManager();

        initialize();
    }

    virtual ~UniqueIDManagerTests(){
        delete manager;
    }

    void initialize(){
        usedIds.clear();
        unusedIds.clear();

        for(uint i=0;i<10000;i++){
            unusedIds.append(i);
        }
    }

    int addUnusedID(){
        if(!unusedIds.empty()){
            std::uniform_int_distribution<int> dist(0,unusedIds.size()-1);
            int index = dist(rng);

            uint id = unusedIds.at(index);

            usedIds.append( manager->newUniqueID(unusedIds.takeAt(index)) );

            return id;
        }
        else
            return -1;
    }

    void addUsedID(){
        if(!usedIds.empty()){
            std::uniform_int_distribution<int> dist(0,usedIds.size()-1);
            int index = dist(rng);

            ASSERT_THROW( manager->newUniqueID( usedIds.at(index)), IDCollisionException);
        }
    }

    void addGeneratedID(){
        if(!unusedIds.empty()){
            uint id = manager->newUniqueID();

            if(unusedIds.contains(id))
                unusedIds.removeOne(id);

            usedIds.append( id );
        }
    }

    void removeUnusedID(){
        if(!unusedIds.empty()){
            std::uniform_int_distribution<int> dist(0,unusedIds.size()-1);
            int index = dist(rng);

            ASSERT_THROW( manager->removeID(unusedIds.at(index)), IDUnknownException);
        }
    }

    void removeUsedID(){
        if(!usedIds.empty()){
            std::uniform_int_distribution<int> dist(0,usedIds.size()-1);
            int index = dist(rng);

            uint id = usedIds[index];

            manager->removeID( usedIds.takeAt(index) );

            unusedIds.append(id);
        }
    }
};

TEST_F(UniqueIDManagerTests, remains_consistent_during_1000_operations){
    std::uniform_int_distribution<int> dist(0,4);

    for(int i=0;i<1000;i++){
        int action = dist(rng);

        switch(action){
        case 0:
            addUnusedID();
            break;
        case 1:
            addUsedID();
            break;
        case 2:
            removeUnusedID();
            break;
        case 3:
            removeUsedID();
            break;
        case 4:
            addGeneratedID();
        }
    }

    for(int i=0;i<usedIds.size();i++){
        ASSERT_TRUE(manager->hasID(usedIds[i]));
    }

    for(int i=0;i<unusedIds.size();i++){
        ASSERT_FALSE(manager->hasID(unusedIds[i]));
    }
}

