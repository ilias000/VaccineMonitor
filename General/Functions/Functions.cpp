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

int errorChecking(int numWords, string *wordsOfLine, LinkedListCitizen *citizens) // returns 1 if the record is good and 0 if it is not
{
    if ((numWords < 7) || (numWords > 8))
    {
        cout << "ERROR IN RECORD (Wrong number of words)";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((numWords == 7) && (wordsOfLine[6].compare("YES") == 0))
    {
        cout << "ERROR IN RECORD (7 wrong with YES)";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((numWords == 8) && (wordsOfLine[6].compare("NO") == 0))
    {
        cout << "ERROR IN RECORD (8 words with NO)";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((stoi(wordsOfLine[0]) < 0) || (stoi(wordsOfLine[0]) > 9999))
    {
        cout << "ERROR IN RECORD (Wrong id)";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((stoi(wordsOfLine[4]) < 1) || (stoi(wordsOfLine[4]) > 120))
    {
        cout << "ERROR IN RECORD (Wrong age)";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((wordsOfLine[6].compare("YES")) && (wordsOfLine[6].compare("NO")))
    {
        cout << "ERROR IN RECORD (6th word is not YES or NO)";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if (((wordsOfLine[6].compare("YES") == 0)) && (checkDate(wordsOfLine[7]) == 0))
    {
        cout << "ERROR IN RECORD (Wrong form of the Date)";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }

    return 1;
}

int checkDate(string *date) // takes a string Date and returns 1 if it is in the right form else 0
{
}