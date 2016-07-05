#include "gtest/gtest.h"
#include "requirement.h"
#include "riskassessmentmodelmock.h"
#include "attributecontainermock.h"
#include "linkcontainermock.h"
#include <iostream>
#include <random>
#include <QDebug>
using namespace std;

class RequirementTests : public ::testing::Test{
protected:
    std::random_device rd;
    std::mt19937 rng;
    UniqueIDManager *idManager;
    shared_ptr<RiskAssessmentModelMock> riskAssessmentModelMock;
    AttributeContainerMock *attributesMock;
    LinkContainerMock *linksMock;

    RequirementTests(){
        rng = std::mt19937(rd());
        idManager = new UniqueIDManager();
        riskAssessmentModelMock = shared_ptr<RiskAssessmentModelMock>(new RiskAssessmentModelMock());
        attributesMock = new AttributeContainerMock();
        linksMock = new LinkContainerMock();
    }

    virtual ~RequirementTests(){
        delete idManager;
    }

    uint getRandomID(){
        std::uniform_int_distribution<uint> dist(0,1000);
        return dist(rng);
    }

    Requirement *newRequirement(unsigned int proposedID = -1){
        if(proposedID == -1)
            return new Requirement(idManager, riskAssessmentModelMock,
                                   attributesMock, linksMock);
        else{
            return new Requirement(idManager, riskAssessmentModelMock,
                                   attributesMock, linksMock,
                                   proposedID);
        }
    }
};

TEST_F(RequirementTests, when_deleted_a_requirement_unregisters_its_id){
    uint id = getRandomID();

    Requirement *item = newRequirement(id);

    EXPECT_TRUE(idManager->hasID(id));

    delete item;

    EXPECT_FALSE(idManager->hasID(id));
}

TEST_F(RequirementTests, when_inserting_a_child_an_item_sets_itself_as_parent){
    Requirement *parent = newRequirement();
    Requirement *child = new Requirement(idManager,
                                         shared_ptr<RiskAssessmentModelMock>(new RiskAssessmentModelMock()),
                                         new AttributeContainerMock(),
                                         new LinkContainerMock());

    parent->appendChild(child);

    EXPECT_EQ(parent, child->getParent());

    delete parent;
}

TEST_F(RequirementTests, item_returns_its_given_id){
    uint id = getRandomID();

    Requirement *item = newRequirement(id);

    EXPECT_EQ(id, item->getID());
}
