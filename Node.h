#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;


class Node{
 public:

  Node();
  ~Node();
  //initializing variables

  //realistically I shouldn't need any of these, all I should need is a data holder - delete later.
  Node* parent;
  Node* left;
  Node* right;
  int data;
  //function prototypes
  void setRight(Node* newRight);
  void setLeft(Node* newLeft);
  Node* getRight();
  Node* getLeft();
  void setParent(Node* newparent);
  Node* getParent();
  void setInformation(int value);
  int getInformation();
 

};


#endif