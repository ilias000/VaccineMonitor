#include "LinkedListString.h"

#include <string>

#include <iostream>
using namespace std;

LinkedListString::LinkedListString() : start(NULL), end(NULL)
{
}

LinkedListString::~LinkedListString()
{
    LinkedListStringNode* tmpNode = start;
    LinkedListStringNode* tmpNodeNext;
    while (tmpNode != NULL)
    {
        tmpNodeNext = tmpNode->next;
        delete tmpNode;
        tmpNode = tmpNodeNext;
    }
}

void LinkedListString::insertNode(string name) // inserts a node at the end of the list
{
    LinkedListStringNode* newNode = new LinkedListStringNode; // creating a new node
    newNode->name = name;
    newNode->next = NULL;

    if (start == NULL) // the list is empty
    {
        // insert the node at the start
        start = newNode;
        end = newNode;
    }
    else // the list is not empty
    {
        // insert the node at the end
        end->next = newNode;
        end = end->next;
    }
}

LinkedListStringNode* LinkedListString::findNode(string name) // if the name exist returns the node else returns NULL
{
    LinkedListStringNode* current = start; // initialize current
    while (current != NULL)
    {
        if (current->name.compare(name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void LinkedListString::print()
{
    LinkedListStringNode* current = start; // initialize current
    while (current != NULL)
    {
        cout << current->name << ",";
        current = current->next;
    }
    cout << endl;
}