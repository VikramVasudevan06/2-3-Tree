#include <iostream>
#include <cstring>
#include "Node.h"
#include "Group.h"


//constructor
Group::Group(){
    left = NULL;
    right = NULL;
    middle = NULL;
    parent = NULL;
    groupRight = NULL;
    groupLeft = NULL;
    groupMiddleLeft = NULL;
    groupMiddleRight = NULL;
    numNodes = 0;
}
//destructor
Group::~Group(){

}
//getting the group's sibling
Group* Group::getSiblingGroup(){
    if(this->getParentGroup()->getLeftGroup() == this){
        if(this->getParentGroup()->getMiddleGroupLeft() != NULL){
            return this->getParentGroup()->getMiddleGroupLeft();
        }
        if(this->getParentGroup()->getMiddleGroupRight() != NULL){
            return this->getParentGroup()->getMiddleGroupRight();
        }
        if(this->getParentGroup()->getRightGroup() != NULL){
            return this->getParentGroup()->getRightGroup();
        }
    }
    if(this->getParentGroup()->getRightGroup() == this){
        if(this->getParentGroup()->getMiddleGroupRight() != NULL){
            return this->getParentGroup()->getMiddleGroupRight();
        }
        else if(this->getParentGroup()->getMiddleGroupLeft() != NULL){
            return this->getParentGroup()->getMiddleGroupLeft();
        }
        else if(this->getParentGroup()->getLeftGroup() != NULL){
            return this->getParentGroup()->getLeftGroup();
        }
    }
    return NULL;

}
//getting the middle group, either groupMiddleLeft or groupMiddleRight
Group* Group::getMiddleGroup(){
    if(groupMiddleLeft != NULL){
        return groupMiddleLeft;
    }
    else if(groupMiddleRight != NULL){
        return groupMiddleRight;
    }
    else{
        return NULL;
    }
}
//setting the child/parent groups of this group.
void Group::setRightGroup(Group* newRightGroup){
    groupRight = newRightGroup;
}

void Group::setLeftGroup(Group* newLeftGroup){
    groupLeft = newLeftGroup;
}
void Group::setMiddleGroupLeft(Group* newMiddleGroupLeft){
    groupMiddleLeft = newMiddleGroupLeft;
}
void Group::setMiddleGroupRight(Group* newMiddleGroupRight){
    groupMiddleRight = newMiddleGroupRight;
}
void Group::setParentGroup(Group* newParent){
    parent = newParent;
}

//setting the nodes in this group
void Group::setRight(Node* newRight){
    right = newRight;
} 
void Group::setLeft(Node* newLeft){
    left = newLeft;
}
void Group::setMiddle(Node* newMiddle){
    middle = newMiddle;
}

//setting the properties of the group.
void Group::setNumNodes(int newNumNodes){
    numNodes = newNumNodes;
}
void Group::setLow(int newLow){
    low = newLow;
}
void Group::setHigh(int newHigh){
    high = newHigh;
}

//getters
Group* Group::getRightGroup(){
    return groupRight;
}
Group* Group::getLeftGroup(){
    return groupLeft;
}
Group* Group::getMiddleGroupLeft(){
    return groupMiddleLeft;
}
Group* Group::getMiddleGroupRight(){
    return groupMiddleRight;
}
Group* Group::getParentGroup(){
    return parent;
}
Node* Group::getRight(){
    return right;
}
Node* Group::getLeft(){
    return left;
}
Node* Group::getMiddle(){
    return middle;
}
int Group::getNumNodes(){
    return numNodes;
}
int Group::getLow(){
    return low;
}
int Group::getHigh(){
    return high;
}