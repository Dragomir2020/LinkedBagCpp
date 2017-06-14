
/////////////////////
//FILE NAME: node.h//
/////////////////////

////////////////
//Contributers//
////////////////

///////////////////////////////////////////////

// NAME                   DATE           CHANGE
// Dillon Dragomir        07-14-2017     Node Class
// Andrew Piment          07-14-2017     Node CLass

///////////////////////////////////////////////

////////////////
//DEPENDANCIES//
////////////////

// LinkedList Node class

#ifndef NODE_
#define NODE_

class Node
{
private:
   int        data; // A data item
   Node*      next; // Pointer to next node
   
public:
   Node();  // Default Constructor
   Node(const int& aData);  // Overloaded constructor
   Node(const int& aData, Node* nextNodePtr); // Overloaded constructor
   void setItem(const int& aData);  // Set data
   void setNext(Node* nextNodePtr); // Set next node pointer
   int getItem() const ;    // get data
   Node* getNext() const ;  // get next node pointer
}; // end Node

#endif