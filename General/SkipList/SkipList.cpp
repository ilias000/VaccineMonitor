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