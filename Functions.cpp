#include "Functions.h"

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

string *splitString(string *line)
{
    if (line == NULL)
    {
        cout << "The string is NULL !" << endl;
        return 0;
    }

    int numWords = 0;
    string word;

    istringstream I_line(*line);

    while (I_line >> word)
        numWords++;

    string *wordsOfLine = new string[numWords];

    for (int currentWord = 0; currentWord < numWords; currentWord++)
    {
        I_line >> wordsOfLine[currentWord];
    }

    return wordsOfLine;
}