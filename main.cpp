//https://www.cs.princeton.edu/~dpw/courses/cos326-12/ass/2-3-trees.pdf

#include <iostream>
#include <cstring>
#include "Node.h"
#include "Group.h"
#include <vector>
#include <fstream>

using namespace std;

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

int main(){
    Group* root = NULL;
    bool stillRunning = true;
    while(stillRunning == true){
       
        cout << "What would you like to do? ADD, REMOVE, SEARCH, PRINT, or QUIT" << endl; 
        char choice[50];
        cin.get(choice, 50);
        cin.get();

        if(strcmp(choice, "ADD") == 0){
            char input[50];
            char method;
            cout << "Would you like to enter by file (f) or by console (c)? " << endl;
            cin >> method;
            cin.get();
            if(method == 'c'){
                cout << "How many numbers will you be entering? " << endl;
                int numNums;
                cin >> numNums;
                cin.get();
                cout << "Enter your string of numbers: " << endl;
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

        }
        else if(strcmp(choice, "REMOVE") == 0){
            int value;
            cout << "What number would you like to remove? " << endl;
            cin >> value;
            cin.get();
            //remove
            removeMechanics(root, search(root, value), value);
        }
        else if(strcmp(choice, "SEARCH") == 0){
            int value;
            cout << "What number would like to search for? " << endl;
            cin >> value;
            cin.get();
            search(root, value);
        }
        else if(strcmp(choice, "PRINT") == 0){
            print(root, 0);
        }
        else if(strcmp(choice, "QUIT") == 0){
            stillRunning = false;
        }
    }
}

Group* findSuccessor(Group* current, int value){
    Group* successor = current;

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
    if(current->getRightGroup() != NULL){
        successor = current->getRightGroup();
        while(successor->getLeftGroup() != NULL){
            successor = successor->getLeftGroup();
        }
    }
    cout << "IN SUCCESSOR" << endl;
    cout << successor->getMiddle()->getInformation() << endl;
    return successor;

}

void caseOne(Group* &root, Group* current){
    cout << "Made it in" << endl;
    cout << "Current values" << endl;
    cout << current->getSiblingGroup()->getHigh() << endl;
    cout << current->getSiblingGroup()->getLow() << endl;
    if(current == current->getParentGroup()->getLeftGroup()){
        cout << "1 IN HERE" << endl;
        current->getSiblingGroup()->setLeft(current->getParentGroup()->getMiddle());
        current->getSiblingGroup()->setLow(current->getSiblingGroup()->getLeft()->getInformation());
        current->getSiblingGroup()->setMiddleGroupLeft(current->getSiblingGroup()->getLeftGroup());
        current->getSiblingGroup()->setLeftGroup(current->getMiddleGroup());

    }
    else if(current == current->getParentGroup()->getRightGroup()){
        cout << "2 IN HERE" << endl;
         cout << current->getSiblingGroup()->getHigh() << endl;
        cout << current->getSiblingGroup()->getLow() << endl;
        current->getSiblingGroup()->setRight(current->getParentGroup()->getMiddle());
        cout << current->getParentGroup()->getMiddle()->getInformation() << endl;
        current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getRight()->getInformation());
        current->getSiblingGroup()->setMiddleGroupLeft(current->getSiblingGroup()->getRightGroup());
        current->getSiblingGroup()->setRightGroup(current->getMiddleGroup());
        
        cout << "OOP: " << current->getSiblingGroup()->getHigh() << endl;
        cout << "SY: " << current->getSiblingGroup()->getLow() << endl;
    }
    if(current->getMiddleGroup() != NULL){
        current->getMiddleGroup()->setParentGroup(current->getSiblingGroup());
    }

    cout << current->getSiblingGroup()->getHigh() << endl;
    cout << current->getSiblingGroup()->getLow() << endl;
    cout << "3" << endl;
    current->getSiblingGroup()->setNumNodes(2);
    cout << "4" << endl;
    cout << current->getParentGroup()->getMiddle()->getInformation() << endl;
    cout << current->getMiddle()->getInformation() << endl;
    current->getParentGroup()->setMiddle(current->getMiddle());
    cout << "5" << endl;
    current->getParentGroup()->setMiddleGroupLeft(current->getSiblingGroup());
    if(current->getParentGroup()->getMiddleGroupLeft() != NULL){
        current->getParentGroup()->getMiddleGroupLeft()->setParentGroup(current->getParentGroup());
    }

    cout << "6" << endl;
    Group* temp = current->getParentGroup();
    cout << "7" << endl;
    current->getParentGroup()->setLeftGroup(NULL);
    cout << "8" << endl;
    current->getParentGroup()->setRightGroup(NULL);
    cout << "9" << endl;
    cout << "HERE" << endl;
    callCases(root, temp);
}

void caseTwo(Group* &root, Group* current){
    current->getMiddle()->setInformation((current->getParentGroup()->getMiddle()->getInformation()));
    if(current == current->getParentGroup()->getLeftGroup()){
        cout << "Firstly in here" << endl;
        current->getParentGroup()->getMiddle()->setInformation(current->getSiblingGroup()->getLow());
        cout << "Made it here" << endl;
        if(current->getSiblingGroup()->getLeft() != NULL && current->getSiblingGroup()->getLeft()->getInformation() == current->getSiblingGroup()->getLow()){
            cout << "entered this" << endl;
            current->getSiblingGroup()->setLeft(NULL);
            
        }
        else{
            cout << "no this one" << endl;
            current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getRight());
            current->getSiblingGroup()->setRight(NULL);
            
        }
        cout << "out here" << endl;
        current->getSiblingGroup()->setLow(current->getSiblingGroup()->getMiddle()->getInformation());
        current->setLeftGroup(current->getMiddleGroupLeft());
        current->setMiddleGroupLeft(NULL);
        cout << "Whoop" << endl;
        current->setRightGroup(current->getSiblingGroup()->getLeftGroup());
        if(current->getRightGroup() != NULL){
            current->getRightGroup()->setParentGroup(current);
        }
        current->getSiblingGroup()->setLeftGroup(current->getSiblingGroup()->getMiddleGroup());
        cout << "OUT" << endl;
        
    }
    else if(current == current->getParentGroup()->getRightGroup()){
        cout << "This one" << endl;
        current->getParentGroup()->getMiddle()->setInformation(current->getSiblingGroup()->getHigh());
        cout << "Past this" << endl;
        if(current->getSiblingGroup()->getRight() != NULL && current->getSiblingGroup()->getRight()->getInformation() == current->getSiblingGroup()->getHigh()){
            cout << "HELLO" << endl;
            current->getSiblingGroup()->setRight(NULL);
        }
        else{
            cout << "Vibes" << endl;
            current->getSiblingGroup()->setMiddle(current->getSiblingGroup()->getLeft());
            current->getSiblingGroup()->setLeft(NULL);
        }
        cout << "Sweet Caroline" << endl;
        current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getMiddle()->getInformation());
        current->setRightGroup(current->getMiddleGroupLeft());
        current->setMiddleGroupLeft(NULL);
        cout << "HERE" << endl;
        current->setLeftGroup(current->getSiblingGroup()->getRightGroup());
        if(current->getSiblingGroup()->getRightGroup() != NULL){
            current->getSiblingGroup()->setParentGroup(current);
        }
        current->getSiblingGroup()->setRightGroup(current->getSiblingGroup()->getMiddleGroup());
        cout << "RAHHH" << endl;
    }
    if(current->getSiblingGroup()->getMiddleGroupLeft() != NULL){
        current->getSiblingGroup()->setMiddleGroupLeft(NULL);
    }
    else{
        current->getSiblingGroup()->setMiddleGroupRight(NULL);
    }
    current->getParentGroup()->setHigh(current->getParentGroup()->getMiddle()->getInformation());
    current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
    current->setHigh(current->getMiddle()->getInformation());
    current->setLow(current->getMiddle()->getInformation());
    current->getSiblingGroup()->setNumNodes(1);
    cout << "DONE" << endl;

}

void caseThree(Group* &root, Group* current){
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

void caseFour(Group* &root, Group* current){
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

void caseFive(Group* &root, Group* current){
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
    current->setHigh(current->getMiddle()->getInformation());
    current->setLow(current->getMiddle()->getInformation());
    current->getSiblingGroup()->setNumNodes(1);
    current->getSiblingGroup()->setHigh(current->getSiblingGroup()->getMiddle()->getInformation());
    current->getSiblingGroup()->setLow(current->getSiblingGroup()->getMiddle()->getInformation());
}

void caseSix(Group* &root, Group* current){
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

void callCases(Group* &root, Group* current){
    print(root, 0);
    cout << "Let's call some cases" << endl;
    if(current == root){
        cout << "YOOO" << endl;
    }
    if(current == root){
        cout << "IG Case 0? " << endl;
        root = current->getMiddleGroup();
        cout << current->getHigh() << endl;
        cout << current->getLow() << endl;
        current->setMiddleGroupLeft(NULL);
        root->setParentGroup(NULL);
        delete current;
        return;
    }
    if(current->getParentGroup()->getNumNodes() == 1 && current->getSiblingGroup()->getNumNodes() == 1){
        cout << "Case 1 " << endl;
        caseOne(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 1 && current->getSiblingGroup()->getNumNodes() == 2){
        cout << "Case 2" << endl;
        caseTwo(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 2 && current->getSiblingGroup()->getNumNodes() == 1){
        cout << "Case 3" << endl;
        caseThree(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 2 && current->getParentGroup()->getMiddleGroup() == current && (current->getParentGroup()->getLeftGroup()->getNumNodes() == 1 || current->getParentGroup()->getRightGroup()->getNumNodes() == 1)){
        cout << "Case 4" << endl;
        caseFour(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 2 && current->getSiblingGroup()->getNumNodes() == 2){
        cout << "Case 5" << endl;
        caseFive(root, current);
        return;
    }
    else if(current->getParentGroup()->getNumNodes() == 2 && current->getParentGroup()->getMiddleGroup() == current && (current->getParentGroup()->getLeftGroup()->getNumNodes() == 2 || current->getParentGroup()->getRightGroup()->getNumNodes() == 2)){
        cout << "Case 6 " << endl;
        caseSix(root, current);
        return;
    }
}


void removeMechanics(Group* &root, Group* currentInitial, int value){
    if(root->getMiddle()->getInformation() == value && root->getNumNodes() == 1){
        root = NULL;
        cout << "The tree is empty" << endl;
        return;
    }
    cout << "ENTERED HERE" << endl;
    cout << currentInitial->getNumNodes() << endl;
    cout << currentInitial->getMiddle()->getInformation() << endl;
    Group* current = findSuccessor(currentInitial, value);
    cout << current->getMiddle()->getInformation() << endl;
    if(current != currentInitial){
        cout << "RUNNING THIS AT ALL?  " << endl;
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
    if(current->getNumNodes() == 2){
        cout << "Woho1 " << endl;
        cout << "CURRENT INFORMATION: " << current->getMiddle()->getInformation() << endl;
        cout << "VALUE: " << value << endl;
        if(current->getMiddle()->getInformation() == value){
            if(current->getLeft() != NULL){
                cout << "THIS ONE" << endl;
                current->setHigh(current->getLeft()->getInformation());
                current->setMiddle(current->getLeft());
                current->setLeft(NULL);
            }
            else{
                cout << "THIS TWO" << endl;
                current->setLow(current->getRight()->getInformation());
                cout << current->getRight()->getInformation() << endl;
                current->setMiddle(current->getRight());
                cout << current->getMiddle()->getInformation() << endl;
                current->setRight(NULL);
            }
        }
        else if (current->getMiddle()->getInformation() > value){
            cout << "THIS THREE" << endl;
            current->setLeft(NULL);
            current->setLow(current->getMiddle()->getInformation());
        }
        else{
            cout << "THIS FOUR" << endl;
            current->setRight(NULL);
            current->setHigh(current->getMiddle()->getInformation());
        }
        current->setNumNodes(1);
    }
    else if(current->getNumNodes() == 1){
        cout << "woHo2" << endl;
        if(current->getParentGroup()->getNumNodes() == 1){
            //parent has 1 node
            cout << "Parent 1" << endl;
            cout << current->getParentGroup()->getMiddle()->getInformation() << endl;
            if(current->getSiblingGroup()->getNumNodes() == 2){
                cout << "This version" << endl;
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
            else if(current->getSiblingGroup()->getNumNodes() == 1){
                cout << "Cool kids" << endl;
                callCases(root, current);
            }

            

        }
        else if(current->getParentGroup()->getNumNodes() == 2){
            cout << "2 numNodes" << endl;
            cout << current->getParentGroup()->getMiddle()->getInformation() << endl;
            //parent has 2 nodes
            if(current == current->getParentGroup()->getLeftGroup()){
                cout << "THIS THE ISSUE?" << endl;
                

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

                        cout << "this" << endl;
                        current->getSiblingGroup()->setLeft(current->getParentGroup()->getMiddle());
                        current->getParentGroup()->setMiddle(current->getParentGroup()->getRight());
                        current->getParentGroup()->setRight(NULL);
                    }
                    else{
                        cout << "This" << endl;
                        current->getSiblingGroup()->setLeft(current->getParentGroup()->getLeft());
                        cout << current->getParentGroup()->getLeft()->getInformation() << endl;
                        current->getParentGroup()->setLeft(NULL);
                    }
                    cout << "RUNNING THIS " << endl;
                    current->getSiblingGroup()->setLow(current->getSiblingGroup()->getLeft()->getInformation());
                    cout << "1" << endl;
                    current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
                    cout << "2" << endl;
                    current->getParentGroup()->setNumNodes(1);
                    current->getSiblingGroup()->setNumNodes(2);
                    cout << "3" << endl;
                    current->getParentGroup()->setLeftGroup(current->getSiblingGroup());
                    cout << "4" << endl;
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
            cout << "GETTING HERE? " << endl;
            if(current == current->getParentGroup()->getRightGroup()){
                cout << "FOUND THIS PLACE" << endl;
                if(current == current->getParentGroup()->getRightGroup()){
                    if(current->getSiblingGroup()->getNumNodes() == 2){
                        if(current->getParentGroup()->getRight()->getInformation() == current->getParentGroup()->getHigh()){
                            current->setMiddle(current->getParentGroup()->getRight());
                            cout << "IN HERE" << endl;
                            cout << "NUM: " << current->getParentGroup()->getRight()->getInformation() << endl;
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
                        cout << "RUNNING THIS " << endl;
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
                cout << "We're entering this version?" << endl; 
                if(current->getParentGroup()->getLeftGroup()->getNumNodes() == 2){
                    cout << "SHould be entering this" << endl;
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
                    cout << "STILL ISSUE" << endl;
                    current->getParentGroup()->setLow(current->getParentGroup()->getLeftGroup()->getHigh());
                    if(current->getParentGroup()->getLeftGroup()->getRight() != NULL){
                        current->getParentGroup()->getLeftGroup()->setRight(NULL);
                    }
                    else{
                        current->getParentGroup()->getLeftGroup()->setMiddle(current->getParentGroup()->getLeftGroup()->getLeft());
                        current->getParentGroup()->getLeftGroup()->setLeft(NULL);
                    }
                    cout << "NOT YET" << endl;
                    current->getParentGroup()->getLeftGroup()->setHigh(current->getParentGroup()->getLeftGroup()->getMiddle()->getInformation());
                }
                else if(current->getParentGroup()->getRightGroup()->getNumNodes() == 2){
                    cout << "NO THIS ONE" << endl;
                    current->getParentGroup()->getRightGroup()->setNumNodes(1);
                    current->getMiddle()->setInformation(current->getParentGroup()->getHigh());
                    current->setLow(current->getParentGroup()->getHigh());
                    current->setHigh(current->getParentGroup()->getHigh());
                    cout << "SUMMER VIBES" << endl;
                    if(current->getParentGroup()->getRight() != NULL){
                        current->getParentGroup()->getRight()->setInformation(current->getParentGroup()->getRightGroup()->getLow());
                    }
                    else{
                        current->getParentGroup()->getMiddle()->setInformation(current->getParentGroup()->getRightGroup()->getLow());
                    }
                    cout << "CUZ HOW MANY COUTS" << endl;
                    cout << current->getParentGroup()->getRightGroup()->getNumNodes() << endl;
                    current->getParentGroup()->setHigh(current->getParentGroup()->getRightGroup()->getLow());
                    if(current->getParentGroup()->getLeftGroup()->getRight() == NULL){
                        current->getParentGroup()->getRightGroup()->setLeft(NULL);
                    }
                    else{
                        current->getParentGroup()->getRightGroup()->setMiddle(current->getParentGroup()->getRightGroup()->getRight());
                        current->getParentGroup()->getRightGroup()->setRight(NULL);
                    }
                    cout << "DOES A WISE MAN NEED" << endl;
                    cout << current->getParentGroup()->getRightGroup()->getNumNodes() << endl;
                    cout << current->getParentGroup()->getRightGroup()->getMiddle()->getInformation() << endl;
                    current->getParentGroup()->getRightGroup()->setLow(current->getParentGroup()->getRightGroup()->getMiddle()->getInformation());
                    cout << "SOMETHING WRONG WITH THIS?" << endl;
                }
                else{
                    cout << "HERE" << endl;
                    Node* temp = new Node();
                    temp->setInformation(current->getParentGroup()->getLow());
                    current->getParentGroup()->getLeftGroup()->setRight(temp);
                    current->getParentGroup()->getLeftGroup()->setHigh(temp->getInformation());
                    current->getParentGroup()->getLeftGroup()->setNumNodes(2);
                    current->getParentGroup()->setNumNodes(1);
                    if(current->getParentGroup()->getMiddle()->getInformation() == current->getParentGroup()->getLow()){
                        cout << "THIS? " << endl;
                        current->getParentGroup()->setMiddle(current->getParentGroup()->getRight());
                        current->getParentGroup()->setRight(NULL);
                    }
                    else{
                        cout << "OR THAT" << endl;
                        current->getParentGroup()->setLeft(NULL);
                    }
                    current->getParentGroup()->setLow(current->getParentGroup()->getMiddle()->getInformation());
                    if(current->getParentGroup()->getMiddleGroupLeft() != NULL){
                        cout << "THIS ONE" << endl;
                        current->getParentGroup()->setMiddleGroupLeft(NULL);
                    }
                    else{
                        cout << "OR THAT ONE" << endl;
                        current->getParentGroup()->setMiddleGroupRight(NULL);
                    }
                    delete current;
                }
            }
        }
    }
}



void add(Group* &root, Group* current, Node* newNode){
    //if root is null
    if(root == NULL){
        cout << "IN HERE, ROOT IS NULL" << endl;
        root = new Group();
        root->setMiddle(newNode);
        root->setNumNodes(1);
        root->setLow(newNode->getInformation());
        root->setHigh(newNode->getInformation());
    }
    //if root isn't null
    else{
        cout << "Inside here" << endl;
        cout << newNode->getInformation() << " : NEW NODE" << endl;
        cout << "HIGH: " << current->getHigh() << endl;
        cout << "LOW: " << current->getLow() << endl;
        //traversing to correct location in tree
        if(newNode->getInformation() < current->getLow()){
            if(current->getLeftGroup() != NULL){
                cout << "1" << endl;
                add(root, current->getLeftGroup(), newNode);
                return;
            }
        }
        else if(newNode->getInformation() > current->getLow() && newNode->getInformation() < current->getHigh()){
            if(current->getMiddleGroupLeft() != NULL){
                cout << "2" << endl;
                add(root, current->getMiddleGroupLeft(), newNode);
                return;
            }
            else if(current->getMiddleGroupRight() != NULL){
                cout << "3" << endl;
                add(root, current->getMiddleGroupRight(), newNode);
                return;
            }
        }
        else if(newNode->getInformation() > current->getHigh()){
            if(current->getRightGroup() != NULL){
                cout << "4" << endl;
                add(root, current->getRightGroup(), newNode);
                return;
            }
        }
        //if there's only one node, just adding it in. 
        cout << "No Traversal" << endl;
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
            cout << "There are two nodes" << endl;
            cout << current->getMiddle()->getInformation() << "Mid" << endl;
            cout << current->getNumNodes() << ": Nodes" << endl;
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
            fixTree(root, current);
        }
    }
}

void fixTree(Group* &root, Group* current){
    cout << "Time to fix this tree" << endl;
    Group* left = new Group();
    Group* right = new Group();
    Group* parent;
    if(current->getParentGroup() == NULL){
        cout << "Parent is null" << endl;
        parent = new Group();
        root = parent;

    }
    else{
        parent = current->getParentGroup();
    }

    //has to be fixed
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
    left->setMiddle(current->getLeft());
    left->setLow(current->getLeft()->getInformation());
    left->setHigh(current->getLeft()->getInformation());
    right->setLow(current->getRight()->getInformation());
    right->setHigh(current->getRight()->getInformation());
    left->setNumNodes(1);
    right->setMiddle(current->getRight());
    right->setNumNodes(1);

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

Group* search(Group* current, int value){
    cout << "LOW: " << current->getLow() << endl;
    cout << "HIGH: " << current->getHigh() << endl;
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
        cout << current->getLeft()->getInformation() << "a"<<endl;
    }
    if(current->getMiddleGroupLeft() != NULL){
        print(current->getMiddleGroupLeft(), count + 1);
    }
    if(current->getMiddle() != NULL){
        for(int i = 0; i < count; i++){
            cout << '\t';
        }
        cout << current->getMiddle()->getInformation() <<"b"<< endl;
    }


    if(current->getMiddleGroupRight() != NULL){
        print(current->getMiddleGroupRight(), count+1);
    }
    if(current->getRight() != NULL){
        for(int i = 0; i < count; i++){
            cout << '\t';
        }
        cout << current->getRight()->getInformation() << "c" << endl;
    }
    if(current->getRightGroup() != NULL){
        print(current->getRightGroup(), count + 1);
    }
}