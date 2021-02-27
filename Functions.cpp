#include "Functions.h"

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

string *splitString(string *line, int *numWords)
{
    if (line == NULL)
    {
        cout << "The string is NULL !" << endl;
        return 0;
    }

    *numWords = 1;
    string word;

    istringstream str(*line);
    while (str >> word)
        (*numWords)++;

    string *wordsOfLine = new string[*numWords];
    istringstream I_line(*line);
    for (int currentWord = 0; currentWord < *numWords; currentWord++)
    {
        I_line >> wordsOfLine[currentWord];
    }

    return wordsOfLine;
}