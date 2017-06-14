
///////////////////////////////////
//FILE NAME: LinkedBagRecursive.h//
///////////////////////////////////

////////////////
//Contributers//
////////////////

///////////////////////////////////////////////

// NAME                   DATE           CHANGE
// Dillon Dragomir        07-14-2017     Class Declaration
// Andrew Piment          07-14-2017     Class Declaration

///////////////////////////////////////////////

////////////////
//DEPENDANCIES//
////////////////

#ifndef LINKED_BAG_RECURSIVE_
#define LINKED_BAG_RECURSIVE_

#include "BagInterface.h"
#include "Node.h"

using namespace std;

class LinkedBagRecursive : public BagInterface
{
private:
   Node* headPtr; // Pointer to first node
   int itemCount;           // Current count of bag items

   // Fills the vector bagContents with the data in the nodes of
   // the linked chain to which curPtr points.
   void fillVector(vector<int>& bagContents, Node* curPtr) const;

   // Locates a given entry within this bag.
   // Returns either a pointer to the node containing a given entry or
   // the null pointer if the entry is not in the bag.
   Node* getPointerTo(const int& target, Node* curPtr) const;

   // Counts the frequency of occurrence of a given entry in this bag.
   int countFrequency(const int& anEntry, int counter,
                      Node* curPtr) const;
   Node* findIndex(int index, Node* curPtr) const;
   //Node* findIndex(unsigned index, Node* curPtr) const;

   // Deallocates all nodes assigned to this bag
   void deallocate(Node* nextNodePtr);



public:
   LinkedBagRecursive();
   LinkedBagRecursive(const LinkedBagRecursive& aBag); // Copy constructor
   virtual ~LinkedBagRecursive();                       // Destructor should be virtual
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(const int& newEntry);
   bool remove(const int& anEntry);
   void clear();
   bool contains(const int& anEntry) const;
   int getFrequencyOf(const int& anEntry) const;
   vector<int> toVector() const;
   int getAt(const int& pos) const;    // Gets the value at the given position
   void setAt(const int& value, const int& pos);   // Sets the value at the given position
   bool insert(const int& value, const int& pos);		// Inserts a node at the given position
   void push_back(const int& value);    // Adds the value at the end of the list
   void pop_front();    // Removes the first element in the list
   void pop_back();     // Removes the last element in the list
   LinkedBagRecursive reverse() const;   // Reverse the given list
}; // end LinkedBagRecursive

#endif
