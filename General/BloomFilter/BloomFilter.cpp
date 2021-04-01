#include "BloomFilter.h"

#include <iostream>
using namespace std;

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

unsigned long djb2(unsigned char *str)
{
    int c;
    unsigned long hash = 5381;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

// hash function

unsigned long sdbm(unsigned char *str)
{
    int c;
    unsigned long hash = 0;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

// hash function

unsigned long hash_i(unsigned char *str, unsigned int i)
{
    return djb2(str) + i * sdbm(str) + i * i;
}

void BloomFilter::insert(int number) // takes the id of the citizen and makes 16 bits of the filter that the hash function will tell 1
{
    unsigned char numberChar = (unsigned char)number;
    int K = 16;
    for (int i = 0; i < K; i++)
    {
        int bit = hash_i(&numberChar, i) % this->getSize(); // mod with the size because the hash function may return a value greater than the size of the bloom filter
        this->setBit1(bit);
    }
}

bool BloomFilter::find(int number) // returns true if an
{
    unsigned char numberChar = (unsigned char)number;
    int K = 16;
    for (int i = 0; i < K; i++)
    {
        int bit = hash_i(&numberChar, i) % this->getSize(); // mod with the size because the hash function may return a value greater than the size of the bloom filter
        if (!this->getBit(bit))
            return false;
    }
    return true;
}

LinkedListBloomFilter::LinkedListBloomFilter(LinkedListStringNode *virus, int size) : virus(virus)
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

void LinkedListBloomFilter::insert(LinkedListStringNode *virus, int size)
{
    LinkedListBloomFilter *tmp = this;
    LinkedListBloomFilter *newNode = new LinkedListBloomFilter(virus, size);
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

BloomFilter *LinkedListBloomFilter::getFilter(LinkedListStringNode *virus)
{
    LinkedListBloomFilter *node = this;
    while (node != NULL)
    {
        if (node->virus->name.compare(virus->name) == 0)
            return node->filter;
        node = node->next;
    }
    return NULL;
}

LinkedListBloomFilter *LinkedListBloomFilter::getNode(LinkedListStringNode *virus)
{
    LinkedListBloomFilter *node = this;
    while (node != NULL)
    {
        if (node->virus->name.compare(virus->name) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}