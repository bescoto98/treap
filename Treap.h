/**
Brenda Escoto
escot105@mail.chapman.edu
May 17, 2019
**/


#include <iostream>
#include <cstdlib>

using namespace std;

struct Node
{
  int key, priority;
  Node *left;
  Node *right;
  Node *prev;
};

class Treap
{

public:
  Treap();
  ~Treap();

  Node* root;
  Node* recent;
  bool pNode;
  bool priorities[100];//to prevent a priority being given more than once

  bool insert(int k);//the function main will call
  Node* insert(int k, Node* curr);
  void fixRoot(Node* curr);//helper for insert
  void checkPriority();//checks newest node for heap violation
  void printNode(Node* v);
  bool search(int k); //will return true if node exists in tree
  bool search(int k, Node* root);
  bool remove(int k);
  Node* newNode(int key);
  void printTreap();
  void printTreap(Node* root);
  void loadedRotation(Node* y);//rotation with children
  void destroy(Node *victim);//called in destructor
};
