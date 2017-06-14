//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

///////////////////////////
//FILE NAME: ArrayBag.cpp//
///////////////////////////

////////////////
//Contributers//
////////////////

///////////////////////////////////////////////

// NAME                   DATE           CHANGE
// Dillon Dragomir        07-14-2017     Implemented Member Functions
// Andrew Piment          07-14-2017     Implemented Member Functions

///////////////////////////////////////////////

////////////////
//DEPENDANCIES//
////////////////

/** ADT bag: Link-based implementation.
    @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <cmath>
#include <stdexcept>

using namespace std;

LinkedBag::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

LinkedBag::LinkedBag(const LinkedBag& aBag)
{
	itemCount = aBag.itemCount;
   Node* origChainPtr = aBag.headPtr;  // Points to nodes in original chain

   if (origChainPtr == nullptr)
      headPtr = nullptr;  // Original bag is empty
   else
   {
      // Copy first node
      headPtr = new Node();
      headPtr->setItem(origChainPtr->getItem());

      // Copy remaining nodes
      Node* newChainPtr = headPtr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer

      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         int nextItem = origChainPtr->getItem();

         // Create a new node containing the next item
         Node* newNodePtr = new Node(nextItem);

         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);

         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while

      newChainPtr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

LinkedBag::~LinkedBag()
{
   clear();
}  // end destructor

bool LinkedBag::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

int LinkedBag::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

bool LinkedBag::add(const int& newEntry)
{
   // Add to beginning of chain: new node references rest of chain;
   // (headPtr is null if chain is empty)
   Node* nextNodePtr = new Node();
   nextNodePtr->setItem(newEntry);
   nextNodePtr->setNext(headPtr);  // New node points to chain
//   Node<ItemType>* nextNodePtr = new Node<ItemType>(newEntry, headPtr); // alternate code

   headPtr = nextNodePtr;          // New node is now first node
   itemCount++;

   return true;
}  // end add

vector<int> LinkedBag::toVector() const
{
   vector<int> bagContents;
   Node* curPtr = headPtr;
   int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
   {
		bagContents.push_back(curPtr->getItem());
      curPtr = curPtr->getNext();
      counter++;
   }  // end while

   return bagContents;
}  // end toVector

bool LinkedBag::remove(const int& anEntry)
{
   Node* entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
   if (canRemoveItem)
   {
      // Copy data from first node to located node
      entryNodePtr->setItem(headPtr->getItem());

      // Delete first node
      Node* nodeToDeletePtr = headPtr;
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;

      itemCount--;
   } // end if

	return canRemoveItem;
}  // end remove

void LinkedBag::clear()
{
   Node* nodeToDeletePtr = headPtr;
   while (headPtr != nullptr)
   {
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;

      nodeToDeletePtr = headPtr;
   }  // end while
   // headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
}  // end clear

int LinkedBag::getFrequencyOf(const int& anEntry) const
{
	int frequency = 0;
    int counter = 0;
    Node* curPtr = headPtr;
    while ((curPtr != nullptr) && (counter < itemCount))
    {
       if (anEntry == curPtr->getItem())
       {
          frequency++;
       } // end if

       counter++;
       curPtr = curPtr->getNext();
   } // end while

   return frequency;
}  // end getFrequencyOf

bool LinkedBag::contains(const int& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains

// Gets the value at the given position
int LinkedBag::getAt(const int& pos) const
{
	// Find the pointer to the wanted node
    Node* currentPtr = getPos(pos);

	// Get the value from the node
	return currentPtr->getItem();
}

// Sets the value at the given position
void LinkedBag::setAt(const int& value, const int& pos)
{
	// Find the pointer to the wanted node
	Node* currentPtr = getPos(pos);

	// Set the value to the wanted node
	currentPtr->setItem(value);
}

// Inserts a node at the given position
bool LinkedBag::insert(const int& value, const int& pos)
{
	// If the postion is not within the bag size
	if(pos < 0 || pos > getCurrentSize())
		return false;

	// If the bag is empty
	if(itemCount == 0)
	{
		// Set the new value to the head node
		headPtr = new Node(value,nullptr);
	}
	else
	{
		// Find the previous and next node
		Node* prevPtr = getPos(pos-1);
		Node* currentPtr = prevPtr->getNext();

		// Set the new node to be inbetween these nodes
		prevPtr->setNext(new Node(value,currentPtr));
	}

	// Increase the item count
	itemCount++;

	// Return the success
	return true;
}

// Adds the value at the end of the list
void LinkedBag::push_back(const int& value)
{
	// Insert a new value to the end of the bag
    insert(value,getCurrentSize());
}

// Removes the first element in the list
void LinkedBag::pop_front()
{
	// Find the first Node and the second node
	Node* tempPtr = headPtr;
	Node* nextPtr = tempPtr->getNext();

	// Delete the first node and set head pointer to the second node
    delete tempPtr;
	headPtr = nextPtr;

	// Decrease the item count
	itemCount--;
}

// Removes the last element in the list
void LinkedBag::pop_back()
{
	// FInd the last and second to last nodes
    Node* secondLastptr = getPos(getCurrentSize()-2);
	Node* tempPtr = secondLastptr->getNext();

	// Delete the last node and set next for the second to last node to nullptr
	delete tempPtr;
	secondLastptr->setNext(nullptr);

	// Decrease the item count
	itemCount--;
}

// Reverse the given list
LinkedBag LinkedBag::reverse() const
{
	// Create a new bag
	LinkedBag* nextBag = new LinkedBag();

	// Set each index in the old bag to the opposite position in the new bag
    for (int i = 1; i <= getCurrentSize(); i++)
	{
    	nextBag->push_back(getAt(getCurrentSize()-i));
    }

	// Return the new bag
	return *nextBag;
}

// private
// Returns either a pointer to the node containing a given entry
// or the null pointer if the entry is not in the bag.
Node* LinkedBag::getPointerTo(const int& anEntry) const
{
   bool found = false;
   Node* curPtr = headPtr;

   while (!found && (curPtr != nullptr))
   {
      if (anEntry == curPtr->getItem())
         found = true;
      else
         curPtr = curPtr->getNext();
   } // end while

   return curPtr;
} // end getPointerTo

Node* LinkedBag::getPos( const int& index) const
{
	// Get the inital variabes
	Node* currentPtr = headPtr;
	int length = getCurrentSize();

	// Check that the index is valid
	if( abs(index) > length)
		throw logic_error("Invalid Index");

	// If the index is negative, find the positive index equal to the given negative and look forward that many indecies
	if(index < 0)
	{
		for (int i = 0; i < length+index; i++)
		{
			currentPtr = currentPtr->getNext();
		}
	}
	// If the index is positive, look forward that many indecies
	else if(index > 0)
	{
		for (int i = 0; i < index; i++)
		{
			currentPtr = currentPtr->getNext();
		}
	}

	// Return the node pointer
	return currentPtr;
}
