#include "gtest/gtest.h"
#include "appsettings.h"
#include "attributecontainermock.h"
#include "requirement.h"
#include "riskassessmentmodelmock.h"
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
    AppSettings *settings;

    RequirementTests(){
        rng = std::mt19937(rd());
        idManager = new UniqueIDManager();
        riskAssessmentModelMock = make_shared<RiskAssessmentModelMock>();
        attributesMock = new AttributeContainerMock();
        linksMock = new LinkContainerMock();
        settings = new AppSettings();
    }

    virtual ~RequirementTests(){
        delete idManager;
        delete settings;
    }

    uint getRandomID(){
        std::uniform_int_distribution<uint> dist(0,1000);
        return dist(rng);
    }

    Requirement *newRequirement(unsigned int proposedID = -1){
        if(proposedID == -1)
            return new Requirement(idManager,
                                   new RequirementRefCounter(),
                                   riskAssessmentModelMock,
                                   new AttributeContainerMock(), new LinkContainerMock(),
                                   settings);
        else{
            return new Requirement(idManager,
                                   new RequirementRefCounter(), riskAssessmentModelMock,
                                   new AttributeContainerMock(), new LinkContainerMock(),
                                   settings, proposedID);
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
                                         new RequirementRefCounter(),
                                         shared_ptr<RiskAssessmentModelMock>(new RiskAssessmentModelMock()),
                                         new AttributeContainerMock(),
                                         new LinkContainerMock(),
                                         settings);

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

ACTION

RESULT

*/
TEST_F(Requirement_getNumberedTitle, when_parent_is_root_number_is_child_index){
    Requirement *parent = newRequirement();
    Requirement *child1 = newRequirement();
    Requirement *child2 = newRequirement();
    Requirement *child3 = newRequirement();

    parent->appendChild(child1);
    parent->appendChild(child2);
    parent->appendChild(child3);

    EXPECT_EQ(QString("1 Requirement"), child1->getNumberedTitle());
    EXPECT_EQ(QString("2 Requirement"), child2->getNumberedTitle());
    EXPECT_EQ(QString("3 Requirement"), child3->getNumberedTitle());

    delete parent;
}

/*! TEST_SPEC Requirement::getNumberedTitle()
SHORT
When the parent is not the root element, the requirement's number
is combined from the parent's number and the requirement's
index within the parent's children plus 1.

PREPARATION

ACTION

RESULT

*/
TEST_F(Requirement_getNumberedTitle, number_is_combined_from_parent_number_and_child_index){
    Requirement *root = newRequirement();
    Requirement *lastChild;

    for(int i=0;i<3;i++){
        lastChild = newRequirement();
        root->appendChild(lastChild);
    }

    for(int i=0;i<4;i++){
        lastChild->appendChild(newRequirement());
    }

    Requirement *child = newRequirement();
    lastChild->appendChild(child);

    EXPECT_EQ(QString("3.5 Requirement"), child->getNumberedTitle());

    delete root;
}

/*! TEST_SPEC Requirement::getNumberedTitle()
SHORT
When the requirement is a "DesignRequirement" the requirement's
title number begins with "DS.".

PREPARATION

ACTION

RESULT

*/
TEST_F(Requirement_getNumberedTitle, for_design_requirements_number_starts_with_DS){
    Requirement *root = newRequirement();
    Requirement *lastChild;

    for(int i=0;i<5;i++){
        lastChild = newRequirement();
        root->appendChild(lastChild);
    }

    Requirement *child = newRequirement();
    lastChild->appendChild(child);

    child->setType(Requirement::DesignRequirement);

    EXPECT_EQ(QString("DS.5.1 Requirement"), child->getNumberedTitle());

    delete root;
}

/*! TEST_SPEC Requirement::getNumberedTitle()
SHORT
When the requirement is a "DesignRequirement" the requirement's
title number begins with "DS.".

PREPARATION

ACTION

RESULT

*/
TEST_F(Requirement_getNumberedTitle, for_design_requirements_numbering_is_parallel_to_functional_requirements){
    Requirement *root = newRequirement();
    Requirement *lastChild;

    for(int i=0;i<2;i++){
        lastChild = newRequirement();
        root->appendChild(lastChild);
    }

    for(int i=0;i<5;i++){
        lastChild->appendChild(newRequirement());
    }

    Requirement *child = newRequirement();
    lastChild->appendChild(child);

    child->setType(Requirement::DesignRequirement);

    // The numbers 2.1 to 2.5 exist as well,
    // but the counting for DS-numbers starts
    // at DS.2.1 independently:

    EXPECT_EQ(QString("DS.2.1 Requirement"), child->getNumberedTitle());

    delete root;
}
