#include "Functions.h"

#include <sstream>
#include <string>
#include <iostream>
using namespace std;

string* stringSeperator(string* line, int* numWords)
{
    if (line == NULL)
        return NULL;

    *numWords = 0;
    string word; // will store every word of the string

    istringstream countWords(*line); // counting how many words the string has
    while (countWords >> word)
        (*numWords)++;

    string* wordsOfLine = new string[*numWords]; // allocating memory for an array of strings that will store every word
    istringstream I_line(*line);
    for (int currentWord = 0; currentWord < *numWords; currentWord++) // inserting every word of the string to the array
        I_line >> wordsOfLine[currentWord];

    return wordsOfLine; // returning the array that contains the strings
}

int errorChecking(int numWords, string* wordsOfLine, LinkedListCitizen* citizens) // returns 1 if the record is good and 0 if it is not
{
    if ((numWords < 7) || (numWords > 8))
    {
        cout << "ERROR (Wrong number of words) IN RECORD : ";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((numWords == 7) && (wordsOfLine[6].compare("YES") == 0))
    {
        cout << "ERROR (7 words with YES) IN RECORD : ";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((numWords == 8) && (wordsOfLine[6].compare("NO") == 0))
    {
        cout << "ERROR (8 words with NO) IN RECORD : ";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((stoi(wordsOfLine[0]) < 0) || (stoi(wordsOfLine[0]) > 9999))
    {
        cout << "ERROR (Wrong id) IN RECORD : ";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((stoi(wordsOfLine[4]) < 1) || (stoi(wordsOfLine[4]) > 120))
    {
        cout << "ERROR (Wrong age) IN RECORD : ";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((wordsOfLine[6].compare("YES")) && (wordsOfLine[6].compare("NO")))
    {
        cout << "ERROR (6th word is not YES or NO) IN RECORD : ";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }
    else if ((wordsOfLine[6].compare("YES") == 0) && (checkDate(wordsOfLine[7]) == 0))
    {
        cout << "ERROR (Wrong form of the Date) IN RECORD : ";
        for (int i = 0; i < numWords; i++)
            cout << " " << wordsOfLine[i];
        cout << endl;
        return 0;
    }

    return 1;
}

int checkDate(string date) // takes a string Date and returns 1 if it is in the right form else 0
{
    int day, month, year;
    string dash1, dash2;

    for (unsigned int i = 0; i < date.length(); i++) // checking if the string contains only digits and -
        if (((date[i] < '0' || date[i] > '9') && date[i] != '-'))
            return 0;

    char firstChar = date.front();
    char lastChar = date.back();
    if (!isdigit(firstChar) || !isdigit(lastChar)) // checking that the first and last chars are digits
        return 0;

    if ((date.length() < 8) || (date.length() > 10)) // checking the length of the string (it can be 8-10 because d-mm-yyyy, d-m-yyyy, dd-mm-yyyy, dd-m-yyyy)
        return 0;

    dash1 = date.substr(1, 1);
    if (dash1.compare("-") == 0) // the date is d-...
    {
        dash2 = date.substr(3, 1);
        if (dash2.compare("-") == 0) // the date is d-m-yyyy
        {
            day = stoi(date.substr(0, 1));
            month = stoi(date.substr(2, 1));
            year = stoi(date.substr(4));
            if ((day < 1) || (day > 30))
                return 0;
            if ((month < 1) || (month > 12))
                return 0;
            if ((year < 1900) || (year > 2021))
                return 0;
            return 1;
        }
        dash2 = date.substr(4, 1);
        if (dash2.compare("-") == 0) // the date is d-mm-yyyy
        {
            day = stoi(date.substr(0, 1));
            month = stoi(date.substr(2, 2));
            year = stoi(date.substr(5));
            if ((day < 1) || (day > 30))
                return 0;
            if ((month < 1) || (month > 12))
                return 0;
            if ((year < 1900) || (year > 2021))
                return 0;
            return 1;
        }
        return 0;
    }
    dash1 = date.substr(2, 1);
    if (dash1.compare("-") == 0) // the date is dd-...
    {
        dash2 = date.substr(4, 1);
        if (dash2.compare("-") == 0) // the date is dd-m-yyyy
        {
            day = stoi(date.substr(0, 2));
            month = stoi(date.substr(3, 1));
            year = stoi(date.substr(5));
            if ((day < 1) || (day > 30))
                return 0;
            if ((month < 1) || (month > 12))
                return 0;
            if ((year < 1900) || (year > 2021))
                return 0;
            return 1;
        }
        dash2 = date.substr(5, 1);
        if (dash2.compare("-") == 0) // the date is dd-mm-yyyy
        {
            day = stoi(date.substr(0, 2));
            month = stoi(date.substr(3, 2));
            year = stoi(date.substr(6));
            if ((day < 1) || (day > 30))
                return 0;
            if ((month < 1) || (month > 12))
                return 0;
            if ((year < 1900) || (year > 2021))
                return 0;
            return 1;
        }
        return 0;
    }
    return 0;
}