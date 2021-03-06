#ifndef CITIZENRECORD_H
#define CITIZENRECORD_H

#include "LinkedList/LinkedListString/LinkedListString.h"

#include <string>

#include <iostream>
using namespace std;

class CitizenRecord
{
    int id;
    string firstName;
    string lastName;
    string country;
    int age;
    string virusName;
    string vaccinated;
    string date;

public:
    CitizenRecord(int, string, string, LinkedListStringNode *, int, LinkedListStringNode *, string, string);
    ~CitizenRecord();
    void print();
};

#endif