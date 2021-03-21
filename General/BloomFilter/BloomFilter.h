#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include "../LinkedList/LinkedListVaccine/LinkedListVaccine.h"

#include <iostream>

using namespace std;

class BloomFilter
{
    int size; // bits of bloom filter
    char *filter;

public:
    BloomFilter(int);
    ~BloomFilter();

    void setBit0(int);
    void setBit1(int);
    int getBit(int);
    int getSize() { return size * 8; }
    void insert(int);
    bool find(int);
};

class LinkedListBloomFilter
{

    BloomFilter *filter;
    LinkedListBloomFilter *next;

public:
    LinkedListStringNode *virus;
    LinkedListBloomFilter(LinkedListStringNode *, int);
    ~LinkedListBloomFilter();

    void insert(LinkedListStringNode *, int);
    BloomFilter *getFilter(LinkedListStringNode *);
    LinkedListBloomFilter *getNode(LinkedListStringNode *);
};

#endif