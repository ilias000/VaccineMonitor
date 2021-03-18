#ifndef LINKEDLISTVACCINATED_H
#define LINKEDLISTVACCINATED_H

#include "../LinkedListString/LinkedListString.h"

#include <iostream>

using namespace std;

struct LinkedListVaccineNode
{
    LinkedListStringNode *virusName;
    string vaccinated;
    string date;
    LinkedListVaccineNode *next;
};

class LinkedListVaccine
{
    LinkedListVaccineNode *start;
    LinkedListVaccineNode *end;

public:
    LinkedListVaccine();
    ~LinkedListVaccine();

    void insertNode(LinkedListStringNode *, string, string); // inserts a node at the end of the list
    LinkedListVaccineNode *findNode(LinkedListStringNode *); // if the LinkedListStringNode exist returns the node else returns NULL
    LinkedListVaccineNode *findNode(string);                 // if the string exist returns the node else returns NULL
    void print();
    LinkedListVaccineNode *getFirstNode() { return start; }
};

#endif