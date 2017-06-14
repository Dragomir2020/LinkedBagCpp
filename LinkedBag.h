
//////////////////////////
//FILE NAME: LinkedBag.h//
//////////////////////////

////////////////
//Contributers//
////////////////

///////////////////////////////////////////////

// NAME                   DATE           CHANGE
// Dillon Dragomir        07-14-2017     Class structure for Linked Bag
// Andrew Piment          07-14-2017     Class structure for Linked Bag

///////////////////////////////////////////////

////////////////
//DEPENDANCIES//
////////////////

#ifndef LINKED_BAG_
#define LINKED_BAG_

#include "BagInterface.h"
#include "Node.h"

using namespace std;

class LinkedBag : public BagInterface
{
private:
   Node* headPtr;           // Pointer to first node
   int itemCount;           // Current count of bag items

   // Returns either a pointer to the node containing a given entry
   // or the null pointer if the entry is not in the bag.
   Node* getPointerTo(const int& target) const;
   Node* getPos(const int& index) const;

public:
   LinkedBag();     // Default constructor
   LinkedBag(const LinkedBag& aBag); // Copy constructor
   virtual ~LinkedBag();                       // Destructor should be virtual
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(const int& newEntry);   // Adds to the begining of the list
   bool remove(const int& anEntry);
   void clear();
   bool contains(const int& anEntry) const;
   int getFrequencyOf(const int& anEntry) const;
   vector<int> toVector() const;
   int getAt(const int& pos) const;    // Gets the value at the given position
   void setAt(const int& value, const int& pos);   // Sets the value at the given position
   bool insert(const int& value, const int& pos);	// Inserts a node at the given position
   void push_back(const int& value);    // Adds the value at the end of the list
   void pop_front();    // Removes the first element in the list
   void pop_back();     // Removes the last element in the list
   LinkedBag reverse() const;   // Reverse the given list
}; // end LinkedBag

#endif
