#include "LinkedListCitizen.h"

#include <iostream>
using namespace std;

LinkedListCitizen::LinkedListCitizen() : start(NULL), end(NULL)
{
}

LinkedListCitizen::~LinkedListCitizen()
{
    LinkedListCitizenNode *tmpNode = start;
    LinkedListCitizenNode *tmpNodeNext;
    while (tmpNode != NULL)
    {
        tmpNodeNext = tmpNode->next;
        delete tmpNode->citizen;
        delete tmpNode;
        tmpNode = tmpNodeNext;
    }
}

void LinkedListCitizen::insertNode(CitizenRecord *citizen) // inserts a node at the rigth place so the list is sorted with smaller ides first
{
    LinkedListCitizenNode *newNode = new LinkedListCitizenNode; // creating a new node
    newNode->citizen = citizen;
    newNode->next = NULL;

    if (start == NULL) // the list is empty
    {
        // insert the node at the start
        start = newNode;
        end = newNode;
    }
    else // the list is not empty
    {
        // insert the node at the right place so the list is sorted
        LinkedListCitizenNode *current = start; // initialize current

        if (current->citizen->getId() > newNode->citizen->getId()) // the id of the first node is greater than the id of the new node
        {
            newNode->next = current;
            start = newNode;
            return;
        }
        else if (current->citizen->getId() == newNode->citizen->getId()) // the id of the first node is equal to the id of the new node
        {
            if (current->citizen->getViruses()->findNode(citizen->getViruses()->getFirstNode()->virusName) == NULL) // if the citizen has not the virus in the list of viruses
            {
                // we insert the virus in the list with the viruses
                current->citizen->getViruses()->insertNode(citizen->getViruses()->getFirstNode()->virusName, citizen->getViruses()->getFirstNode()->vaccinated, citizen->getViruses()->getFirstNode()->date);
            }
            delete citizen;
            delete newNode;
            return;
        }
        while (current->next != NULL) // while there is another node
        {
            if (current->next->citizen->getId() < newNode->citizen->getId()) // if the id of the next node is smaller than the id of the new node
            {
                current = current->next; // we go to the next node
            }
            else if (current->next->citizen->getId() > newNode->citizen->getId()) // if the id of the next node is greater than the id of the new node
            {
                // we insert the new node before the next node and after the current node
                newNode->next = current->next;
                current->next = newNode;
                break;
            }
            else // the id of the next node is equal to the id of the new node
            {
                if (current->next->citizen->getViruses()->findNode(citizen->getViruses()->getFirstNode()->virusName) == NULL) // if the citizen has not the virus in the list of viruses
                {
                    // we insert the virus in the list with the viruses
                    current->next->citizen->getViruses()->insertNode(citizen->getViruses()->getFirstNode()->virusName, citizen->getViruses()->getFirstNode()->vaccinated, citizen->getViruses()->getFirstNode()->date);
                }
                delete citizen;
                delete newNode;
                break;
            }
        }
        if (current->next == NULL) // all the nodes are smaller than the new one so we insert the new one at the end
        {
            current->next = newNode;
        }
    }
}

LinkedListCitizenNode *LinkedListCitizen::findNode(int id) // if the id exist returns the node else returns NULL
{
    LinkedListCitizenNode *current = start; // initialize current
    while (current != NULL)
    {
        if (current->citizen->getId() == id)
            return current;
        current = current->next;
    }
    return NULL;
}

void LinkedListCitizen::print() // prints every citizen of the list
{
    LinkedListCitizenNode *current = start; // initialize current
    while (current != NULL)
    {
        current->citizen->print();
        cout << endl;
        current = current->next;
    }
}