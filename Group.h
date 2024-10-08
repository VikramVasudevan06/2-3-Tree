#ifndef GROUP_H
#define GROUP_H
#include <iostream>
#include <cstring>
#include "Node.h"
using namespace std;

class Group{
    public: 
    //constructor
    Group();
    //destructor
    ~Group();
    //nodes in each group
    Node* left;
    Node* middle;
    Node* right;

    //int storing number of nodes
    int numNodes;
    int low;
    int high;

    //group's right, group's left, group's middle, group's parent
    Group* groupRight;
    Group* groupLeft;
    Group* groupMiddleLeft;
    Group* groupMiddleRight;
    Group* parent;

    //setting the right groups
    void setRightGroup(Group* newRightGroup);
    void setLeftGroup(Group* newLeftGroup);
    void setMiddleGroupLeft(Group* newMiddleGroupLeft);
    void setMiddleGroupRight(Group* newMiddleGroupRight);
    void setParentGroup(Group* newParent);
    

    //setting the nodes
    void setRight(Node* newRight);
    void setLeft(Node* newLeft);
    void setMiddle(Node* newMiddle);
    
    //setting the number of nodes
    void setNumNodes(int newNumNodes);
    void setLow(int newLow);
    void setHigh(int newHigh);
    
    //getting the groups
    Group* getRightGroup();
    Group* getLeftGroup();
    Group* getMiddleGroupLeft();
    Group* getMiddleGroupRight();
    Group* getParentGroup();
    Group* getSiblingGroup();
    Group* getMiddleGroup();

    //getting the nodes
    Node* getRight();
    Node* getMiddle();
    Node* getLeft();

    //getting the number of nodes
    int getNumNodes();
    int getLow();
    int getHigh();

};

#endif