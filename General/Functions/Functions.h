#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../LinkedList/LinkedListCitizen/LinkedListCitizen.h"
#include "../CitizenRecord/CitizenRecord.h"

#include <iostream>
using namespace std;

string *stringSeperator(string *, int *);              // takes a string and an int, stores inside the int the size of the array and returns the array that contains every word of the string
int errorChecking(int, string *, LinkedListCitizen *); // returns 1 if the record is good and 0 if it is not

#endif