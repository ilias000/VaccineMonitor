#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "../LinkedList/LinkedListString/LinkedListString.h"
#include "../LinkedList/LinkedListCitizen/LinkedListCitizen.h"

#include <iostream>

using namespace std;

class SkipListNode
{
    CitizenRecord* citizen;
    SkipListNode* next;
    SkipListNode* below;

public:
    SkipListNode(CitizenRecord*, SkipListNode*, SkipListNode*);
    ~SkipListNode();

    SkipListNode* getNext() { return next; }
    SkipListNode* getBelow() { return below; }
    CitizenRecord* getCitizen() { return citizen; }

    void setCitizen(CitizenRecord* citizen) { this->citizen = citizen; }
    void setNext(SkipListNode* next) { this->next = next; }
    void setBelow(SkipListNode* below) { this->below = below; }

    int getId(); // returns the id of the citizen if it is not one of the limit nodes
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

    void printLayer(int&); // prints all the nodes of the specific layer
    void deleteAllLayers();
};

class SkipList
{
    SkipListLayer* vaccinated; // the skipList for the vaccinated citizens of the specific virus
    SkipListLayer* nonVaccinated;  // the skipList for the non_vaccinated citizens of the specific virus
    LinkedListStringNode* virus;
    SkipList* next;

public:
    SkipList(LinkedListStringNode*);
    ~SkipList();

    SkipListLayer* getVaccinated() { return vaccinated; } // returns the vaccinated skipList
    SkipListLayer* getNonVaccinated() { return nonVaccinated; } // returns the nonVaccinated skipList
    string getVirusName() { return virus->name; } // returns the name of the specific virus
    SkipList* getNext() { return next; } // returns the node for the next virus

    void setVaccinated(SkipListLayer* vaccinated) { this->vaccinated = vaccinated; }
    void setNonVaccinated(SkipListLayer* nonVaccinated) { this->nonVaccinated = nonVaccinated; }
    void setVirus(LinkedListStringNode* virus) { this->virus = virus; }
    void setNext(SkipList* next) { this->next = next; }

    void printNonVaccinatedLastLayer(int&); // prints the last Layer of the nonVaccinated skipList
    void printVaccinatedLastLayer(int&); // prints the last Layer of the vaccinated skipList

    void insertVirus(LinkedListStringNode*); // inserts a virus at the end of the list

    SkipList* findVirus(LinkedListStringNode*); // returns the skipList of the specific virus
    SkipList* findVirus(string); // returns the skipList of the specific virus

    void insertNodeVaccinated(CitizenRecord*); // inserts a citizen to the vaccinated skipList of the specific virus
    void insertNodeNonVaccinated(CitizenRecord*); // inserts a citizen to the nonVaccinated skipList of the specific virus

    void deleteNodeVaccinated(int);
    void deleteNodeNonVaccinated(int);

    SkipListNode* findNodeVaccinated(int);
    SkipListNode* findNodeNonVaccinated(int);

    void print(); // prints all viruses on skiplist
};

#endif