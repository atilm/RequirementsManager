#include "gtest/gtest.h"
#include "requirement.h"
#include <iostream>
#include <random>
using namespace std;

class RequirementTests : public ::testing::Test{
protected:
    std::random_device rd;
    std::mt19937 rng;
    UniqueIDManager *idManager;

    RequirementTests(){
        rng = std::mt19937(rd());
        idManager = new UniqueIDManager();
    }

    virtual ~RequirementTests(){
        delete idManager;
    }

    uint getRandomID(){
        std::uniform_int_distribution<uint> dist(0,1000);
        return dist(rng);
    }
};

TEST_F(RequirementTests, when_deleted_a_requirement_unregisters_its_id){
    uint id = getRandomID();

    Requirement *item = new Requirement(idManager, id);

    EXPECT_TRUE(idManager->hasID(id));

    delete item;

    EXPECT_FALSE(idManager->hasID(id));
}

TEST_F(RequirementTests, when_inserting_a_child_an_item_sets_itself_as_parent){
    Requirement *parent = new Requirement(idManager);
    Requirement *child = new Requirement(idManager);

    parent->appendChild(child);

    EXPECT_EQ(parent, child->getParent());

    delete parent;
}

TEST_F(RequirementTests, item_returns_its_given_id){
    uint id = getRandomID();

    Requirement *item = new Requirement(idManager, id);

    EXPECT_EQ(id, item->getID());
}
