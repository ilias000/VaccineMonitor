#include "SkipList.h"

#include <iostream>
using namespace std;

// SKIP_LIST_NODE

SkipListNode::SkipListNode(int id, SkipListNode *below, SkipListNode *next) : id(id), next(next), below(below)
{
}

SkipListNode::~SkipListNode()
{
}

void SkipListNode::printAll() // prints all nodes
{
    SkipListNode *temp = this->getNext();
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

SkipListLayer::SkipListLayer(SkipListLayer *belowLayer)
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

void insertNode(int)
{
}
void deleteNode(int)
{
}

SkipListNode *findNode(int id)
{
    SkipListNode *currentNode = this->first->getNegInf();
    SkipListNode *nextNode = currNode->getNext();

    while (1)
    {
        if (id < nextNode->getId())
        {
            if (currNode->getDown() != NULL)
            { // if there is a down level
                // step down
                currNode = currNode->getDown();
                nextNode = currNode->getNext();
                currLevel = currLevel->getDownLevel();
            }
            else
            {
                return NULL;
            }
        }
        else if (id > nextNode->getId())
        {
            currNode = nextNode;
            nextNode = nextNode->getNext();
        }
        else
        {
            if (top_bottom == 'b')
            {
                while (1)
                {
                    if (nextNode->getDown() == NULL)
                    {
                        break;
                    }
                    nextNode = nextNode->getDown();
                }
            }
            return nextNode;
        }
    }
}

//SKIP_LIST

SkipList::SkipList(LinkedListStringNode *virus) : virus(virus)
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