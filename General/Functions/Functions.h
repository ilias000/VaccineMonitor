#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../LinkedList/LinkedListCitizen/LinkedListCitizen.h"
#include "../CitizenRecord/CitizenRecord.h"
#include "../BloomFilter/BloomFilter.h"
#include "../SkipList/SkipList.h"

#include <iostream>
using namespace std;

string* stringSeperator(string*, int*);              // takes a string and an int, stores inside the int the size of the array and returns the array that contains every word of the string
int errorChecking(int, string*, LinkedListCitizen*); // returns 1 if the record is good and 0 if it is not
int checkDate(string date);                            // takes a string Date and returns 1 if it is in the right form else 0
void commandInterface(LinkedListString*, LinkedListString*, LinkedListCitizen*, LinkedListBloomFilter*, SkipList*, int); // its the interface for the commands that the user can give
#endif