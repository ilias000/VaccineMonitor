#ifndef LINKEDLISTSTRING_H
#define LINKEDLISTSTRING_H

#include <string>

#include <iostream>

using namespace std;

struct LinkedListStringNode
{
    string name;
    LinkedListStringNode* next;
};

class LinkedListString
{
    LinkedListStringNode* start;
    LinkedListStringNode* end;

public:
    LinkedListString();
    ~LinkedListString();

    LinkedListStringNode* getStart() { return start; }

    void insertNode(string);                // inserts a node at the end of the list
    LinkedListStringNode* findNode(string); // if the name exist returns the node else returns NULL
    void print();
};

#endif
