#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "../LinkedList/LinkedListString/LinkedListString.h"

#include <iostream>

using namespace std;

class SkipListNode
{
    int id; // todo: id to citizen
    SkipListNode *next;
    SkipListNode *below;

public:
    SkipListNode(int, SkipListNode *, SkipListNode *);
    ~SkipListNode();

    int getId() { return id; }
    SkipListNode *getNext() { return next; }
    SkipListNode *getBelow() { return below; }

    void setId(int id) { this->id = id; }
    void setNext(SkipListNode *next) { this->next = next; }
    void setBelow(SkipListNode *below) { this->below = below; }

    void printAll(); // prints all nodes
};

class SkipListLayer
{
    SkipListNode *firstNode;
    SkipListNode *lastNode;
    SkipListLayer *belowLayer;
    int layer;

public:
    SkipListLayer(SkipListLayer *);
    ~SkipListLayer();

    SkipListNode *getFirstNode() { return firstNode; }
    SkipListNode *getLastNode() { return lastNode; }
    SkipListLayer *getBelowLayer() { return belowLayer; }
    int getLayer() { return layer; }

    void setFirstNode(SkipListNode *firstNode) { this->firstNode = firstNode; }
    void setLastNode(SkipListNode *lastNode) { this->lastNode = lastNode; }
    void setBelowLayer(SkipListLayer *belowLayer) { this->belowLayer = belowLayer; }
    void setLayer(int layer) { this->layer = layer; }

    void insertNode(int);
    void deleteNode(int);
    SkipListNode *findNode(int);
};

class SkipList
{
    SkipListLayer *vaccinated;
    SkipListLayer *nonVaccinated;
    LinkedListStringNode *virus;
    SkipList *next;
    int vaccinatedLayers;
    int nonVaccinatedLayers;

public:
    SkipList(LinkedListStringNode *);
    ~SkipList();

    SkipListLayer *getVaccinated() { return vaccinated; }
    SkipListLayer *getNonVaccinated() { return nonVaccinated; }
    string getVirusName() { return virus->name; }
    SkipList *getNext() { return next; }
    int getVaccinatedLayers() { return vaccinatedLayers; }
    int getNonVaccinatedLayers() { return nonVaccinatedLayers; }

    void setVaccinated(SkipListLayer *vaccinated) { this->vaccinated = vaccinated; }
    void setNonVaccinated(SkipListLayer *nonVaccinated) { this->nonVaccinated = nonVaccinated; }
    void setVirus(LinkedListStringNode *virus) { this->virus = virus; }
    void setNext(SkipList *next) { this->next = next; }
    void setVaccinatedLayers(int vaccinatedLayers) { this->vaccinatedLayers = vaccinatedLayers; }
    void setNonVaccinatedLayers(int nonVaccinatedLayers) { this->nonVaccinatedLayers = nonVaccinatedLayers; }
};

#endif