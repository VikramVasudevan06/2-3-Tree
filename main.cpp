/*
Author: Vikram Vasudevan
Date: 10/7/2024
Description: This program creates a 2-3 tree and can display it in the terminal. Users can add values to the tree, 
remove values, search for values, and print the tree out. The tree self-balances any time a specific group gains 3+
numbers.
Citations - This website helped with developing the tree rotations: //https://www.cs.princeton.edu/~dpw/courses/cos326-12/ass/2-3-trees.pdf
*/


//includes
#include <iostream>
#include <cstring>
#include "Node.h"
#include "Group.h"
#include <vector>
#include <fstream>

using namespace std;


//function prototypes
void add(Group* &root, Group* current, Node* newNode);
void fixTree(Group* &root, Group* current);
void print(Group* current, int count);
Group* search(Group* current, int value);
void removeMechanics(Group* &root, Group* currentInitial, int value);
Group* findSuccessor(Group* current, int value);
void callCases(Group* &root, Group* current);
void caseOne(Group* &root, Group* current);
void caseTwo(Group* &root, Group* current);
void caseThree(Group* &root, Group* current);
void caseFour(Group* &root, Group* current);
void caseFive(Group* &root, Group* current);
void caseSix(Group* &root, Group* current);

//main
int main(){
    Group* root = NULL;
    bool stillRunning = true;

    //while loop where code runs
    while(stillRunning == true){
        //prompting user for choice
        cout << "What would you like to do? ADD, REMOVE, SEARCH, PRINT, or QUIT" << endl; 
        char choice[50];
        cin.get(choice, 50);
        cin.get();
        //if statement chains for user choice
        if(strcmp(choice, "ADD") == 0){
            char input[50];
            char method;
            cout << "How many numbers will you be entering? " << endl;
            int numNums;
            cin >> numNums;
            cin.get();
            cout << "Enter your string of numbers: " << endl;
            //processing numbers, adding them to nodes, and calling the add function.
            for(int i = 0; i < numNums; i++){
                int tempInt;
                cin >> tempInt;
                cin.get();
                Node* newNode = new Node();
                newNode->setInformation(tempInt);
                //add
                add(root, root, newNode);
            }
        }
        else if(strcmp(choice, "REMOVE") == 0){
            int value;
            cout << "What number would you like to remove? " << endl;
            cin >> value;
            cin.get();
            //calling the remove function
            removeMechanics(root, search(root, value), value);
        }
        else if(strcmp(choice, "SEARCH") == 0){
            int value;
            cout << "What number would like to search for? " << endl;
            cin >> value;
            cin.get();
            //calling the search function
            search(root, value);
        }
        else if(strcmp(choice, "PRINT") == 0){
            //calling the print function
            print(root, 0);
        }
        else if(strcmp(choice, "QUIT") == 0){
            //exiting the while loop.
            stillRunning = false;
        }
    }
}

//function to find the successor group of a current value.
Group* findSuccessor(Group* current, int value){
    Group* successor = current;
    //if there are two nodes, if the middle group exists, go to the middle and then go as far left as possible.
    if(current->getNumNodes() == 2){
        if(value == current->getLow()){
            if(current->getMiddleGroup() != NULL){
                successor = current->getMiddleGroup();
                while(successor->getLeftGroup() != NULL){
                    successor = successor->getLeftGroup();
                }
                return successor;
            }
        }
    }
    //if there's only one node, go right, and then go as far left as possible to find the successor.
    if(current->getRightGroup() != NULL){
        successor = current->getRightGroup();
        while(successor->getLeftGroup() != NULL){
            successor = successor->getLeftGroup();
        }
    }
    return successor;

}

//code for the first deletion case. This codes for all of the group/node rotations.
void caseOne(Group* &root, Group* current){
    //resetting group children/parents
    if(current == current->getParentGroup()->getLeftGroup()){
        current->getSiblingGroup()->setLeft(current->getParentGroup()->getMiddle());
        current->getSiblingGroup()->setLow(current->getSiblingGroup()->getLeft()->getInformation());
        current->getSiblingGroup()->setMiddleGroupLeft(current->getSiblingGroup()->getLeftGroup());
        current->getSiblingGroup()->setLeftGroup(current->getMiddleGroup());

    }
    else if(current == current->getParentGroup()->getRightGroup()){
        current->getSiblingGroup()->setRight(current->getParentGroup()->getMiddle());
        current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getRight()->getInformation());
        current->getSiblingGroup()->setMiddleGroupLeft(current->getSiblingGroup()->getRightGroup());
        current->getSiblingGroup()->setRightGroup(current->getMiddleGroup());
    }
    if(current->getMiddleGroup() != NULL){
        current->getMiddleGroup()->setParentGroup(current->getSiblingGroup());
    }
    //resetting group data.
    current->getSiblingGroup()->setNumNodes(2);
   
    current->getParentGroup()->setMiddle(current->getMiddle());
    current->getParentGroup()->setMiddleGroupLeft(current->getSiblingGroup());
    if(current->getParentGroup()->getMiddleGroupLeft() != NULL){
        current->getParentGroup()->getMiddleGroupLeft()->setParentGroup(current->getParentGroup());
    }

    Group* temp = current->getParentGroup();
    current->getParentGroup()->setLeftGroup(NULL);
    current->getParentGroup()->setRightGroup(NULL);
    //caseOne is not a terminating case. At the end of caseOne, call callCases again.
    callCases(root, temp);
}

//code for the second deletion case. This codes for all of the group/node rotations.
void caseTwo(Group* &root, Group* current){
    current->getMiddle()->setInformation((current->getParentGroup()->getMiddle()->getInformation()));
    if(current == current->getParentGroup()->getLeftGroup()){
        current->getParentGroup()->getMiddle()->setInformation(current->getSiblingGroup()->getLow());
        if(current->getSiblingGroup()->getLeft() != NULL && current->getSiblingGroup()->getLeft()->getInformation() == current->getSiblingGroup()->getLow()){
            current->getSiblingGroup()->setLeft(NULL);
            
        }
        else{
            current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getRight());
            current->getSiblingGroup()->setRight(NULL);
            
        }
        current->getSiblingGroup()->setLow(current->getSiblingGroup()->getMiddle()->getInformation());
        current->setLeftGroup(current->getMiddleGroupLeft());
        current->setMiddleGroupLeft(NULL);
        current->setRightGroup(current->getSiblingGroup()->getLeftGroup());
        if(current->getRightGroup() != NULL){
            current->getRightGroup()->setParentGroup(current);
        }
        current->getSiblingGroup()->setLeftGroup(current->getSiblingGroup()->getMiddleGroup());
        
    }
    else if(current == current->getParentGroup()->getRightGroup()){
        current->getParentGroup()->getMiddle()->setInformation(current->getSiblingGroup()->getHigh());
        if(current->getSiblingGroup()->getRight() != NULL && current->getSiblingGroup()->getRight()->getInformation() == current->getSiblingGroup()->getHigh()){
            current->getSiblingGroup()->setRight(NULL);
        }
        else{
            current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getLeft());
            current->getSiblingGroup()->setLeft(NULL);
        }
        current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getMiddle()->getInformation());
        current->setRightGroup(current->getMiddleGroupLeft());
        current->setMiddleGroupLeft(NULL);
        current->setLeftGroup(current->getSiblingGroup()->getRightGroup());
        if(current->getSiblingGroup()->getRightGroup() != NULL){
            current->getSiblingGroup()->setParentGroup(current);
        }
        current->getSiblingGroup()->setRightGroup(current->getSiblingGroup()->getMiddleGroup());
    }
    if(current->getSiblingGroup()->getMiddleGroupLeft() != NULL){
        current->getSiblingGroup()->setMiddleGroupLeft(NULL);
    }
    else{
        current->getSiblingGroup()->setMiddleGroupRight(NULL);
    }
    //resetting group data.
    current->getParentGroup()->setHigh(current->getParentGroup()->getMiddle()->getInformation());
    current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
    current->setHigh(current->getMiddle()->getInformation());
    current->setLow(current->getMiddle()->getInformation());
    current->getSiblingGroup()->setNumNodes(1);

}


//code for the third deletion case. This codes for all of the group/node rotations.
void caseThree(Group* &root, Group* current){
    //changing group connections
    if(current == current->getParentGroup()->getLeftGroup()){
        if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getLow()){
            current->getSiblingGroup()->setLeft(current->getParentGroup()->getMiddle());
            current->getParentGroup()->setMiddle(current->getParentGroup()->getRight());
            current->getParentGroup()->setRight(NULL);
            
        }
        else{
            current->getSiblingGroup()->setLeft(current->getParentGroup()->getLeft());
            current->getParentGroup()->setLeft(NULL);
        }
        current->getSiblingGroup()->setLow(current->getSiblingGroup()->getLeft()->getInformation());
        current->getSiblingGroup()->setMiddleGroupLeft(current->getSiblingGroup()->getLeftGroup());
        current->getSiblingGroup()->setLeftGroup(current->getMiddleGroupLeft());
        if(current->getMiddleGroupLeft() != NULL){
            current->getMiddleGroupLeft()->setParentGroup(current->getSiblingGroup());
        }
        current->getParentGroup()->setLeftGroup(current->getSiblingGroup());
        if(current->getSiblingGroup() != NULL){
            current->getSiblingGroup()->setParentGroup(current->getParentGroup());
        }
    }
    else if(current == current->getParentGroup()->getRightGroup()){
        if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getHigh()){
            current->getSiblingGroup()->setRight(current->getParentGroup()->getMiddle());
            current->getParentGroup()->setMiddle(current->getParentGroup()->getLeft());
            current->getParentGroup()->setLeft(NULL);
        }
        else{
            current->getSiblingGroup()->setRight(current->getParentGroup()->getRight());
            current->getParentGroup()->setRight(NULL);
        }
        current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getRight()->getInformation());
        current->getSiblingGroup()->setMiddleGroupLeft(current->getSiblingGroup()->getRightGroup());
        current->getSiblingGroup()->setRightGroup(current->getMiddleGroupLeft());
        if(current->getMiddleGroupLeft() != NULL){
            current->getMiddleGroupLeft()->setParentGroup(current->getSiblingGroup());
        }
        current->getParentGroup()->setRightGroup(current->getSiblingGroup());
        if(current->getSiblingGroup() != NULL){
            current->getSiblingGroup()->setParentGroup(current->getParentGroup());
        }
    }
    //resetting group data
    current->getSiblingGroup()->setNumNodes(2);
    current->getParentGroup()->setNumNodes(1);
    current->getParentGroup()->setHigh(current->getParentGroup()->getMiddle()->getInformation());
    current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
    if(current->getParentGroup()->getMiddleGroupLeft() != NULL){
        current->getParentGroup()->setMiddleGroupLeft(NULL);
    }
    else{
        current->getParentGroup()->setMiddleGroupRight(NULL);
    }
    delete current;
}

//code for the fourth deletion case. This codes for all of the group/node rotations.
void caseFour(Group* &root, Group* current){
    //changing group connections
    if(current->getParentGroup()->getRightGroup()->getNumNodes() == 1){
        if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getHigh()){
            current->getParentGroup()->getRightGroup()->setLeft(current->getParentGroup()->getMiddle());
            current->getParentGroup()->setMiddle(current->getParentGroup()->getLeft());
            current->getParentGroup()->setLeft(NULL);
        }
        else{
            current->getParentGroup()->getRightGroup()->setLeft(current->getParentGroup()->getRight());
            current->getParentGroup()->setRight(NULL);
        }
        current->getParentGroup()->getRightGroup()->setMiddleGroupLeft(current->getParentGroup()->getRightGroup()->getLeftGroup());
        current->getParentGroup()->getRightGroup()->setLeftGroup(current->getMiddleGroup());
        if(current->getMiddleGroup() != NULL){
            current->getMiddleGroup()->setParentGroup(current->getParentGroup());
        }
        current->getParentGroup()->getRightGroup()->setNumNodes(2);
        current->getParentGroup()->getRightGroup()->setLow(current->getParentGroup()->getRightGroup()->getLeft()->getInformation());
        current->getParentGroup()->setHigh(current->getParentGroup()->getMiddle()->getInformation());
    }
    else if(current->getParentGroup()->getLeftGroup()->getNumNodes() == 1){
        if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getLow()){
            current->getParentGroup()->getLeftGroup()->setRight(current->getParentGroup()->getMiddle());
            current->getParentGroup()->setMiddle(current->getParentGroup()->getRight());
            current->getParentGroup()->setRight(NULL);
        }
        else{
            current->getParentGroup()->getLeftGroup()->setRight(current->getParentGroup()->getLeft());
            current->getParentGroup()->setLeft(NULL);
        }
        current->getParentGroup()->getLeftGroup()->setMiddleGroupLeft(current->getParentGroup()->getLeftGroup()->getRightGroup());
        current->getParentGroup()->getLeftGroup()->setRightGroup(current->getMiddleGroup());
        if(current->getMiddleGroup() != NULL){
            current->getMiddleGroup()->setParentGroup(current->getParentGroup());
        }
        current->getParentGroup()->getLeftGroup()->setNumNodes(2);
        current->getParentGroup()->getLeftGroup()->setHigh(current->getParentGroup()->getLeftGroup()->getRight()->getInformation());
        current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
    }
    current->getParentGroup()->setNumNodes(1);
    if(current->getParentGroup()->getMiddleGroupLeft() != NULL){
        current->getParentGroup()->setMiddleGroupLeft(NULL);
    }
    else{
        current->getParentGroup()->setMiddleGroupRight(NULL);
    }
    delete current;
}

//code for the fifth deletion case. This codes for all of the group/node rotations.
void caseFive(Group* &root, Group* current){
    //changing group connections
    if(current == current->getParentGroup()->getLeftGroup()){
        current->getMiddle()->setInformation(current->getParentGroup()->getLow());
        if(current->getParentGroup()->getLeft() != NULL){
            current->getParentGroup()->getLeft()->setInformation(current->getParentGroup()->getMiddleGroup()->getLow());
            current->getParentGroup()->setLow(current->getParentGroup()->getLeft()->getInformation());
        }
        else{
            current->getParentGroup()->getMiddle()->setInformation(current->getParentGroup()->getMiddleGroup()->getLow());
            current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
        }
        if(current->getSiblingGroup()->getLeft() != NULL){
            current->getSiblingGroup()->setLeft(NULL);
        }
        else{
            current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getRight());
            current->getSiblingGroup()->setRight(NULL);
        }
        current->setLeftGroup(current->getMiddleGroup());
        current->setMiddleGroupLeft(NULL);
        current->setRightGroup(current->getSiblingGroup()->getLeftGroup());
        if(current->getSiblingGroup()->getLeftGroup() != NULL){
            current->getSiblingGroup()->getLeftGroup()->setParentGroup(current);
        }
        current->getSiblingGroup()->setLeftGroup(current->getSiblingGroup()->getMiddleGroup());
    }
    else if(current == current->getParentGroup()->getRightGroup()){
        current->getMiddle()->setInformation(current->getParentGroup()->getHigh());
        if(current->getParentGroup()->getRight() != NULL){
            current->getParentGroup()->getRight()->setInformation(current->getParentGroup()->getMiddleGroup()->getHigh());
            current->getParentGroup()->setHigh(current->getParentGroup()->getRight()->getInformation());
        }
        else{
            current->getParentGroup()->getMiddle()->setInformation(current->getParentGroup()->getMiddleGroup()->getHigh());
            current->getParentGroup()->setHigh(current->getParentGroup()->getMiddle()->getInformation());

        }
        if(current->getSiblingGroup()->getRight() != NULL){
            current->getSiblingGroup()->setRight(NULL);
        }
        else{
            current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getLeft());
            current->getSiblingGroup()->setLeft(NULL);
        }
        current->setRightGroup(current->getMiddleGroup());
        current->setMiddleGroupLeft(NULL);
        current->setLeftGroup(current->getSiblingGroup()->getRightGroup());
        if(current->getSiblingGroup()->getRightGroup() != NULL){
            current->getSiblingGroup()->getRightGroup()->setParentGroup(current);
        }
        current->getSiblingGroup()->setRightGroup(current->getSiblingGroup()->getMiddleGroup());

    }
    if(current->getSiblingGroup()->getMiddleGroupLeft() != NULL){
        current->getSiblingGroup()->setMiddleGroupLeft(NULL);
    }
    else{
        current->getSiblingGroup()->setMiddleGroupRight(NULL);
    }
    //resetting group data.
    current->setHigh(current->getMiddle()->getInformation());
    current->setLow(current->getMiddle()->getInformation());
    current->getSiblingGroup()->setNumNodes(1);
    current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getMiddle()->getInformation());
    current->getSiblingGroup()->setLow(current->getSiblingGroup()->getMiddle()->getInformation());
}


//code for the sixth deletion case. This codes for all of the group/node rotations.
void caseSix(Group* &root, Group* current){
    //changing group connections
    if(current->getParentGroup()->getLeftGroup()->getNumNodes() == 2){
        current->getMiddle()->setInformation(current->getParentGroup()->getLow());
        if(current->getParentGroup()->getLeft() != NULL){
            current->getParentGroup()->getLeft()->setInformation(current->getParentGroup()->getLeftGroup()->getHigh());
        }
        else{
            current->getParentGroup()->getMiddle()->setInformation(current->getParentGroup()->getLeftGroup()->getHigh());
        }
        if(current->getParentGroup()->getLeftGroup()->getRight() != NULL){
            current->getParentGroup()->getLeftGroup()->setRight(NULL);
        }
        else{
            current->getParentGroup()->getLeftGroup()->setMiddle(current->getParentGroup()->getLeftGroup()->getLeft());
            current->getParentGroup()->getLeftGroup()->setLeft(NULL);
        }
        current->setRightGroup(current->getMiddleGroup());
        current->setMiddleGroupLeft(NULL);
        current->setLeftGroup(current->getParentGroup()->getLeftGroup()->getRightGroup());
        if(current->getParentGroup()->getLeftGroup()->getRightGroup() != NULL){
            current->getParentGroup()->getLeftGroup()->getRightGroup()->setParentGroup(current);
        }
        current->getParentGroup()->getLeftGroup()->setRightGroup(current->getParentGroup()->getLeftGroup()->getMiddleGroup());
        if(current->getParentGroup()->getLeftGroup()->getMiddleGroupLeft() != NULL){
            current->getParentGroup()->getLeftGroup()->getRightGroup()->setParentGroup(current->getParentGroup()->getLeftGroup());
            current->getParentGroup()->getLeftGroup()->setMiddleGroupLeft(NULL);
        }
        else{
            current->getParentGroup()->getLeftGroup()->setMiddleGroupRight(NULL);
        }
    }
    else if(current->getParentGroup()->getRightGroup()->getNumNodes() == 2){
        current->getMiddle()->setInformation(current->getParentGroup()->getHigh());
        if(current->getParentGroup()->getRight() != NULL){
            current->getParentGroup()->getRight()->setInformation(current->getParentGroup()->getRightGroup()->getLow());
        }
        else{
            current->getParentGroup()->getMiddle()->setInformation(current->getParentGroup()->getRightGroup()->getLow());
        }
        if(current->getParentGroup()->getRightGroup()->getLeft() != NULL){
            current->getParentGroup()->getRightGroup()->setLeft(NULL);
        }
        else{
            current->getParentGroup()->getRightGroup()->setMiddle(current->getParentGroup()->getRightGroup()->getRight());
            current->getParentGroup()->getRightGroup()->setRight(NULL);
        }
        current->setLeftGroup(current->getMiddleGroup());
        current->setMiddleGroupLeft(NULL);
        current->setRightGroup(current->getParentGroup()->getRightGroup()->getLeftGroup());
        if(current->getParentGroup()->getRightGroup()->getLeftGroup() != NULL){
            current->getRightGroup()->setParentGroup(current);
        }
        current->getParentGroup()->getRightGroup()->setLeftGroup(current->getParentGroup()->getRightGroup()->getMiddleGroup());
        if(current->getParentGroup()->getRightGroup()->getMiddleGroupLeft() != NULL){
            current->getParentGroup()->getRightGroup()->setMiddleGroupLeft(NULL);
        }
        else{
            current->getParentGroup()->getRightGroup()->setMiddleGroupRight(NULL);
        }
    }
}

//function that calls the relevant delete cases
void callCases(Group* &root, Group* current){
    print(root, 0);
    if(current == root){
    }
    if(current == root){
        root = current->getMiddleGroup();
        current->setMiddleGroupLeft(NULL);
        root->setParentGroup(NULL);
        delete current;
        return;
    }
    //list of if statements. Depending on which is satisfied, the relevant case will be called.
    if(current->getParentGroup()->getNumNodes() == 1 && current->getSiblingGroup()->getNumNodes() == 1){
        caseOne(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 1 && current->getSiblingGroup()->getNumNodes() == 2){
        caseTwo(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 2 && current->getSiblingGroup()->getNumNodes() == 1){
        caseThree(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 2 && current->getParentGroup()->getMiddleGroup() == current && (current->getParentGroup()->getLeftGroup()->getNumNodes() == 1 || current->getParentGroup()->getRightGroup()->getNumNodes() == 1)){
        caseFour(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 2 && current->getSiblingGroup()->getNumNodes() == 2){
        caseFive(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 2 && current->getParentGroup()->getMiddleGroup() == current && (current->getParentGroup()->getLeftGroup()->getNumNodes() == 2 || current->getParentGroup()->getRightGroup()->getNumNodes() == 2)){
        caseSix(root, current);
        return;
    }
}

//function that handles the initial remove call
void removeMechanics(Group* &root, Group* currentInitial, int value){
    //if only the root exists, delete it and declare the tree empty.
    if(root->getMiddle()->getInformation() == value && root->getNumNodes() == 1){
        root = NULL;
        cout << "The tree is empty" << endl;
        return;
    }
    Group* current = findSuccessor(currentInitial, value);
    //swapping the values of the current and the successor, 
    if(current != currentInitial){
        if(currentInitial->getLeft() != NULL && currentInitial->getLeft()->getInformation() == value){
            currentInitial->getLeft()->setInformation(current->getLow());
        }
        else if(currentInitial->getMiddle() != NULL && currentInitial->getMiddle()->getInformation() == value){
            currentInitial->getMiddle()->setInformation(current->getLow());
        }
        else{
            currentInitial->getRight()->setInformation(current->getLow());
        }
    }
    print(root, 0);
    if(current != currentInitial){
        value = current->getLow();
    }
    //if current - which is the successor - has two nodes, delete the successor node and readjust the remaining node
    //so that it is in the middle slot.
    if(current->getNumNodes() == 2){
        if(current->getMiddle()->getInformation() == value){
            if(current->getLeft() != NULL){
                current->setHigh(current->getLeft()->getInformation());
                current->setMiddle(current->getLeft());
                current->setLeft(NULL);
            }
            else{
                current->setLow(current->getRight()->getInformation());
                current->setMiddle(current->getRight());
                current->setRight(NULL);
            }
        }
        else if (current->getMiddle()->getInformation() > value){
            current->setLeft(NULL);
            current->setLow(current->getMiddle()->getInformation());
        }
        else{
            current->setRight(NULL);
            current->setHigh(current->getMiddle()->getInformation());
        }
        current->setNumNodes(1);
    }
    else if(current->getNumNodes() == 1){
        //if the successor only has one node, and its parent only has one node, follow this block of code.
        if(current->getParentGroup()->getNumNodes() == 1){
            //if the sibling of the group has two nodes, steal one of the sibling's nodes and rearrange.
            if(current->getSiblingGroup()->getNumNodes() == 2){
                delete current->getMiddle();
                current->setMiddle(current->getParentGroup()->getMiddle());
                if(current->getMiddle()->getInformation() > current->getSiblingGroup()->getMiddle()->getInformation()){
                    if(current->getSiblingGroup()->getMiddle()->getInformation() == current->getSiblingGroup()->getHigh()){
                        current->getParentGroup()->setMiddle(current->getSiblingGroup()->getMiddle());
                        current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getLeft());
                        current->getSiblingGroup()->setLeft(NULL);
                    }
                    else{
                        current->getParentGroup()->setMiddle(current->getSiblingGroup()->getRight());
                        current->getSiblingGroup()->setRight(NULL);
                    }
                }
                else if(current->getMiddle()->getInformation() < current->getSiblingGroup()->getMiddle()->getInformation()){
                    if(current->getSiblingGroup()->getMiddle()->getInformation() == current->getSiblingGroup()->getLow()){
                        current->getParentGroup()->setMiddle(current->getSiblingGroup()->getMiddle());
                        current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getRight());
                        current->getSiblingGroup()->setRight(NULL);
                    }
                    else{
                        current->getParentGroup()->setMiddle(current->getSiblingGroup()->getLeft());
                        current->getSiblingGroup()->setLeft(NULL);
                    }
             
                }
                current->getSiblingGroup()->setNumNodes(1);
                current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getMiddle()->getInformation());
                current->getSiblingGroup()->setLow(current->getSiblingGroup()->getMiddle()->getInformation());
            }
            //otherwise, call the delete cases.
            else if(current->getSiblingGroup()->getNumNodes() == 1){
                callCases(root, current);
            }

            

        }
        else if(current->getParentGroup()->getNumNodes() == 2){
            //if parent has two nodes, rearrange the nodes, depending on how many nodes the sibling has, and whether the successor
            //group is the left group, right group, or middle group.
            if(current == current->getParentGroup()->getLeftGroup()){
                

                if(current->getSiblingGroup()->getNumNodes() == 2){
                    if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getLow()){
                        current->setMiddle(current->getParentGroup()->getMiddle());
                        current->getParentGroup()->setMiddle(current->getParentGroup()->getRight());
                        current->getParentGroup()->setRight(NULL);
                    }
                    else if(current->getParentGroup()->getLeft()->getInformation() == current->getParentGroup()->getLow()){
                        current->setMiddle(current->getParentGroup()->getLeft());
                        current->getParentGroup()->setLeft(NULL);
                    }
                    if(current->getSiblingGroup()->getLeft()->getInformation() == current->getSiblingGroup()->getLow()){
                        current->getParentGroup()->setLeft(current->getSiblingGroup()->getLeft());
                        current->getSiblingGroup()->setLeft(NULL);
                    }
                    else{
                        current->getParentGroup()->setLeft(current->getSiblingGroup()->getMiddle());
                        current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getRight());
                        current->getSiblingGroup()->setRight(NULL);
                    }
                    current->getSiblingGroup()->setNumNodes(1);
                    current->getSiblingGroup()->setLow(current->getSiblingGroup()->getMiddle()->getInformation());


                }
                else if(current->getSiblingGroup()->getNumNodes() == 1){
  

                    if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getLow()){

                        current->getSiblingGroup()->setLeft(current->getParentGroup()->getMiddle());
                        current->getParentGroup()->setMiddle(current->getParentGroup()->getRight());
                        current->getParentGroup()->setRight(NULL);
                    }
                    else{
                        current->getSiblingGroup()->setLeft(current->getParentGroup()->getLeft());
                        current->getParentGroup()->setLeft(NULL);
                    }
                    current->getSiblingGroup()->setLow(current->getSiblingGroup()->getLeft()->getInformation());
                    current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
                    current->getParentGroup()->setNumNodes(1);
                    current->getSiblingGroup()->setNumNodes(2);
                    current->getParentGroup()->setLeftGroup(current->getSiblingGroup());
                    if(current->getParentGroup()->getMiddleGroupLeft() != NULL){
                        current->getParentGroup()->setMiddleGroupLeft(NULL);
                    }
                    else{
                        current->getParentGroup()->setMiddleGroupRight(NULL);
                    }
                    delete current;
                    return;

                }

            }
            if(current == current->getParentGroup()->getRightGroup()){
                if(current == current->getParentGroup()->getRightGroup()){
                    if(current->getSiblingGroup()->getNumNodes() == 2){
                        if(current->getParentGroup()->getRight()->getInformation() == current->getParentGroup()->getHigh()){
                            current->setMiddle(current->getParentGroup()->getRight());
                        }
                        else if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getHigh()){
                            current->setMiddle(current->getParentGroup()->getMiddle());
                            current->getParentGroup()->setMiddle(current->getParentGroup()->getLeft());
                            current->getParentGroup()->setLeft(NULL);
                        }

                        if(current->getSiblingGroup()->getRight()->getInformation() == current->getSiblingGroup()->getHigh()){
                            current->getParentGroup()->setRight(current->getSiblingGroup()->getRight());
                            current->getSiblingGroup()->setRight(NULL);
                        }
                        else{
                            current->getParentGroup()->setRight(current->getSiblingGroup()->getMiddle());
                            current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getLeft());
                            current->getSiblingGroup()->setLeft(NULL);
                        }
                    }
                    else if(current->getSiblingGroup()->getNumNodes() == 1){
                        if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getHigh()){
                            current->getSiblingGroup()->setRight(current->getParentGroup()->getMiddle());
                            current->getParentGroup()->setMiddle(current->getParentGroup()->getLeft());
                            current->getParentGroup()->setLeft(NULL);
                        }
                        else{
                            current->getSiblingGroup()->setRight(current->getParentGroup()->getRight());
                            current->getParentGroup()->setRight(NULL);
                        }
                        current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getRight()->getInformation());
                        current->getParentGroup()->setHigh(current->getParentGroup()->getMiddle()->getInformation());
                        current->getParentGroup()->setNumNodes(1);
                        current->getSiblingGroup()->setNumNodes(2);
                        current->getParentGroup()->setRightGroup(current->getSiblingGroup());
                        if(current->getParentGroup()->getRightGroup() != NULL){
                            current->getParentGroup()->getRightGroup()->setParentGroup(current->getParentGroup());
                        }
                        if(current->getParentGroup()->getMiddleGroupLeft() != NULL){
                            current->getParentGroup()->setMiddleGroupLeft(NULL);
                        }
                        else{
                            current->getParentGroup()->setMiddleGroupRight(NULL);
                        }
                        delete current;

                    }
                }
            }
            else if(current == current->getParentGroup()->getMiddleGroup()){
                //if current is the middle group, steal nodes from either the left group or the right group. getSibling does not work
                //if the current group is the middle group, thus three rounds of if statements are necessary.
                if(current->getParentGroup()->getLeftGroup()->getNumNodes() == 2){
                    current->getParentGroup()->getLeftGroup()->setNumNodes(1);
                    current->getMiddle()->setInformation(current->getParentGroup()->getLow());
                    current->setLow(current->getParentGroup()->getLow());
                    current->setHigh(current->getParentGroup()->getLow());
                    if(current->getParentGroup()->getLeft() != NULL){
                        current->getParentGroup()->getLeft()->setInformation(current->getParentGroup()->getLeftGroup()->getHigh());
                    }
                    else{
                        current->getParentGroup()->getMiddle()->setInformation(current->getParentGroup()->getLeftGroup()->getHigh());
                    }
                    current->getParentGroup()->setLow(current->getParentGroup()->getLeftGroup()->getHigh());
                    if(current->getParentGroup()->getLeftGroup()->getRight() != NULL){
                        current->getParentGroup()->getLeftGroup()->setRight(NULL);
                    }
                    else{
                        current->getParentGroup()->getLeftGroup()->setMiddle(current->getParentGroup()->getLeftGroup()->getLeft());
                        current->getParentGroup()->getLeftGroup()->setLeft(NULL);
                    }
                    current->getParentGroup()->getLeftGroup()->setHigh(current->getParentGroup()->getLeftGroup()->getMiddle()->getInformation());
                }
                else if(current->getParentGroup()->getRightGroup()->getNumNodes() == 2){
                    current->getParentGroup()->getRightGroup()->setNumNodes(1);
                    current->getMiddle()->setInformation(current->getParentGroup()->getHigh());
                    current->setLow(current->getParentGroup()->getHigh());
                    current->setHigh(current->getParentGroup()->getHigh());
                    if(current->getParentGroup()->getRight() != NULL){
                        current->getParentGroup()->getRight()->setInformation(current->getParentGroup()->getRightGroup()->getLow());
                    }
                    else{
                        current->getParentGroup()->getMiddle()->setInformation(current->getParentGroup()->getRightGroup()->getLow());
                    }
                    current->getParentGroup()->setHigh(current->getParentGroup()->getRightGroup()->getLow());
                    if(current->getParentGroup()->getLeftGroup()->getRight() == NULL){
                        current->getParentGroup()->getRightGroup()->setLeft(NULL);
                    }
                    else{
                        current->getParentGroup()->getRightGroup()->setMiddle(current->getParentGroup()->getRightGroup()->getRight());
                        current->getParentGroup()->getRightGroup()->setRight(NULL);
                    }
                    current->getParentGroup()->getRightGroup()->setLow(current->getParentGroup()->getRightGroup()->getMiddle()->getInformation());
                }
                else{
                    //if neither sibling has two nodes, adjust the nodes as follows.
                    Node* temp = new Node();
                    temp->setInformation(current->getParentGroup()->getLow());
                    current->getParentGroup()->getLeftGroup()->setRight(temp);
                    current->getParentGroup()->getLeftGroup()->setHigh(temp->getInformation());
                    current->getParentGroup()->getLeftGroup()->setNumNodes(2);
                    current->getParentGroup()->setNumNodes(1);
                    if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getLow()){
                        current->getParentGroup()->setMiddle(current->getParentGroup()->getRight());
                        current->getParentGroup()->setRight(NULL);
                    }
                    else{
                        current->getParentGroup()->setLeft(NULL);
                    }
                    current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
                    if(current->getParentGroup()->getMiddleGroupLeft() != NULL){
                        current->getParentGroup()->setMiddleGroupLeft(NULL);
                    }
                    else{
                        current->getParentGroup()->setMiddleGroupRight(NULL);
                    }
                    delete current;
                }
            }
        }
    }
}


//function that handles the initial add call.
void add(Group* &root, Group* current, Node* newNode){
    //if root is null
    if(root == NULL){
        root = new Group();
        root->setMiddle(newNode);
        root->setNumNodes(1);
        root->setLow(newNode->getInformation());
        root->setHigh(newNode->getInformation());
    }
    //if root isn't null
    else{
        //traversing to correct location in tree
        if(newNode->getInformation() < current->getLow()){
            if(current->getLeftGroup() != NULL){
                add(root, current->getLeftGroup(), newNode);
                return;
            }
        }
        else if(newNode->getInformation() > current->getLow() && newNode->getInformation() < current->getHigh()){
            if(current->getMiddleGroupLeft() != NULL){
                add(root, current->getMiddleGroupLeft(), newNode);
                return;
            }
            else if(current->getMiddleGroupRight() != NULL){
                add(root, current->getMiddleGroupRight(), newNode);
                return;
            }
        }
        else if(newNode->getInformation() > current->getHigh()){
            if(current->getRightGroup() != NULL){
                add(root, current->getRightGroup(), newNode);
                return;
            }
        }
        //if there's only one node, just adding it in. 
        if(current->getNumNodes() == 1){
            if(newNode->getInformation() < current->getMiddle()->getInformation()){
                current->setLeft(newNode);
                current->setLow(newNode->getInformation());
            }
            else if(newNode->getInformation() > current->getMiddle()->getInformation()){
                current->setRight(newNode);
                current->setHigh(newNode->getInformation());
            }
            current->setNumNodes(2);
        }
        else if(current->getNumNodes() == 2){
        //if there are two nodes
            if(current->getLeft() == NULL){
                if(newNode->getInformation() < current->getMiddle()->getInformation()){
                    current->setLeft(newNode);
                }
                else if(newNode->getInformation() > current->getMiddle()->getInformation()){
                    if(newNode->getInformation() > current->getRight()->getInformation()){
                        Node* tempRight = current->getRight();
                        Node* tempMid = current->getMiddle();
                        current->setLeft(tempMid);
                        current->setMiddle(tempRight);
                        current->setRight(newNode);
                    }
                    else{
                        current->setLeft(current->getMiddle());
                        current->setMiddle(newNode);
                    }
                }
            }
            else if(current->getRight() == NULL){
                if(newNode->getInformation() > current->getMiddle()->getInformation()){
                    current->setRight(newNode);
                }
                else if(newNode->getInformation() < current->getMiddle()->getInformation()){
                    if(newNode->getInformation() < current->getLeft()->getInformation()){
                        current->setRight(current->getMiddle());
                        current->setMiddle(current->getLeft());
                        current->setLeft(newNode);
                    }
                    else{
                        current->setRight(current->getMiddle());
                        current->setMiddle(newNode);
                    }
                }
            }
            //call fixTree after adding a third node.
            fixTree(root, current);
        }
    }
}
//this function fixes the tree after three nodes have been added to a single group.
void fixTree(Group* &root, Group* current){
    Group* left = new Group();
    Group* right = new Group();
    Group* parent;
    //if there is no parent, create one.
    if(current->getParentGroup() == NULL){
        parent = new Group();
        root = parent;

    }
    else{
        parent = current->getParentGroup();
    }

    left->setParentGroup(parent);
    right->setParentGroup(parent);
    left->setLeftGroup(current->getLeftGroup());
    if(current->getLeftGroup() != NULL){
        current->getLeftGroup()->setParentGroup(left);
    }
    if(current->getMiddleGroupRight() != NULL){
    }
    left->setRightGroup(current->getMiddleGroupLeft());
    if(current->getMiddleGroupLeft() != NULL){
        current->getMiddleGroupLeft()->setParentGroup(left);
    }

    right->setLeftGroup(current->getMiddleGroupRight());
    if(current->getMiddleGroupRight() != NULL){
        current->getMiddleGroupRight()->setParentGroup(right);
    }
    right->setRightGroup(current->getRightGroup());
    if(current->getRightGroup() != NULL){
        current->getRightGroup()->setParentGroup(right);
    }
    //splitting each node into its own unique group.
    left->setMiddle(current->getLeft());
    left->setLow(current->getLeft()->getInformation());
    left->setHigh(current->getLeft()->getInformation());
    right->setLow(current->getRight()->getInformation());
    right->setHigh(current->getRight()->getInformation());
    left->setNumNodes(1);
    right->setMiddle(current->getRight());
    right->setNumNodes(1);

    //adding the new unique groups to the parent's network.
    if(parent->getNumNodes() == 2){
        if(parent->getLeft() != NULL){
            if(current->getMiddle()->getInformation() < parent->getLeft()->getInformation()){
                parent->setRight(parent->getMiddle());
                parent->setMiddle(parent->getLeft());
                parent->setLeft(current->getMiddle());
                
                parent->setLeftGroup(left);
                if(parent->getMiddleGroupLeft() != NULL){
                    if(parent->getMiddleGroupRight() != NULL){
         
                        parent->setRightGroup(parent->getMiddleGroupRight());
                        
                    }
                    parent->setMiddleGroupRight(parent->getMiddleGroupLeft());
                }
                parent->setMiddleGroupLeft(right);
            }
            else if(current->getMiddle()->getInformation() > parent->getLeft()->getInformation() && current->getMiddle()->getInformation() < parent->getMiddle()->getInformation()){
                parent->setRight(parent->getMiddle());
                parent->setMiddle(current->getMiddle());
                parent->setMiddleGroupLeft(left);
                parent->setMiddleGroupRight(right);
            }
            else{
                parent->setRight(current->getMiddle());
                if(parent->getMiddleGroupRight() != NULL){
                    if(parent->getMiddleGroupLeft() != NULL){
         
                        parent->setLeftGroup(parent->getMiddleGroupLeft());
                        
                    }
                    parent->setMiddleGroupLeft(parent->getMiddleGroupRight());
                }
                parent->setMiddleGroupRight(left);
                parent->setRightGroup(right);
            }
        }
        else if(parent->getRight() != NULL){
            if(current->getMiddle()->getInformation() > parent->getRight()->getInformation()){
                parent->setLeft(parent->getMiddle());
                parent->setMiddle(parent->getRight());
                parent->setRight(current->getMiddle());
                parent->setRightGroup(right);
                if(parent->getMiddleGroupRight() != NULL){
                    if(parent->getMiddleGroupLeft() != NULL){
         
                        parent->setLeftGroup(parent->getMiddleGroupLeft());
                        
                    }
                    parent->setMiddleGroupLeft(parent->getMiddleGroupRight());
                }
                parent->setMiddleGroupRight(left);

            }
            else if(current->getMiddle()->getInformation() < parent->getRight()->getInformation() && current->getMiddle()->getInformation() > parent->getMiddle()->getInformation()){
                parent->setLeft(parent->getMiddle());
                parent->setMiddle(current->getMiddle());
                parent->setMiddleGroupRight(right);
                parent->setMiddleGroupLeft(left);
            }
            else{
                parent->setLeft(current->getMiddle());
                if(parent->getMiddleGroupLeft() != NULL){
                    if(parent->getMiddleGroupRight() != NULL){
         
                        parent->setRightGroup(parent->getMiddleGroupRight());
                        
                    }
                    parent->setMiddleGroupRight(parent->getMiddleGroupLeft());
                }
                parent->setMiddleGroupLeft(right);
                parent->setLeftGroup(left);
            }
        }
        parent->setLow(parent->getLeft()->getInformation());
        parent->setHigh(parent->getRight()->getInformation());
        fixTree(root, parent);
    }
    else if(parent->getNumNodes() == 1){
        if(current->getMiddle()->getInformation() > parent->getMiddle()->getInformation()){
            parent->setRight(current->getMiddle());
            parent->setHigh(parent->getRight()->getInformation());
            parent->setLow(parent->getMiddle()->getInformation());
            parent->setRightGroup(right);
            parent->setMiddleGroupRight(left);
            parent->setNumNodes(2);
        }
        else{
            parent->setLeft(current->getMiddle());
            parent->setHigh(parent->getMiddle()->getInformation());
            parent->setLow(parent->getLeft()->getInformation());
            parent->setLeftGroup(left);
            parent->setMiddleGroupLeft(right);
            parent->setNumNodes(2);
        }
    }
    else if(parent->getNumNodes() == 0){
        parent->setMiddle(current->getMiddle());
        parent->setLow(parent->getMiddle()->getInformation());
        parent->setHigh(parent->getMiddle()->getInformation());
        parent->setLeftGroup(left);
        parent->setRightGroup(right);
        parent->setNumNodes(1);
    }
    current->setMiddle(NULL);
    delete current;
}

//searching through the tree to determine if the value parameter exists.
Group* search(Group* current, int value){
    if(current->getLeft() != NULL){
        if(value == current->getLeft()->getInformation()){
            cout << "This value exists!" << endl;
            return current;
        }
    }
    if(current->getMiddle() != NULL){
        if(value == current->getMiddle()->getInformation()){
            cout << "This value exists!" << endl;

            return current;
        }
    }
    if(current->getRight() != NULL){
        if(value == current->getRight()->getInformation()){
            cout << "This value exists!" << endl;
            return current;
        }
    }
    if(value < current->getLow()){
            if(current->getLeftGroup() != NULL){
                current = search(current->getLeftGroup(), value);
                return current;
            }
        }
    else if(value > current->getLow() && value < current->getHigh()){
        if(current->getMiddleGroupLeft() != NULL){
            current = search(current->getMiddleGroupLeft(), value);
            return current;
            
        }
        else if(current->getMiddleGroupRight() != NULL){
            current = search(current->getMiddleGroupRight(), value);
            return current;
            
        }
    }
    else if(value > current->getHigh()){
          if(current->getRightGroup() != NULL){
            current = search(current->getRightGroup(), value);
            return current;
        }
    }
    
    cout << "This value doesn't exist" << endl;
    return NULL;
}

//following a similar traversal path to the search function, this function prints out the tree.
void print(Group* current, int count){
    if(count == 0 && current == NULL){
        cout << "The tree is empty" << endl;
        return;
    }
    if(current->getLeftGroup() != NULL){
        print(current->getLeftGroup(), count+1);
    }

    if(current->getLeft() != NULL){
        for(int i = 0; i < count; i++){
            cout << '\t';
        }
        cout << current->getLeft()->getInformation() <<endl;
    }
    if(current->getMiddleGroupLeft() != NULL){
        print(current->getMiddleGroupLeft(), count + 1);
    }
    if(current->getMiddle() != NULL){
        for(int i = 0; i < count; i++){
            cout << '\t';
        }
        cout << current->getMiddle()->getInformation() << endl;
    }


    if(current->getMiddleGroupRight() != NULL){
        print(current->getMiddleGroupRight(), count+1);
    }
    if(current->getRight() != NULL){
        for(int i = 0; i < count; i++){
            cout << '\t';
        }
        cout << current->getRight()->getInformation() << endl;
    }
    if(current->getRightGroup() != NULL){
        print(current->getRightGroup(), count + 1);
    }
}