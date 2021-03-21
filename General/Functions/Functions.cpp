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
    cout << "ID = " << wordsOfLine[0] << endl;
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
    else if ((wordsOfLine[6].compare("YES") == 0) && (checkDate(wordsOfLine[7]) == 0))
    {
        cout << "ERROR IN RECORD (Wrong form of the Date)";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }

    return 1;
}

int checkDate(string date) // takes a string Date and returns 1 if it is in the right form else 0
{
    istringstream Date(date);
    int day, month, year;
    string dash1, dash2;

    if ((date.length() < 8) || (date.length() > 10)) // it can be 8-10 because d-mm-yyyy, d-m-yyyy, dd-mm-yyyy, dd-m-yyyy
        return 0;

    dash1 = date.substr(1, 1);
    if (dash1.compare("-") == 0) // the date is d-...
    {
        cout << "the date is d-..." << endl;
        dash2 = date.substr(3, 1);
        if (dash2.compare("-") == 0) // the date is d-m-...
        {
            cout << "the date is d-m-..." << endl;
            return 1;
        }
        dash2 = date.substr(4, 1);
        if (dash2.compare("-") == 0) // the date is d-mm-...
        {
            cout << "the date is d-mm-..." << endl;
            return 1;
        }
        return 0;
    }
    dash1 = date.substr(2, 1);
    if (dash1.compare("-") == 0) // the date is dd-...
    {
        cout << "the date is dd-..." << endl;
        dash2 = date.substr(4, 1);
        if (dash2.compare("-") == 0) // the date is dd-m-...
        {
            cout << "the date is dd-m-..." << endl;
            return 1;
        }
        dash2 = date.substr(5, 1);
        if (dash2.compare("-") == 0) // the date is dd-mm-...
        {
            cout << "the date is dd-mm-..." << endl;
            return 1;
        }
        return 0;
        return 0;
    }

    // dash1 = date.substr(3, 1);
    // month = stoi(date.substr(5, 2));
    // dash2 = stoi(date.substr(5, 5));
    // year = stoi(date.substr(5, 8));
    // cout << "Date  = " << day << dash1 << month << dash2 << year << endl;
    // check the lenght
    // if (Date >> day >> ignore >> month >> ignore >> year)
    // {

    // }
    return 0;
}