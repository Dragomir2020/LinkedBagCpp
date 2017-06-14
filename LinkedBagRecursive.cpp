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

/** ADT bag: Link-based implementation - RECURSIVE VERSION.
    @file LinkedBagRecursive.cpp */

#include "LinkedBagRecursive.h"
#include "Node.h"
#include <iostream>
#include <cstddef>
#include <stdlib.h>

using namespace std;

LinkedBagRecursive::LinkedBagRecursive() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

LinkedBagRecursive::LinkedBagRecursive(const LinkedBagRecursive& aBag)
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

         origChainPtr = origChainPtr->getNext();  // Advance original-chain pointer

         // Create a new node containing the next item
         Node* newNodePtr = new Node(nextItem);

         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);

         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();
      }  // end while

      newChainPtr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

LinkedBagRecursive::~LinkedBagRecursive()
{
   clear();
}  // end destructor

bool LinkedBagRecursive::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

int LinkedBagRecursive::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

bool LinkedBagRecursive::add(const int& newEntry)
{
   // Add to beginning of chain: new node references rest of chain;
   // (headPtr is null if chain is empty)
   Node* nextNodePtr = new Node();
   nextNodePtr->setItem(newEntry);
   nextNodePtr->setNext(headPtr);  // New node points to chain

   headPtr = nextNodePtr;          // New node is now first node
   itemCount++;

   return true;
}  // end add

vector<int> LinkedBagRecursive::toVector() const
{
   vector<int> bagContents;
   fillVector(bagContents, headPtr);
   return bagContents;
}  // end toVector

bool LinkedBagRecursive::remove(const int& anEntry)
{
   Node* entryNodePtr = getPointerTo(anEntry, headPtr);
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

void LinkedBagRecursive::clear()
{
   deallocate(headPtr);
   headPtr = nullptr;
   itemCount = 0;
}  // end clear

int LinkedBagRecursive::getFrequencyOf(const int& anEntry) const
{
	return countFrequency(anEntry, 0, headPtr);
}  // end getFrequencyOf

bool LinkedBagRecursive::contains(const int& anEntry) const
{
	return (getPointerTo(anEntry, headPtr) != nullptr);
}  // end contains


//Your function definitions here (Your code here)
//Implement getAt, setAt, insert, push_back, pop_front, pop_back and reverse using recursive functions
// Gets the value at the given position
int LinkedBagRecursive::getAt(const int& pos) const
{
	// Aquire position for the node and switch negative value to a positive if given
	int length = getCurrentSize();
	if( abs(pos) > length)
		throw logic_error("Invalid Index");

	// if the position is negative find the positive equivalent
	int position;
	if (pos < 0)
		position = length + pos;
	else
		position = pos;

	// Get the head node
	Node* head = headPtr;

	// Find the pointer to the desired node
	Node* currentNode = findIndex(position, head);

	// Output the desired node value
 	return currentNode->getItem();
}

// Sets the value at the given position
void LinkedBagRecursive::setAt(const int& value, const int& pos)
{
	// Aquire position for the node and switch negative value to a positive if given
	int length = getCurrentSize();
	if( abs(pos) > length)
		throw logic_error("Invalid Index");

	// if the position is negative find the positive equivalent
	int position;
	if (pos < 0)
		position = length + pos;
	else
		position = pos;

	// Get the head node
	Node* head = headPtr;

	// Get the node to change the value and change it
	Node* currentNode = findIndex(position, head);
 	currentNode->setItem(value);
}

// Inserts a node at the given position
bool LinkedBagRecursive::insert(const int& value, const int& pos)
{
	// If the new position is between the head pointer within the current size
	if (pos >= 1 && pos <= getCurrentSize())
 	{
		// Get the head pointer and the nodes before and after where the new node will be placed
		Node* head = headPtr;
 		Node* prevNode = findIndex(pos-1,head);
 		Node* nextNode = prevNode->getNext();

		// Place the new node between the two curretn ones
 		prevNode->setNext(new Node(value, nextNode));

		// Increase your item count
		itemCount++;

		// Return true for a success
 		return true;
 	}
	// If the new position is the first
	else if (pos == 0)
	{
		// If the size is 0 have the next node a null else set the next node to the head pointer
		if (getCurrentSize() > 0)
			headPtr = new Node(value,headPtr);
		else
			headPtr = new Node(value,nullptr);

		// Increase your item count
		itemCount++;

		// Return true for a success
	 	return true;
	}
	// Else return false for failing
 	else
 		return false;
}

// Adds the value at the end of the list
void LinkedBagRecursive::push_back(const int& value)
{
   //  Enter a new value at the end of the list
   insert(value,getCurrentSize());
}

// Removes the first element in the list
void LinkedBagRecursive::pop_front()
{
	// Find the first node pointer and the second
	Node* tempPtr = headPtr;
    Node* nextPtr = tempPtr->getNext();

	// Delete the current head pointer and replace it with the second to last
    delete tempPtr;
    headPtr = nextPtr;

	// Decrease your item count
    itemCount--;
}

// Removes the last element in the list
void LinkedBagRecursive::pop_back()
{
	// Record the head node pointer
	Node* head = headPtr;

	// Find the second to last node pointer
	Node* secondLastptr = findIndex(getCurrentSize()-2, head);

	// Get the last pointer and delete it
    Node* tempPtr = secondLastptr->getNext();
    delete tempPtr;

	// Set the next pointer in the now last node to a nullptr
    secondLastptr->setNext(nullptr);

	// Decrease your item count
    itemCount--;
}

// Reverse the given list
LinkedBagRecursive LinkedBagRecursive::reverse() const
{
	// Create inital bag
	LinkedBagRecursive* nextBag = new LinkedBagRecursive();

	// Loop through each value in the old bag
    for (int i = 1; i <= getCurrentSize(); i++)
	{
		// Fill in the new bag in the opposite order
    	nextBag->push_back(getAt(getCurrentSize()-i));
    }

	// Return the new bag
	return *nextBag;
}



// Private Methods:

// Use this section to define recursive function


void LinkedBagRecursive::fillVector(vector<int>& bagContents,
                                     Node* curPtr) const
{
   if (curPtr != nullptr)
   {
      bagContents.push_back(curPtr->getItem());
      fillVector(bagContents, curPtr->getNext());
   } // end if
}  // end toVector

Node* LinkedBagRecursive::getPointerTo(const int& target,
                                                  Node* curPtr) const
{
   Node* result = nullptr;
   if (curPtr != nullptr)
   {
      if (target== curPtr->getItem())
         result = curPtr;
      else
         result = getPointerTo(target, curPtr->getNext());
   } // end if

   return result;
}  // end getPointerTo

int LinkedBagRecursive::countFrequency(const int& anEntry, int counter,
                                        Node* curPtr) const
{
	int frequency = 0;
   if ((curPtr != nullptr) && (counter < itemCount))
   {
      if (anEntry == curPtr->getItem())
      {
         frequency = 1 + countFrequency(anEntry, counter + 1, curPtr->getNext());
      }
      else
      {
         frequency = countFrequency(anEntry, counter + 1, curPtr->getNext());
      }  // end if
   } // end while

	return frequency;
}  // end countFrequency

void LinkedBagRecursive::deallocate(Node* nextNodePtr)
{
   Node* nodeToDeletePtr = nextNodePtr;
   if (nextNodePtr != nullptr)
   {
      nextNodePtr = nextNodePtr->getNext();
      delete nodeToDeletePtr;
      nodeToDeletePtr = nextNodePtr;
      deallocate(nextNodePtr);
   }  // end if
}  // end deallocate

Node* LinkedBagRecursive::findIndex(int index, Node* curPtr) const
{
	// Check to see if the amount of nexts have been completed
	if(index <= 0)
		return curPtr;
	// If not at correct possition shift again
	else
		return findIndex(--index,curPtr->getNext());
}
