#ifndef CITIZENRECORD_H
#define CITIZENRECORD_H

#include "../LinkedList/LinkedListString/LinkedListString.h"
#include "../LinkedList/LinkedListVaccine/LinkedListVaccine.h"

#include <string>

#include <iostream>
using namespace std;

class CitizenRecord
{
    int id;
    string firstName;
    string lastName;
    LinkedListStringNode *country;
    int age;
    LinkedListVaccine *viruses;

public:
    CitizenRecord(int, string, string, LinkedListStringNode *, int, LinkedListStringNode *, string, string);
    ~CitizenRecord();

    int getId() { return id; }                          // returns the id
    LinkedListVaccine *getViruses() { return viruses; } // returns the address of the viruses list

    void print(); // prints the record
};

#endif