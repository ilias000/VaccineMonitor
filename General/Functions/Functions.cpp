#include "Functions.h"

#include <sstream>
#include <iostream>
using namespace std;

string *stringSeperator(string *line, int *numWords)
{
    if (line == NULL)
        return NULL;

    *numWords = 0;
    string word; // will store every word of the string

    istringstream countWords(*line); // counting how many words the string has
    while (countWords >> word)
        (*numWords)++;

    string *wordsOfLine = new string[*numWords]; // allocating memory for an array of strings that will store every word
    istringstream I_line(*line);
    for (int currentWord = 0; currentWord < *numWords; currentWord++) // inserting every word of the string to the array
        I_line >> wordsOfLine[currentWord];

    return wordsOfLine; // returning the array that contains the strings
}