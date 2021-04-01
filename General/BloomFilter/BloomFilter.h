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

    void setBit0(int);                 // finds the K bit and sets it to 0
    void setBit1(int);                 // finds the K bit and sets it to 1
    int getBit(int);                   // returns the value of the specified bit
    int getSize() { return size * 8; } // returns the size of the filter in bytes
    void insert(int);                  // takes the id of the citizen and makes 16 bits of the filter that the hash function will tell 1
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

    void insert(LinkedListStringNode *, int);               // creates a linked list bloom filter with filter for the specified virus and inserts it to the list
    BloomFilter *getFilter(LinkedListStringNode *);         // returns the filter of the specified virus
    LinkedListBloomFilter *getNode(LinkedListStringNode *); // returns the node of the specified virus
};

#endif