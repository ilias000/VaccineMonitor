#ifndef LINKEDLISTCITIZEN_H
#define LINKEDLISTCITIZEN_H

#include "../../CitizenRecord/CitizenRecord.h"

#include <iostream>

using namespace std;

class LinkedListCitizenNode
{
    CitizenRecord* citizen;
    LinkedListCitizenNode* next;
public:
    LinkedListCitizenNode();
    ~LinkedListCitizenNode();

    int getId() { return citizen->getId(); }

    CitizenRecord* getCitizen() { return citizen; }
    LinkedListCitizenNode* getNext() { return next; }
    void setCitizen(CitizenRecord* citizen) { this->citizen = citizen; }
    void setNext(LinkedListCitizenNode* next) { this->next = next; }
};

class LinkedListCitizen
{
    LinkedListCitizenNode* start;
    LinkedListCitizenNode* end;

public:
    LinkedListCitizen();
    ~LinkedListCitizen();

    int insertNode(CitizenRecord**);             // inserts a node at the rigth place so the list is sorted with smaller ides first (if the citizen inserted returns 1 else returns 0)
    int insertNodeCommand(CitizenRecord**);      // inserts a node at the rigth place so the list is sorted with smaller ides first (if the citizen inserted returns 1 else returns 0)
    LinkedListCitizenNode* findNode(int);        // if the id exist returns the node else returns NULL
    void print();                                // prints every citizen of the list
};

#endif