#include "SkipList.h"

#include <iostream>
using namespace std;

// SKIP_LIST_NODE

SkipListNode::SkipListNode(int id, SkipListNode* below, SkipListNode* next) : id(id), next(next), below(below)
{
}

SkipListNode::~SkipListNode()
{
}

void SkipListNode::printNode() // prints a node
{
    cout << "[" << id << "," << this << "," << this->getBelow() << "]";
}

// SKIP_LIST_LAYER

SkipListLayer::SkipListLayer(SkipListLayer* belowLayer)
{
    if (belowLayer == NULL)
    {
        this->layer = 0;
        this->belowLayer = NULL;
        this->lastNode = new SkipListNode(10000, NULL, NULL);         // 10000 because the ids are [0,9999]
        this->firstNode = new SkipListNode(-1, NULL, this->lastNode); // -1 because the ids are [0,9999]
    }
    else
    {
        this->layer = belowLayer->getLayer() + 1;
        this->belowLayer = belowLayer;
        this->lastNode = new SkipListNode(10000, belowLayer->lastNode, NULL);         // 10000 because the ids are [0,9999]
        this->firstNode = new SkipListNode(-1, belowLayer->firstNode, this->lastNode); // -1 because the ids are [0,9999]
    }
}
SkipListLayer ::~SkipListLayer()
{
}

void SkipListLayer::printLayer()
{
    SkipListNode* tmp = this->firstNode;
    while (tmp != NULL)
    {
        tmp->printNode();
        tmp = tmp->getNext();
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
}

void SkipList::printNonVaccinated()
{
    SkipListLayer* tmp = this->nonVaccinated;
    while (tmp != NULL)
    {
        tmp->printLayer();
        cout << endl;
        tmp = tmp->getBelowLayer();
    }
    cout << endl;
}

void SkipList::printVaccinated()
{
    SkipListLayer* tmp = this->vaccinated;
    while (tmp != NULL)
    {
        tmp->printLayer();
        cout << endl;
        tmp = tmp->getBelowLayer();
    }
    cout << endl;
}

void SkipList::insertVirus(LinkedListStringNode* virus) // inserts at the end
{
    SkipList* tmp = this;
    while (tmp->next != NULL)
        tmp = tmp->getNext();
    tmp->setNext(new SkipList(virus));
}

SkipList* SkipList::findVirus(LinkedListStringNode* virus)
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

SkipList* SkipList::findVirus(string virusName)
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

void SkipList::insertNodeVaccinated(int id)
{
    SkipListNode* currentNode = this->getVaccinated()->getFirstNode();
    SkipListNode* nextNode = currentNode->getNext();
    int currentLayer = this->getVaccinated()->getLayer();

    // struct timeval time;
    // gettimeofday(&time, NULL);
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    srand((time.tv_nsec * 1000) + (time.tv_sec * 1000));

    int layerOfNewNode = 0;
    while ((rand() % 2) && (currentLayer >= layerOfNewNode))
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
        if (nextNode->getId() < id) // if the next node id is smaller than the id
        {
            currentNode = nextNode;
            nextNode = currentNode->getNext();
        }
        else if (nextNode->getId() > id) // if the next node id is greater than the id
        {
            if (layerOfNewNode >= currentLayer)
            {
                SkipListNode* newNode = new SkipListNode(id, NULL, NULL);
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

void SkipList::insertNodeNonVaccinated(int id)
{
    SkipListNode* currentNode = this->getNonVaccinated()->getFirstNode();
    SkipListNode* nextNode = currentNode->getNext();
    int currentLayer = this->getNonVaccinated()->getLayer();

    // struct timeval time;
    // gettimeofday(&time, NULL);
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    srand((time.tv_nsec * 1000) + (time.tv_sec * 1000));

    int layerOfNewNode = 0;
    while ((rand() % 2) && (currentLayer >= layerOfNewNode))
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
        if (nextNode->getId() < id) // if the next node id is smaller than the id
        {
            currentNode = nextNode;
            nextNode = currentNode->getNext();
        }
        else if (nextNode->getId() > id) // if the next node id is greater than the id
        {
            if (layerOfNewNode >= currentLayer)
            {
                SkipListNode* newNode = new SkipListNode(id, NULL, NULL);
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

void SkipList::deleteNodeVaccinated(int id)
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
        else // the next node id is equal to the id
        {
            SkipListNode* nodeToDelete = nextNode;

        }
    }
}

void SkipList::deleteNodeNonVaccinated(int)
{
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
        else // the next node id is equal to the id
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
        else // the next node id is equal to the id
            return nextNode;
    }
}