#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "../LinkedList/LinkedListString/LinkedListString.h"
#include "../LinkedList/LinkedListCitizen/LinkedListCitizen.h"

#include <iostream>

using namespace std;

class SkipListNode
{
    CitizenRecord* citizen;// todo: id to citizen
    SkipListNode* next;
    SkipListNode* below;

public:
    SkipListNode(CitizenRecord*, SkipListNode*, SkipListNode*);
    ~SkipListNode();

    int getId()
    {
        if (citizen == NULL)
        {
            if (next == NULL)
                return 10000;
            else
                return -1;
        }
        else
            return citizen->getId();
    }
    SkipListNode* getNext() { return next; }
    SkipListNode* getBelow() { return below; }
    CitizenRecord* getCitizen() { return citizen; }

    void setCitizen(CitizenRecord* citizen) { this->citizen = citizen; }
    void setNext(SkipListNode* next) { this->next = next; }
    void setBelow(SkipListNode* below) { this->below = below; }

    void printNode(); // prints a node
};

class SkipListLayer
{
    SkipListNode* firstNode;
    SkipListNode* lastNode;
    SkipListLayer* belowLayer;
    int layer;

public:
    SkipListLayer(SkipListLayer*);
    ~SkipListLayer();

    SkipListNode* getFirstNode() { return firstNode; }
    SkipListNode* getLastNode() { return lastNode; }
    SkipListLayer* getBelowLayer() { return belowLayer; }
    int getLayer() { return layer; }

    void setFirstNode(SkipListNode* firstNode) { this->firstNode = firstNode; }
    void setLastNode(SkipListNode* lastNode) { this->lastNode = lastNode; }
    void setBelowLayer(SkipListLayer* belowLayer) { this->belowLayer = belowLayer; }
    void setLayer(int layer) { this->layer = layer; }

    void printLayer(int&);
    void deleteAllLayers();
};

class SkipList
{
    SkipListLayer* vaccinated;
    SkipListLayer* nonVaccinated;
    LinkedListStringNode* virus;
    SkipList* next;

public:
    SkipList(LinkedListStringNode*);
    ~SkipList();

    SkipListLayer* getVaccinated() { return vaccinated; }
    SkipListLayer* getNonVaccinated() { return nonVaccinated; }
    string getVirusName() { return virus->name; }
    SkipList* getNext() { return next; }

    void setVaccinated(SkipListLayer* vaccinated) { this->vaccinated = vaccinated; }
    void setNonVaccinated(SkipListLayer* nonVaccinated) { this->nonVaccinated = nonVaccinated; }
    void setVirus(LinkedListStringNode* virus) { this->virus = virus; }
    void setNext(SkipList* next) { this->next = next; }

    void printNonVaccinatedLastLayer(int&);
    void printVaccinatedLastLayer(int&);

    void insertVirus(LinkedListStringNode*);

    SkipList* findVirus(LinkedListStringNode*);
    SkipList* findVirus(string);

    void insertNodeVaccinated(CitizenRecord*);
    void insertNodeNonVaccinated(CitizenRecord*);

    void deleteNodeVaccinated(int);
    void deleteNodeNonVaccinated(int);

    SkipListNode* findNodeVaccinated(int);
    SkipListNode* findNodeNonVaccinated(int);

    void print(); // prints all viruses on skiplist
};

#endif