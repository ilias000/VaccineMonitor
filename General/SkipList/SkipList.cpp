#include "SkipList.h"

#include <time>

#include <iostream>
using namespace std;

// SKIP_LIST_NODE

SkipListNode::SkipListNode(int id, SkipListNode* below, SkipListNode* next) : id(id), next(next), below(below)
{
}

SkipListNode::~SkipListNode()
{
}

void SkipListNode::printAll() // prints all nodes
{
    SkipListNode* temp = this->getNext();
    while (temp != NULL)
    {
        cout << temp->getId() << " ";
        temp = temp->getNext();
        if (temp->getNext() == NULL)
            break;
    }
    cout << endl;
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
        this->firstNode = belowLayer->firstNode;
        this->lastNode = belowLayer->lastNode;
    }
}
SkipListLayer ::~SkipListLayer()
{
}

//SKIP_LIST

SkipList::SkipList(LinkedListStringNode* virus) : virus(virus)
{
    this->next = NULL;
    this->vaccinated = new SkipListLayer(NULL);
    this->nonVaccinated = new SkipListLayer(NULL);
    this->vaccinatedLayers = 1;
    this->nonVaccinatedLayers = 1;
}

SkipList::~SkipList()
{
}

void SkipList::insertVirus(LinkedListStringNode* virus) // inserts at the end
{
    SkipList* tmp = this;
    while (tmp->next != NULL)
        tmp = tmp->getNext();
    tmp->setNext(new Skiplist(virus));
}

SkipList* SkipList::findVirus(LinkedListStringNode* virus)
{
    SkipList* tmp = this;
    while (tmp != NULL)
    {
        if (tmp->getVirusName.compare(virus->name) == 0)
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
        if (tmp->getVirusName.compare(virusName) == 0)
            return tmp;
        tmp = tmp->getNext();
    }
    return NULL;
}

void SkipList::insertNodeVaccinated(int id)
{
    SkipListNode* currentNode = this->firstNode;
    SkipListNode* nextNode = currentNode->getNext();
    int currentLayer = this->getLayer();

    struct timeval time;
    gettimeofday(&time, NULL);
    srand((time.tv_nsec * 1000) + (time.tv_sec * 1000) + (time.tv_usec / 1000));

    int layerOfNewNode = 0;
    while ((rand() % 2) && (currentLayer >= layerOfNewNode))
    {
        layerOfNewNode++;
        if (layerOfNewNode == 8) // 9 layers is the max we want
            break;
    }

    if (layerOfNewNode > currentLayer) // checking if i have to create a new layer
    {
        SkipListLayer* newLayer = new SkipListLayer(this);

    }

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

void SkipList::insertNodeNonVaccinated(int id)
{
    SkipListNode* currentNode = this->firstNode;
    SkipListNode* nextNode = currentNode->getNext();
    int currentLayer = this->getLayer();

    struct timeval time;
    gettimeofday(&time, NULL);
    srand((time.tv_nsec * 1000) + (time.tv_sec * 1000) + (time.tv_usec / 1000));

    int layerOfNewNode = 0;
    while ((rand() % 2) && (currentLayer >= layerOfNewNode))
    {
        layerOfNewNode++;
        if (layerOfNewNode == 8) // 9 layers is the max we want
            break;
    }

    if (layerOfNewNode > currentLayer) // checking if i have to create a new layer
    {
        SkipListLayer* newLayer = new SkipListLayer(this);

    }

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

void nikolas()
{
    skipListLevel* currLevel = this->getCeiling();
    skipListNode* currNode = currLevel->getNegInf();
    skipListNode* nextNode = currNode->getNext();

    skipListNode* prevCreated = NULL;
    int create = 0;
    int heightOfNewNode = 0;
    while (this->coinFlip() && (this->getCeiling()->getMyLevel() >= heightOfNewNode) && this->getCeiling()->getMyLevel() < maxLevels - 1)
    {
        heightOfNewNode++;
    }

    while (1)
    {
        if (id < nextNode->getId())
        {
            if (currLevel->getMyLevel() <= heightOfNewNode)
            { // create a node
                if (create)
                {
                    skipListNode* downNode = new skipListNode(citizen);
                    checkNew(downNode);
                    prevCreated->setDown(downNode);
                    currNode->setNext(downNode);
                    downNode->setNext(nextNode);
                    prevCreated = downNode;
                }
                else if (!create) // if it is the first time
                {
                    prevCreated = new skipListNode(citizen);
                    checkNew(prevCreated);
                    currNode->setNext(prevCreated);
                    prevCreated->setNext(nextNode);
                    if (currLevel == this->getCeiling() && heightOfNewNode == this->getCeiling()->getMyLevel() + 1)
                    { // make a new level
                        skipListLevel* newLevel = new skipListLevel(this->getCeiling(), this->getCeiling()->getMyLevel() + 1);
                        checkNew(newLevel);
                        this->setCeiling(newLevel);
                        skipListNode* newN = new skipListNode(prevCreated);
                        checkNew(newN);
                        this->getCeiling()->getList()->add(newN);
                    }
                    create = 1;
                }
            }

            if (currNode->getDown() != NULL)
            { // if there is a down level
                // step down
                currNode = currNode->getDown();
                nextNode = currNode->getNext();
                currLevel = currLevel->getDownLevel();
            }
            else
            {
                if (!create)
                {
                    prevCreated = new skipListNode(citizen);
                    checkNew(prevCreated);
                    currNode->setNext(prevCreated);
                    prevCreated->setNext(nextNode);
                }
                return;
            }
        }
        else if (id > nextNode->getId())
        {
            currNode = nextNode;
            nextNode = nextNode->getNext();
        }
        else if (id == nextNode->getId())
        {
            return;
        }
    }
}

void SkipList::deleteNodeVaccinated(int)
{
}

void SkipList::deleteNodeNonVaccinated(int)
{
}

SkipListNode* SkipList::findNodeVaccinated(int id) // finds the node with the id and returns it else returns NULL
{
    SkipListNode* currentNode = this->firstNode;
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
    SkipListNode* currentNode = this->firstNode;
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