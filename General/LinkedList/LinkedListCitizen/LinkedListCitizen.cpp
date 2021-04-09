#include "LinkedListCitizen.h"

#include <iostream>
using namespace std;

LinkedListCitizenNode::LinkedListCitizenNode() :citizen(NULL), next(NULL)
{
}

LinkedListCitizenNode::~LinkedListCitizenNode()
{
}

LinkedListCitizen::LinkedListCitizen() : start(NULL), end(NULL)
{
}

LinkedListCitizen::~LinkedListCitizen()
{
    LinkedListCitizenNode* tmpNode = start;
    LinkedListCitizenNode* tmpNodeNext;
    while (tmpNode != NULL)
    {
        tmpNodeNext = tmpNode->getNext();
        delete tmpNode->getCitizen();
        delete tmpNode;
        tmpNode = tmpNodeNext;
    }
}

int LinkedListCitizen::insertNode(CitizenRecord** citizen) // inserts a node at the rigth place so the list is sorted with smaller ides first (if the citizen inserted returns 1 else returns 0)
{
    LinkedListCitizenNode* newNode = new LinkedListCitizenNode; // creating a new node
    newNode->setCitizen(*citizen);
    newNode->setNext(NULL);

    if (start == NULL) // the list is empty
    {
        // insert the node at the start
        start = newNode;
        end = newNode;
        return 1;
    }
    else // the list is not empty
    {
        // insert the node at the right place so the list is sorted
        LinkedListCitizenNode* current = start; // initialize current

        if (current->getCitizen()->getId() > newNode->getCitizen()->getId()) // the id of the first node is greater than the id of the new node
        {
            // we insert the new node before the first node
            newNode->setNext(current);
            start = newNode;
            return 1;
        }
        else if (current->getCitizen()->getId() == newNode->getCitizen()->getId()) // the id of the first node is equal to the id of the new node so the citizen already exists
        {
            // checking that while it has the same id it also has the same credentials
            if ((current->getCitizen()->getId() != (*citizen)->getId()) || (current->getCitizen()->getFirstName().compare((*citizen)->getFirstName()) != 0) || (current->getCitizen()->getLastName().compare((*citizen)->getLastName()) != 0) || (current->getCitizen()->getCountryName().compare((*citizen)->getCountryName()) != 0) || (current->getCitizen()->getAge() != (*citizen)->getAge()))
            {
                cout << "ERROR (Same ID but different credentials) : " << endl;
                cout << "New record : ";
                (*citizen)->print();
                cout << endl;
                cout << "Old record : ";
                current->getCitizen()->print();
                cout << endl;
                delete* citizen;
                *citizen = current->getCitizen();
                delete newNode;
                return 0;
            }
            if (current->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName) == NULL) // if the citizen has not the virus in the list of viruses
            {
                // we insert the virus in the list with the viruses
                current->getCitizen()->getViruses()->insertNode((*citizen)->getViruses()->getFirstNode()->virusName, (*citizen)->getViruses()->getFirstNode()->vaccinated, (*citizen)->getViruses()->getFirstNode()->date);
                delete* citizen;
                *citizen = current->getCitizen();
                delete newNode;
                return 1;
            }
            else // the citizen has already the virus in the list
            {
                cout << "ERROR (Bad duplicate) : ";
                (*citizen)->print();
                cout << endl;
                delete* citizen;
                *citizen = current->getCitizen();
                delete newNode;
                return 0;
            }
        }
        while (current->getNext() != NULL) // while there is another node
        {
            if (current->getNext()->getCitizen()->getId() < newNode->getCitizen()->getId()) // if the id of the next node is smaller than the id of the new node
            {
                current = current->getNext(); // we go to the next node
            }
            else if (current->getNext()->getCitizen()->getId() > newNode->getCitizen()->getId()) // if the id of the next node is greater than the id of the new node
            {
                // we insert the new node before the next node and after the current node
                newNode->setNext(current->getNext());
                current->setNext(newNode);
                return 1;
            }
            else // the id of the next node is equal to the id of the new node so the citizen already exists
            {
                // checking that while it has the same id it also has the same credentials
                if ((current->getNext()->getCitizen()->getId() != (*citizen)->getId()) || (current->getNext()->getCitizen()->getFirstName().compare((*citizen)->getFirstName()) != 0) || (current->getNext()->getCitizen()->getLastName().compare((*citizen)->getLastName()) != 0) || (current->getNext()->getCitizen()->getCountryName().compare((*citizen)->getCountryName()) != 0) || (current->getNext()->getCitizen()->getAge() != (*citizen)->getAge()))
                {
                    cout << "ERROR (Same ID but different credentials) : " << endl;
                    cout << "New record : ";
                    (*citizen)->print();
                    cout << endl;
                    cout << "Old record : ";
                    current->getNext()->getCitizen()->print();
                    cout << endl;
                    delete* citizen;
                    *citizen = current->getNext()->getCitizen();
                    delete newNode;
                    return 0;
                }
                if (current->getNext()->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName) == NULL) // if the citizen has not the virus in the list of viruses
                {
                    // we insert the virus in the list with the viruses
                    current->getNext()->getCitizen()->getViruses()->insertNode((*citizen)->getViruses()->getFirstNode()->virusName, (*citizen)->getViruses()->getFirstNode()->vaccinated, (*citizen)->getViruses()->getFirstNode()->date);
                    delete* citizen;
                    *citizen = current->getNext()->getCitizen();
                    delete newNode;
                    return 1;
                }
                else // the citizen has already the virus in the list
                {
                    cout << "ERROR (Bad duplicate) : ";
                    (*citizen)->print();
                    cout << endl;
                    delete* citizen;
                    *citizen = current->getNext()->getCitizen();
                    delete newNode;
                    return 0;
                }
            }
        }
        if (current->getNext() == NULL) // all the nodes are smaller than the new one so we insert the new one at the end
        {
            current->setNext(newNode);
            return 1;
        }
    }
    return 0;
}

int LinkedListCitizen::insertNodeCommand(CitizenRecord** citizen) // inserts a node at the rigth place so the list is sorted with smaller ides first (if the citizen inserted returns 1 else returns 0)
{
    LinkedListCitizenNode* newNode = new LinkedListCitizenNode; // creating a new node
    newNode->setCitizen(*citizen);
    newNode->setNext(NULL);

    if (start == NULL) // the list is empty
    {
        // insert the node at the start
        start = newNode;
        end = newNode;
        return 1;
    }
    else // the list is not empty
    {
        // insert the node at the right place so the list is sorted
        LinkedListCitizenNode* current = start; // initialize current

        if (current->getCitizen()->getId() > newNode->getCitizen()->getId()) // the id of the first node is greater than the id of the new node
        {
            // we insert the new node before the first node
            newNode->setNext(current);
            start = newNode;
            return 1;
        }
        else if (current->getCitizen()->getId() == newNode->getCitizen()->getId()) // the id of the first node is equal to the id of the new node so the citizen already exists
        {
            // checking that while it has the same id it also has the same credentials
            if ((current->getCitizen()->getId() != (*citizen)->getId()) || (current->getCitizen()->getFirstName().compare((*citizen)->getFirstName()) != 0) || (current->getCitizen()->getLastName().compare((*citizen)->getLastName()) != 0) || (current->getCitizen()->getCountryName().compare((*citizen)->getCountryName()) != 0) || (current->getCitizen()->getAge() != (*citizen)->getAge()))
            {
                cout << "ERROR (Same ID but different credentials) : " << endl;
                cout << "New record : ";
                (*citizen)->print();
                cout << endl;
                cout << "Old record : ";
                current->getCitizen()->print();
                cout << endl;
                delete* citizen;
                *citizen = current->getCitizen();
                delete newNode;
                return 0;
            }
            if (current->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName) == NULL) // if the citizen has not the virus in the list of viruses
            {
                // we insert the virus in the list with the viruses
                current->getCitizen()->getViruses()->insertNode((*citizen)->getViruses()->getFirstNode()->virusName, (*citizen)->getViruses()->getFirstNode()->vaccinated, (*citizen)->getViruses()->getFirstNode()->date);

                delete* citizen;
                *citizen = current->getCitizen();
                delete newNode;
                return 1;
            }
            else // the citizen has already the virus in the list
            {
                if (current->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->vaccinated.compare("YES") == 0) // the vaccinated of the old record is YES
                {
                    if ((*citizen)->getViruses()->getFirstNode()->vaccinated.compare("YES") == 0) // the vaccinated of the new record is YES
                    {
                        cout << "ERROR: CITIZEN " << (*citizen)->getId() << " ALREADY VACCINATED ON " << current->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->date << endl;
                        delete newNode;
                        return 2;
                    }
                    else // the vaccinated of the new record is NO
                    {
                        cout << "ERROR: CITIZEN " << (*citizen)->getId() << " ALREADY VACCINATED ON " << current->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->date << endl;
                        delete newNode;
                        return 3;
                    }
                }
                else // the vaccinated of the old record is NO
                {
                    if ((*citizen)->getViruses()->getFirstNode()->vaccinated.compare("YES") == 0) // the vaccinated of the new record is YES
                    {
                        current->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->vaccinated = "YES";
                        current->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->date = (*citizen)->getViruses()->getFirstNode()->date;
                        delete* citizen;
                        *citizen = current->getCitizen();
                        delete newNode;
                        return 4;
                    }
                    else // the vaccinated of the new record is NO
                    {
                        cout << "ERROR: CITIZEN " << (*citizen)->getId() << " IS ALREADY NO !" << endl;
                        delete newNode;
                        return 5;
                    }
                }
            }
        }
        while (current->getNext() != NULL) // while there is another node
        {
            if (current->getNext()->getCitizen()->getId() < newNode->getCitizen()->getId()) // if the id of the next node is smaller than the id of the new node
            {
                current = current->getNext(); // we go to the next node
            }
            else if (current->getNext()->getCitizen()->getId() > newNode->getCitizen()->getId()) // if the id of the next node is greater than the id of the new node
            {
                // we insert the new node before the next node and after the current node
                newNode->setNext(current->getNext());
                current->setNext(newNode);
                return 1;
            }
            else // the id of the next node is equal to the id of the new node so the citizen already exists
            {
                // checking that while it has the same id it also has the same credentials
                if ((current->getNext()->getCitizen()->getId() != (*citizen)->getId()) || (current->getNext()->getCitizen()->getFirstName().compare((*citizen)->getFirstName()) != 0) || (current->getNext()->getCitizen()->getLastName().compare((*citizen)->getLastName()) != 0) || (current->getNext()->getCitizen()->getCountryName().compare((*citizen)->getCountryName()) != 0) || (current->getNext()->getCitizen()->getAge() != (*citizen)->getAge()))
                {
                    cout << "ERROR (Same ID but different credentials) : " << endl;
                    cout << "New record : ";
                    (*citizen)->print();
                    cout << endl;
                    cout << "Old record : ";
                    current->getNext()->getCitizen()->print();
                    cout << endl;
                    delete* citizen;
                    *citizen = current->getNext()->getCitizen();
                    delete newNode;
                    return 0;
                }
                if (current->getNext()->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName) == NULL) // if the citizen has not the virus in the list of viruses
                {
                    // we insert the virus in the list with the viruses
                    current->getNext()->getCitizen()->getViruses()->insertNode((*citizen)->getViruses()->getFirstNode()->virusName, (*citizen)->getViruses()->getFirstNode()->vaccinated, (*citizen)->getViruses()->getFirstNode()->date);
                    delete* citizen;
                    *citizen = current->getNext()->getCitizen();
                    delete newNode;
                    return 1;
                }
                else // the citizen has already the virus in the list
                {
                    if (current->getNext()->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->vaccinated.compare("YES") == 0) // the vaccinated of the old record is YES
                    {
                        if ((*citizen)->getViruses()->getFirstNode()->vaccinated.compare("YES") == 0) // the vaccinated of the new record is YES
                        {
                            cout << "ERROR: CITIZEN " << (*citizen)->getId() << " ALREADY VACCINATED ON " << current->getNext()->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->date << endl;
                            delete newNode;
                            return 2;
                        }
                        else // the vaccinated of the new record is NO
                        {
                            cout << "ERROR: CITIZEN " << (*citizen)->getId() << " ALREADY VACCINATED ON " << current->getNext()->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->date << endl;
                            delete newNode;
                            return 3;
                        }
                    }
                    else // the vaccinated of the old record is NO
                    {
                        if ((*citizen)->getViruses()->getFirstNode()->vaccinated.compare("YES") == 0) // the vaccinated of the new record is YES
                        {
                            current->getNext()->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->vaccinated = "YES";
                            current->getNext()->getCitizen()->getViruses()->findNode((*citizen)->getViruses()->getFirstNode()->virusName)->date = (*citizen)->getViruses()->getFirstNode()->date;
                            delete* citizen;
                            *citizen = current->getNext()->getCitizen();
                            delete newNode;
                            return 4;
                        }
                        else // the vaccinated of the new record is NO
                        {
                            cout << "ERROR: CITIZEN " << (*citizen)->getId() << " IS ALREADY NO !" << endl;
                            delete newNode;
                            return 5;
                        }
                    }
                }
            }
        }
        if (current->getNext() == NULL) // all the nodes are smaller than the new one so we insert the new one at the end
        {
            current->setNext(newNode);
            return 1;
        }
    }
    return 0;
}


LinkedListCitizenNode* LinkedListCitizen::findNode(int id) // if the id exist returns the node else returns NULL
{
    LinkedListCitizenNode* current = start; // initialize current
    while (current != NULL)
    {
        if (current->getCitizen()->getId() == id)
            return current;
        current = current->getNext();
    }
    return NULL;
}

void LinkedListCitizen::print() // prints every citizen of the list
{
    LinkedListCitizenNode* current = start; // initialize current
    while (current != NULL)
    {
        current->getCitizen()->print();
        cout << endl;
        current = current->getNext();
    }
}