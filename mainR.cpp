////////////////////////
//FILE NAME: mainR.cpp//
////////////////////////

////////////////
//Contributers//
////////////////

///////////////////////////////////////////////

// NAME                   DATE           CHANGE
// Dillon Dragomir        07-14-2017     Test LinkedBagRecursive
// Andrew Piment          07-14-2017     Test LinkedBagRecursive

///////////////////////////////////////////////

////////////////
//DEPENDANCIES//
////////////////

#include <iostream>
#include <vector>

#include "LinkedBagRecursive.h"

using namespace std;

int main(){
  LinkedBagRecursive obj;
  cout << "Is list empty? " << obj.isEmpty() << endl;

  for(int i = 0; i < 1000; i++){
    obj.add(999-i);
  }

  cout << "Is list empty? " << obj.isEmpty() << endl;
  cout << "Original Size of the list is " << obj.getCurrentSize() << endl;
  obj.insert(1000, 900);
  cout << "Current Size of the list after inserting 1000 at 900 should be 1001, your ouptput is " << obj.getCurrentSize() << endl;
  cout << "Value at position 900 should be 1000, your output is " << obj.getAt(900) << endl;
  cout << "Value at position 901 should be 900, your output is " << obj.getAt(901) << endl;

  obj.remove(50);
  cout << "Does list contain number 50? " << obj.contains(50) << endl;

  cout << "Frequency of value 40? " << obj.getFrequencyOf(40) << endl;

  cout << "Value at position 49 should be 0, your output is " << obj.getAt(49) << endl; // remove function replaces value at 50 with first value and deletes the first entry

  cout << "Value at position 60 should be 61, your output is " << obj.getAt(60) << endl;

  obj.setAt(50, 50);

  cout << "Does list contain number 50? " << obj.contains(50) << endl;
  cout << "Value at position 50 should be 50, your output is " << obj.getAt(50) << endl;

  obj.clear();

  cout << "List cleared" << endl;

  for(int i = 0; i < 1000; i++){
    obj.push_back(999-i);
  }

  cout << "Value at position 0 should be 999, your output is " << obj.getAt(0) << endl;

  LinkedBagRecursive ret_obj = obj.reverse();

  cout << "Value at position 0 of reverse list should be 0, your output is " << ret_obj.getAt(0) << endl;

  obj.pop_front();
  obj.pop_back();
  cout << "Current Size of the list should be 998, your output is " <<
  obj.getCurrentSize() << endl;
  cout << "Does list contain number 0? " << obj.contains(0) << endl;
  cout << "Does list contain number 999? " << obj.contains(999) << endl;


  return 0;
}
