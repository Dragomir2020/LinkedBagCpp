///////////////////////////
//FILE NAME: ArrayBag.cpp//
///////////////////////////

////////////////
//Contributers//
////////////////

///////////////////////////////////////////////

// NAME                   DATE           CHANGE
// Dillon Dragomir        07-14-2017     Member functions for node class
// Andrew Piment          07-14-2017     Member functions for node class

///////////////////////////////////////////////

////////////////
//DEPENDANCIES//
////////////////

#include "Node.h"

Node::Node() : next(nullptr)
{
} // end default constructor

Node::Node(const int& aData) : data(aData), next(nullptr)
{
} // end constructor

Node::Node(const int& aData, Node* nextNodePtr) :
                data(aData), next(nextNodePtr)
{
} // end constructor

void Node::setItem(const int& aData)
{
   data = aData;
} // end setItem

void Node::setNext(Node* nextNodePtr)
{
   next = nextNodePtr;
} // end setNext

int Node::getItem() const
{
   return data;
} // end getItem

Node* Node::getNext() const
{
   return next;
} // end getNext
