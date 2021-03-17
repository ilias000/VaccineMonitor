#include "LinkedListVaccine.h"

#include <string>

#include <iostream>
using namespace std;

LinkedListVaccine::LinkedListVaccine() : start(NULL), end(NULL)
{
}

LinkedListVaccine::~LinkedListVaccine()
{
    LinkedListVaccineNode *tmpNode = start;
    LinkedListVaccineNode *tmpNodeNext;
    while (tmpNode != NULL)
    {
        tmpNodeNext = tmpNode->next;
        delete tmpNode;
        tmpNode = tmpNodeNext;
    }
}

void LinkedListVaccine::insertNode(LinkedListStringNode *virusName, string vaccinated, string date) // inserts a node at the end of the list
{
    LinkedListVaccineNode *newNode = new LinkedListVaccineNode; // creating a new node
    newNode->virusName = virusName;
    newNode->vaccinated = vaccinated;
    newNode->date = date;
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

LinkedListVaccineNode *LinkedListVaccine::findNode(LinkedListStringNode *stringNode) // if the LinkedListStringNode exist returns the node else returns NULL
{
    LinkedListVaccineNode *current = start; // initialize current
    while (current != NULL)
    {
        if (current->virusName->name.compare(stringNode->name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

LinkedListVaccineNode *LinkedListVaccine::findNode(string name) // if the string exist returns the node else returns NULL
{
    LinkedListVaccineNode *current = start; // initialize current
    while (current != NULL)
    {
        if (current->virusName->name.compare(name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void LinkedListVaccine::print()
{
    LinkedListVaccineNode *tmp = start;
    while (tmp != NULL)
    {
        cout << tmp->virusName->name << " " << tmp->vaccinated << " " << tmp->date << endl;
        tmp = tmp->next;
    }
}