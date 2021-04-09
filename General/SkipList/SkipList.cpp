#include "SkipList.h"

#include <iostream>
using namespace std;

// SKIP_LIST_NODE

SkipListNode::SkipListNode(CitizenRecord* citizen, SkipListNode* below, SkipListNode* next) : citizen(citizen), next(next), below(below)
{
}

SkipListNode::~SkipListNode()
{
}

int SkipListNode::getId() // returns the id of the citizen if it is not one of the limit nodes
{
    if (citizen == NULL) // it is one of the limit nodes (-1 or 10000)
    {
        if (next == NULL) // it is the 10000 node
            return 10000;
        else // it is the -1 node
            return -1;
    }
    else
        return citizen->getId();
}

void SkipListNode::printNode() // prints a node
{
    cout << "[" << this->getId() << "," << this << "," << this->getBelow() << "]";
}

// SKIP_LIST_LAYER

SkipListLayer::SkipListLayer(SkipListLayer* belowLayer)
{
    if (belowLayer == NULL) // this is the first layer
    {
        this->layer = 0;
        this->belowLayer = NULL;
        this->lastNode = new SkipListNode(NULL, NULL, NULL);         // 10000 because the ids are [0,9999]
        this->firstNode = new SkipListNode(NULL, NULL, this->lastNode); // -1 because the ids are [0,9999]
    }
    else // it has already layers 
    {
        this->layer = belowLayer->getLayer() + 1;
        this->belowLayer = belowLayer;
        this->lastNode = new SkipListNode(NULL, belowLayer->lastNode, NULL);         // 10000 because the ids are [0,9999]
        this->firstNode = new SkipListNode(NULL, belowLayer->firstNode, this->lastNode); // -1 because the ids are [0,9999]
    }
}
SkipListLayer ::~SkipListLayer()
{
    SkipListNode* tmp = this->firstNode;
    SkipListNode* next = NULL;
    while (tmp != NULL)
    {
        next = tmp->getNext();
        delete tmp;
        tmp = next;
    }
}

void SkipListLayer::printLayer(int& count) // prints all the nodes of the specific layer
{
    SkipListNode* tmp = this->firstNode;
    while (tmp != NULL)
    {
        if (tmp->getCitizen() != NULL)
        {
            tmp->getCitizen()->printInfo();
            count++;
        }
        tmp = tmp->getNext();
    }
}

void SkipListLayer::deleteAllLayers() // deletes all Layers
{
    SkipListLayer* tmp = this;
    SkipListLayer* below = NULL;
    while (tmp != NULL)
    {
        below = tmp->getBelowLayer();
        delete tmp;
        tmp = below;
    }
}

//SKIP_LIST

SkipList::SkipList(LinkedListStringNode* virus) : virus(virus)
{
    this->next = NULL;
    this->vaccinated = new SkipListLayer(NULL);
    this->nonVaccinated = new SkipListLayer(NULL);
}

SkipList::~SkipList()
{
    this->vaccinated->deleteAllLayers();
    this->nonVaccinated->deleteAllLayers();
    if (this->next != NULL)
        delete this->next;
}

void SkipList::printNonVaccinatedLastLayer(int& count) // prints the last Layer of the nonVaccinated skipList (i use the count for the command /list-nonVaccinated-Persons because if it 0 it means that all the citizens have done the vaccine)
{
    SkipListLayer* lastLayer = nonVaccinated;
    while (lastLayer->getBelowLayer() != NULL) // finding the last layer because it has all the citizens
        lastLayer = lastLayer->getBelowLayer();
    lastLayer->printLayer(count);
}

void SkipList::printVaccinatedLastLayer(int& count) // prints the last Layer of the vaccinated skipList
{
    SkipListLayer* lastLayer = vaccinated;
    while (lastLayer->getBelowLayer() != NULL) // finding the last layer because it has all the citizens
        lastLayer = lastLayer->getBelowLayer();
    lastLayer->printLayer(count);
}

void SkipList::insertVirus(LinkedListStringNode* virus) // inserts a virus at the end of the list
{
    SkipList* tmp = this;
    while (tmp->next != NULL) // finding the end of the list
        tmp = tmp->getNext();
    SkipList* newVirus = new SkipList(virus); // creating the skipList for the virus
    tmp->setNext(newVirus); // inserting the skipList for the virus at the end 
}

SkipList* SkipList::findVirus(LinkedListStringNode* virus) // returns the skipList of the specific virus
{
    SkipList* tmp = this;
    while (tmp != NULL)
    {
        if (tmp->getVirusName().compare(virus->name) == 0)
            return tmp;
        tmp = tmp->getNext();
    }
    return NULL;
}

SkipList* SkipList::findVirus(string virusName) // returns the skipList of the specific virus
{
    SkipList* tmp = this;
    while (tmp != NULL)
    {
        if (tmp->getVirusName().compare(virusName) == 0)
            return tmp;
        tmp = tmp->getNext();
    }
    return NULL;
}

void SkipList::insertNodeVaccinated(CitizenRecord* citizen) // inserts a citizen to the vaccinated skipList of the specific virus
{
    SkipListNode* currentNode = this->getVaccinated()->getFirstNode();
    SkipListNode* nextNode = currentNode->getNext();
    int currentLayer = this->getVaccinated()->getLayer();

    //flip coin
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    srand((time.tv_nsec * 1000) + (time.tv_sec * 1000));

    int layerOfNewNode = 0;
    while ((rand() % 2) && (currentLayer >= layerOfNewNode)) // deciding how many layers the new node will have (it can have max currentLayer + 1)
    {
        layerOfNewNode++;
        if (layerOfNewNode == 8) // 9 layers is the max we want
            break;
    }

    if (layerOfNewNode > currentLayer) // checking if i have to create a new layer
    {
        SkipListLayer* newLayer = new SkipListLayer(this->vaccinated);
        this->vaccinated = newLayer;
        currentLayer++;
        currentNode = this->vaccinated->getFirstNode();
        nextNode = currentNode->getNext();
    }

    SkipListNode* tmp = NULL;
    while (1) // until i find the node or i rich bottom layer (layer 0 and i have not found the id)
    {
        if (nextNode->getId() < citizen->getId()) // if the next node id is smaller than the id
        {
            currentNode = nextNode;
            nextNode = currentNode->getNext();
        }
        else if (nextNode->getId() > citizen->getId()) // if the next node id is greater than the id
        {
            if (layerOfNewNode >= currentLayer) // checking if i have to create the node in this Layer or not
            {
                SkipListNode* newNode = new SkipListNode(citizen, NULL, NULL);
                currentNode->setNext(newNode);
                newNode->setNext(nextNode);
                if (tmp != NULL)
                {
                    tmp->setBelow(newNode);
                }
                tmp = newNode;
            }
            if (currentNode->getBelow() != NULL) // checking if i have another level below, if i have go below
            {
                currentNode = currentNode->getBelow();
                nextNode = currentNode->getNext();
                currentLayer--;
            }
            else // i have not another level below
                return;
        }
        else // the next node id is equal to the id
            return;
    }
}

void SkipList::insertNodeNonVaccinated(CitizenRecord* citizen) // inserts a citizen to the nonVaccinated skipList of the specific virus
{
    SkipListNode* currentNode = this->getNonVaccinated()->getFirstNode();
    SkipListNode* nextNode = currentNode->getNext();
    int currentLayer = this->getNonVaccinated()->getLayer();

    //flip coin
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    srand((time.tv_nsec * 1000) + (time.tv_sec * 1000));

    int layerOfNewNode = 0;
    while ((rand() % 2) && (currentLayer >= layerOfNewNode)) // deciding how many layers the new node will have
    {
        layerOfNewNode++;
        if (layerOfNewNode == 8) // 9 layers is the max we want
            break;
    }

    if (layerOfNewNode > currentLayer) // checking if i have to create a new layer
    {
        SkipListLayer* newLayer = new SkipListLayer(this->nonVaccinated);
        this->nonVaccinated = newLayer;
        currentLayer++;
        currentNode = this->nonVaccinated->getFirstNode();
        nextNode = currentNode->getNext();
    }

    SkipListNode* tmp = NULL;
    while (1) // until i find the node or i rich bottom layer (layer 0 and i have not found the id)
    {
        if (nextNode->getId() < citizen->getId()) // if the next node id is smaller than the id
        {
            currentNode = nextNode;
            nextNode = currentNode->getNext();
        }
        else if (nextNode->getId() > citizen->getId()) // if the next node id is greater than the id
        {
            if (layerOfNewNode >= currentLayer) // checking if i have to create the node in this Layer or not
            {
                SkipListNode* newNode = new SkipListNode(citizen, NULL, NULL);
                currentNode->setNext(newNode);
                newNode->setNext(nextNode);
                if (tmp != NULL)
                {
                    tmp->setBelow(newNode);
                }
                tmp = newNode;
            }
            if (currentNode->getBelow() != NULL) // checking if i have another level below, if i have go below
            {
                currentNode = currentNode->getBelow();
                nextNode = currentNode->getNext();
                currentLayer--;
            }
            else // i have not another level below
                return;
        }
        else // the next node id is equal to the id
            return;
    }
}

void SkipList::deleteNodeVaccinated(int id) // deletes the Node with specific id from the Vaccinated skipList
{
    SkipListNode* currentNode = this->getVaccinated()->getFirstNode();
    SkipListNode* nextNode = currentNode->getNext();

    while (1) // until i find the node or i rich bottom layer (layer 0 and i have not found the id)
    {
        if (nextNode->getId() < id) // if the next node id is smaller than the id
        {
            currentNode = nextNode;
            nextNode = currentNode->getNext();
        }
        else if (nextNode->getId() > id) // if the next node id is greater than the id
        {
            if (currentNode->getBelow() != NULL) // checking if i have another level below, if i have go below
            {
                currentNode = currentNode->getBelow();
                nextNode = currentNode->getNext();
            }
            else // i have not another level below
                return;
        }
        else // the next node id is equal to the id
        {
            SkipListNode* belowNodeToDelete = nextNode->getBelow(); // taking the node below of the one that i will delete 
            currentNode->setNext(nextNode->getNext()); // making the node before the one i will delete point to the next node of the one that i will delte
            delete nextNode; // deleting the node
            if (this->getVaccinated()->getFirstNode()->getNext() == this->getVaccinated()->getLastNode()) // if the layer is empty i delete the layer
            {
                SkipListLayer* tmp = this->getVaccinated()->getBelowLayer();
                delete this->vaccinated;
                this->vaccinated = tmp;
            }
            while (belowNodeToDelete != NULL) // for every layer
            {
                currentNode = currentNode->getBelow(); // current (is the previous node of the one i deleted) will show to the same node on the below layer
                while (1) // finding the previous node of the below node that i deleted so i can delete also this one  
                {
                    if (currentNode->getNext() == belowNodeToDelete)
                        break;
                    currentNode = currentNode->getNext();
                }
                // making the previous node of the one i will delete point to the next one of the node i will delete
                currentNode->setNext(belowNodeToDelete->getNext());
                SkipListNode* tmp = belowNodeToDelete->getBelow();
                delete belowNodeToDelete;
                belowNodeToDelete = tmp;
            }
            return;
        }
    }
}

void SkipList::deleteNodeNonVaccinated(int id) // deletes the Node with specific id from the nonVaccinated skipList
{
    SkipListNode* currentNode = this->getNonVaccinated()->getFirstNode();
    SkipListNode* nextNode = currentNode->getNext();

    while (1) // until i find the node or i rich bottom layer (layer 0 and i have not found the id)
    {
        if (nextNode->getId() < id) // if the next node id is smaller than the id
        {
            currentNode = nextNode;
            nextNode = currentNode->getNext();
        }
        else if (nextNode->getId() > id) // if the next node id is greater than the id
        {
            if (currentNode->getBelow() != NULL) // checking if i have another level below, if i have go below
            {
                currentNode = currentNode->getBelow();
                nextNode = currentNode->getNext();
            }
            else // i have not another level below
                return;
        }
        else // the next node id is equal to the id
        {
            SkipListNode* belowNodeToDelete = nextNode->getBelow(); // taking the node below of the one that i will delete 
            currentNode->setNext(nextNode->getNext()); // making the node before the one i will delete point to the next node of the one that i will delte
            delete nextNode;// deleting the node
            if (this->getNonVaccinated()->getFirstNode()->getNext() == this->getNonVaccinated()->getLastNode())  // if the layer is empty i delete the layer
            {
                SkipListLayer* tmp = this->getNonVaccinated()->getBelowLayer();
                delete this->nonVaccinated;
                this->nonVaccinated = tmp;
            }
            while (belowNodeToDelete != NULL) // for every layer
            {
                currentNode = currentNode->getBelow(); // current (is the previous node of the one i deleted) will show to the same node on the below layer
                while (1) // finding the previous node of the below node that i deleted so i can delete also this one  
                {
                    if (currentNode->getNext() == belowNodeToDelete)
                        break;
                    currentNode = currentNode->getNext();
                }
                // making the previous node of the one i will delete point to the next one of the node i will delete
                currentNode->setNext(belowNodeToDelete->getNext());
                SkipListNode* tmp = belowNodeToDelete->getBelow();
                delete belowNodeToDelete;
                belowNodeToDelete = tmp;
            }
            return;
        }
    }
}

SkipListNode* SkipList::findNodeVaccinated(int id) // finds the node with the id and returns it else returns NULL
{
    SkipListNode* currentNode = this->getVaccinated()->getFirstNode();
    SkipListNode* nextNode = currentNode->getNext();

    while (1) // until i find the node or i rich bottom layer (layer 0 and i have not found the id)
    {
        if (nextNode->getId() < id) // if the next node id is smaller than the id
        {
            currentNode = nextNode;
            nextNode = currentNode->getNext();
        }
        else if (nextNode->getId() > id) // if the next node id is greater than the id
        {
            if (currentNode->getBelow() != NULL) // checking if i have another level below, if i have go below
            {
                currentNode = currentNode->getBelow();
                nextNode = currentNode->getNext();
            }
            else // i have not another level below
                return NULL;
        }
        else if (nextNode->getId() == id)// the next node id is equal to the id
            return nextNode;
    }
}

SkipListNode* SkipList::findNodeNonVaccinated(int id) // finds the node with the id and returns it else returns NULL
{
    SkipListNode* currentNode = this->getNonVaccinated()->getFirstNode();
    SkipListNode* nextNode = currentNode->getNext();

    while (1) // until i find the node or i rich bottom layer (layer 0 and i have not found the id)
    {
        if (nextNode->getId() < id) // if the next node id is smaller than the id
        {
            currentNode = nextNode;
            nextNode = currentNode->getNext();
        }
        else if (nextNode->getId() > id) // if the next node id is greater than the id
        {
            if (currentNode->getBelow() != NULL) // checking if i have another level below, if i have go below
            {
                currentNode = currentNode->getBelow();
                nextNode = currentNode->getNext();
            }
            else // i have not another level below
                return NULL;
        }
        else if (nextNode->getId() == id)// the next node id is equal to the id
            return nextNode;
    }
}

void SkipList::print()
{
    SkipList* current = this; // initialize current
    while (current != NULL)
    {
        cout << current->virus->name << ",";
        current = current->next;
    }
    cout << endl;
}