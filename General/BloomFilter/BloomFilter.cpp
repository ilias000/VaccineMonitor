#include "BloomFilter.h"

#include <iostream>
using namespace std;

//BLOOM_FILTER

BloomFilter::BloomFilter(int size)
{
    this->size = size / sizeof(char); // converting the bytes to bits
    this->filter = new char[this->size];
    for (int i = 0; i < this->size; i++)
        this->filter[i] = 0;
}

BloomFilter::~BloomFilter()
{
    delete filter;
}

void BloomFilter::setBit0(int k) // finds the K bit and sets it to 0
{
    int byte = k / 8;
    int bit = k % 8;
    this->filter[byte] = this->filter[byte] & ~(1 << bit);
}

void BloomFilter::setBit1(int k) // finds the K bit and sets it to 1
{
    int byte = k / 8;
    int bit = k % 8;
    this->filter[byte] = this->filter[byte] | (1 << bit);
}

int BloomFilter::getBit(int k) // returns the value of the specified bit
{
    int byte = k / 8;
    int bit = k % 8;
    if (this->filter[byte] & (1 << bit))
        return 1;
    return 0;
}

// hash function

unsigned long djb2(unsigned char* str)
{
    int c;
    unsigned long hash = 5381;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

// hash function

unsigned long sdbm(unsigned char* str)
{
    int c;
    unsigned long hash = 0;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

// hash function

unsigned long hash_i(unsigned char* str, unsigned int i)
{
    return djb2(str) + i * sdbm(str) + i * i;
}

void BloomFilter::insert(int id) // takes the id of the citizen and makes 16 bits of the filter that the hash function will tell 1
{
    char charId[4];                  // will store the id like a char
    unsigned char unsignedCharId[4]; // will store the id like a unsigned char
    sprintf(charId, "%d", id);       // storing the id like a char in the charId array
    for (int i = 0; i < 4; i++)      // storing the id like an unsinged char in the unsignedCharId array
        unsignedCharId[i] = charId[i];

    for (int i = 0; i < 16; i++)
    {
        int bit = hash_i(unsignedCharId, i) % this->getSize(); // mod with the size because the hash function may return a value greater than the size of the bloom filter
        this->setBit1(bit);
    }
}

bool BloomFilter::find(int id) // takes the id and returns true if all of the bits that the hash function will tell are 1
{
    char charId[4];                  // wil store the id like a char
    unsigned char unsignedCharId[4]; // will store the id like a unsigned char
    sprintf(charId, "%d", id);       // storing the id like a char in the charId array
    for (int i = 0; i < 4; i++)      // storing the id like an unsinged char in the unsignedCharId array
        unsignedCharId[i] = charId[i];

    for (int i = 0; i < 16; i++)
    {
        int bit = hash_i(unsignedCharId, i) % this->getSize(); // mod with the size because the hash function may return a value greater than the size of the bloom filter
        if (!this->getBit(bit))
            return false;
    }
    return true;
}

// LINKED_LIST_BLOOM_FILTER

LinkedListBloomFilter::LinkedListBloomFilter(LinkedListStringNode* virus, int size) : virus(virus)
{
    this->filter = new BloomFilter(size);
    this->next = NULL;
}

LinkedListBloomFilter::~LinkedListBloomFilter()
{
    if (this->filter != NULL)
        delete this->filter;
    if (this->next != NULL)
        delete this->next;
}

void LinkedListBloomFilter::insert(LinkedListStringNode* virus, int size) // creates a linked list bloom filter with filter for the specified virus and inserts it to the list
{
    LinkedListBloomFilter* tmp = this;
    LinkedListBloomFilter* newNode = new LinkedListBloomFilter(virus, size);
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

BloomFilter* LinkedListBloomFilter::getFilter(LinkedListStringNode* virus) // returns the filter of the specified virus
{
    LinkedListBloomFilter* node = this;
    while (node != NULL)
    {
        if (node->virus->name.compare(virus->name) == 0)
            return node->filter;
        node = node->next;
    }
    return NULL;
}

LinkedListBloomFilter* LinkedListBloomFilter::getNode(LinkedListStringNode* virus) // returns the node of the specified virus
{
    LinkedListBloomFilter* node = this;
    while (node != NULL)
    {
        if (node->virus->name.compare(virus->name) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}