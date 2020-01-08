/**
Brenda Escoto
escot105@mail.chapman.edu
May 17, 2019
**/


#include "Treap.h"

Treap::Treap()
{
  root=NULL;
  recent=NULL;
  pNode=false;

  for(int i=0;i<100;++i)
  {
    priorities[i]=false;
  }

}

Treap::~Treap()
{
  destroy(root);
  delete recent;
  cout << "end of line" << endl;
}

void Treap::destroy(Node* v)
{
  if(v==NULL)
  {
    return;
  }
  else
  {
    destroy(v->left);
    destroy(v->right);
    delete v;
  }
  return;
}

void Treap::printNode(Node* x)
{

  if(x==root)
  {
    cout << "\t**ROOT**" << endl;
  }
  cout << "\t"<<x->key << "|" << x->priority << endl;
  if(x!=root)
  {
    cout << "PREVIOUS NODE: " << x->prev->key << endl;
  }
  if(x->left!=NULL)
  {
    cout << "LEFT CHILD: " << x->left->key << endl;
  }
  if(x->right!=NULL)
  {
    cout << "RIGHT CHILD: " << x->right->key << endl;
  }
  pNode=false;
}

bool Treap::search(int k)//function main will call
{
  pNode=true;
  return search(k, root);
}

bool Treap::search(int k, Node* curr)
{
  if(curr==NULL)//since root is passed first, this means that there's nothing in the treap
  {
    return false;
  }
  if(curr->key==k)//found it
  {
    if(pNode)
    {
      printNode(curr);
    }
    return true;
  }
  else //search next node
  {
    if(curr->key > k)
    {
      search(k, curr->left);
    }
    else if(curr->key < k)
    {
      search(k, curr->right);
    }
  }

}

void Treap::loadedRotation(Node* y)
{
  Node* x = y->prev;
  Node* p = x->prev;

  //x can move down freely
  if(x->key > y->key && y->right==NULL||x->key < y->key && y->left==NULL)
  {
    //y->prev = x
    y->prev = p;

    //parent->L/R=x, x is a child of parent
    if(p->left==x)
    {
      p->left=y;
    }
    if(p->right==x)
    {
      p->right=y;
    }

    //x->L/R=y, y is a child of x
    if(x->key < y->key)
    {
      y->left = x;
      //y->right = NULL;
    }
    if(x->key > y->key)
    {
      y->right = x;
      //y->left=NULL;
    }

    //x is now a child of y
    x->prev = y;

    //y is no longer a child of x
    if(x->left==y)
    {
      x->left=NULL;
    }
    if(x->right==y)
    {
      x->right=NULL;
    }

    //if heap rule is still being violated
    if(y->priority > p->priority)
    {
      loadedRotation(y);
    }
    return;
  }

  y->prev=p;
  if(p->left==x)
  {
    p->left=y;
  }
  if(p->right==x)
  {
    p->right=y;
  }

  if(x->left==y)
  {
    x->left=NULL;
  }
  if(x->right==y)
  {
    x->right=NULL;
  }
  //else: y has children we have to worry about
  Node* grandchild;

  if(x->key > y->key)//x will need to be a right child
  {
    grandchild=y->right;
    while(true)
    {
      if(grandchild->right==NULL)
      {
        break;
      }
      grandchild=grandchild->right;
    }
    grandchild->right=x;
  }
  else if(x->key < y->key)//x will need to be a left child
  {
    grandchild=y->left;
    while(true)
    {
      if(grandchild->left==NULL)
      {
        break;
      }
      grandchild=grandchild->left;
    }
    grandchild->left=x;
  }

  x->prev=grandchild;

  //ad infinitum aka til it sticks
  if(x->priority > grandchild->priority)
  {
    loadedRotation(x);
  }


  return;
}

void Treap::fixRoot(Node* curr)
{

  Node* temp=root;

  //changing pointers to new root so that we don't have an infinite loop
  if(curr->prev->left==curr)
  {
    curr->prev->left=NULL;
  }
  if(curr->prev->right==curr)
  {
    curr->prev->right=NULL;
  }

  curr->prev=NULL;

  if(curr->left!=NULL||curr->right!=NULL)//if it's not a leaf we've got an issue
  {
    cout << "Error" << endl;
    return;
  }

  root=curr;

  if(root->key < temp->key)
  {
    root->right=temp;
  }
  if(root->key > temp->key)
  {
    root->left=temp;
  }
  temp->prev=root;
}

void Treap::checkPriority()
{
  Node* temp=root;

  if(recent==root) //only node
  {
    return;
  }
  //recent does not have ->prev so we're going to find it
  while(true)
  {
    if(recent->key==temp->key)
    {
      break;
    }
    if(recent->key > temp->key)
    {
      temp=temp->right;
    }
    if(recent->key < temp->key)
    {
      temp=temp->left;
    }
  }

  if(temp->priority > root->priority)
  {

    fixRoot(temp);
    return;
  }

  //not root and rotation needed
  if(temp->priority > temp->prev->priority)
  {
    loadedRotation(temp);
  }
}

bool Treap::insert(int k)
{
  if(search(k, root))//if true
  {
    cout << "Value exists already." << endl;
    return false;
  }
  else
  {
    insert(k,root);
    checkPriority();
    return true;
  }
}

Node* Treap::insert(int k, Node* curr)
{
  if(curr==NULL)
  {
    curr = newNode(k);
    if(root==NULL)
    {
      root=curr;
    }
    recent=curr;
  }

  if(k < curr->key)//k smaller than currrent key
  {
    curr->left = insert(k, curr->left);
    curr->left->prev = curr;
  }
  else if(k > curr->key)//larger than
  {
    curr->right = insert(k, curr->right);
    curr->right->prev=curr;
  }

  return curr;
}

void Treap::printTreap()
{
  cout << "\tKEY|PRIORITY" << endl;
  printTreap(root);
}

void Treap::printTreap(Node* curr)
{

  if(curr==NULL)
  {
    cout << "\n";
    return;
  }
  printTreap(curr->left);

  //information
  if(curr==root)
  {
    cout << "\t**ROOT**" << endl;
  }
  cout << "\t"<<curr->key << "|" << curr->priority << endl;
  if(curr!=root)
  {
    cout << "PREVIOUS NODE: " << curr->prev->key << endl;
  }
  if(curr->left!=NULL)
  {
    cout << "LEFT CHILD: " << curr->left->key << endl;
  }
  if(curr->right!=NULL)
  {
    cout << "RIGHT CHILD: " << curr->right->key << endl;
  }
  printTreap(curr->right);
}

bool Treap::remove(int k)//only one function bc no recursion needed
{
  if(search(k, root))//exists in tree
  {
    /**
    Steps to remove node:

    1. Find node in Treap
    2.
      a. Best case: node is leaf
          i. remove parent's pointer to node
          ii. null it's prev pointer
      b. Root case: node is root
          i. choose whichever of its children has the highest priority
          ii. set child as the new root
          iii. null prev pointer of new root
          iii. if there is another child, make it a child of the new root
          iv. set pointer of child to new root
      c. Worst case: node is child and has children
          i. just cry
    3. delete node
    **/

    Node* temp=root;

    //find node in tree
    while(true)
    {
      if(temp->key==k)//temp has been found
      {
        break;
      }
      else
      {
        if(temp->key < k)
        {
          temp=temp->right;
        }
        if(temp->key > k)
        {
          temp=temp->left;
        }
      }
    }


    Node* rKid=temp->right;
    Node* lKid=temp->left;
    Node* parent=temp->prev;

    //best case
    if(lKid==NULL&&rKid==NULL)
    {
      if(parent->left==temp)
      {
        parent->left=NULL;
      }
      if(parent->right==temp)
      {
        parent->right=NULL;
      }
      temp->prev=NULL;
      delete temp;
      return true;
    }
    //end best case


    //root case
    if(temp->key==root->key)
    {
      //choose new root
      if(lKid==NULL||lKid->priority < rKid->priority)
      {
        root = rKid;
        if(root->left==NULL)
        {
          root->left=lKid;
        }
        else//new root has a child
        {
          while(true)
          {
            if(rKid->left==NULL)
            {
              rKid->left=lKid;
              break;
            }
            rKid=rKid->left;
          }
        }
      }
      else if(rKid==NULL||lKid->priority > rKid->priority)
      {
        root = lKid;
        if(root->right==NULL)
        {
          root->right=rKid;
        }
        else
        {
          while(true)
          {
            if(lKid->right==NULL)
            {
              lKid->right=rKid;
              break;
            }
            lKid=lKid->right;
          }
        }
      }

      root->prev=NULL;
      delete temp;
      return true;
    }
    //end root case


    //worst case
    bool leftPromoted;

    //parent-child relationships
    if(parent->left==temp)//temp was left node
    {
      if(lKid->priority > rKid->priority)
      {
        parent->left=lKid;
        lKid->prev=parent;
        leftPromoted=true;
      }
      if(lKid->priority < rKid->priority)
      {
        parent->left=rKid;
        rKid->prev=parent;
        leftPromoted=false;
      }
    }
    else if(parent->right==temp)//temp was right node
    {
      if(lKid->priority > rKid->priority)
      {
        parent->right=lKid;
        lKid->prev=parent;
        leftPromoted=true;
      }
      if(rKid->priority > lKid->priority)
      {
        parent->right=rKid;
        rKid->prev=parent;
        leftPromoted=false;
      }
    }
    //left-right relationships
    if(leftPromoted)
    {
      loadedRotation(rKid);
    }
    else
    {
      loadedRotation(lKid);
    }
    delete temp;
    return true;
  }
  else
  {
    cout << "Error, value does not exist in tree." << endl;
    return false;
  }
}


Node* Treap::newNode(int k)
{
  Node *tempNode = new Node;
  int p;
  tempNode->key=k;

  while(true)
  {
    p=rand()%100+1;//1-100
    if(priorities[p-1]==false)//find a priority that's empty
    {
      priorities[p-1]=true;
      break;
    }
  }

  tempNode->priority=p;
  tempNode->left=NULL;
  tempNode->right=NULL;

  return tempNode;
}
