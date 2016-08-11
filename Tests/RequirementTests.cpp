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

/*! TEST_SPEC Requirement::getID()
SHORT
When an id has been given to a requirement in the constutor,
exactly this id is returned.

PREPARATION
- Create an object "item" of class Requirement with 11 as id

ACTION
- Call item.getID()

RESULT
- The function returns 11.
*/
TEST_F(RequirementTests, item_returns_its_given_id){
    uint id = 11;

    Requirement *item = newRequirement(id);

    EXPECT_EQ(id, item->getID());
}

class Requirement_getNumberedTitle : public RequirementTests{
protected:
};

/*! TEST_SPEC Requirement::getNumberedTitle()
SHORT
When the parent is the root element, the requirement's number
is its index within the parent's children plus 1.

PREPARATION
- Create a mock requirement "parentMock"
- Create an object "requirement" with its parent set to "parentMock"
- Prepare "parentMock" to return an empty string from number()
- Prepare "parentMock" to return 4 from displayIndexOf(_)
- Set requirement's title to "test title"

ACTION
- Call requirement.getNumberedTitle()

RESULT
- The function returns "4 test title"
*/
TEST_F(Requirement_getNumberedTitle, when_parent_is_root_number_is_child_index){
    EXPECT_TRUE(false);
}

/*! TEST_SPEC Requirement::getNumberedTitle()
SHORT
When the parent is not the root element, the requirement's number
is combined from the parent's number and the requirement's
index within the parent's children plus 1.

PREPARATION
- Create a mock requirement "parentMock"
- Create an object "requirement" with its parent set to "parentMock"
- Prepare "parentMock" to return "2.3" from number()
- Prepare "parentMock" to return 5 from displayIndexOf(_)
- Set requirement's title to "test title"

ACTION
- Call requirement.getNumberedTitle()

RESULT
- The function returns "2.3.5 test title"
*/
TEST_F(Requirement_getNumberedTitle, number_is_combined_from_parent_number_and_child_index){
    EXPECT_TRUE(false);
}

/*! TEST_SPEC Requirement::getNumberedTitle()
SHORT
When the requirement is a "DesignRequirement" the requirement's
title number begins with "DS.".

PREPARATION
- Create a mock requirement "parentMock"
- Create an object "requirement" with its parent set to "parentMock"
- Make the "requirement" a DesignRequirement
- Prepare "parentMock" to return "1.4" from number()
- Prepare "parentMock" to return 7 from displayIndexOf(_)
- Set requirement's title to "test title"

ACTION
- Call requirement.getNumberedTitle()

RESULT
- The function returns "DS.1.4.7 test title"
*/
TEST_F(Requirement_getNumberedTitle, for_design_requirements_number_starts_with_DS){
    EXPECT_TRUE(false);
}
