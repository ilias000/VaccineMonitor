#include "Functions/Functions.h"
#include "CitizenRecord/CitizenRecord.h"
#include "LinkedList/LinkedListString/LinkedListString.h"
#include "LinkedList/LinkedListCitizen/LinkedListCitizen.h"

#include <stdlib.h>
//#include <string>
#include <fstream>
#include <cstring>
#include <sys/stat.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "                             --- THE VACCINE MONITOR PROGRAM STARTED ---                                 " << endl;
    string extensionOfFileName = (".txt");
    string fileName;
    int bloomSize; // size of bloom filter (bytes)
    string line;   // will store one line of the file each time

    if (argc != 5) // checking the general form of the execution command
    {
        cout << "The general form of the command is not acceptable ! " << endl;
        return 0;
    }

    if (((string(argv[1]).compare("-c")) == 0) && ((string(argv[3]).compare("-b")) == 0)) // The form is : ./vaccineMonitor -c citizenRecordsFile –b bloomSize
    {
        fileName = argv[2];        // storing the file name in the filename variable
        bloomSize = atoi(argv[4]); // converting to int and storing the bloomSize in the bloomSize variable
    }
    else if (((string(argv[3]).compare("-c")) == 0) && ((string(argv[1]).compare("-b")) == 0)) // The form is : ./vaccineMonitor –b bloomSize -c citizenRecordsFile
    {
        fileName = argv[4];        // storing the file name in the filename variable
        bloomSize = atoi(argv[2]); // converting to int and storing the bloomSize in the bloomSize variable
    }
    else // The form is not correct
    {
        cout << "Please use the right form for the execution command ! " << endl;
        return 0;
    }

    fileName.append(extensionOfFileName); // adding extension to the filename

    if (!fstream{fileName}) // checking if the file exist
    {
        cout << "The file : " << fileName << " does not exist!" << endl;
        return 0;
    }

    LinkedListString *countries = new LinkedListString();
    LinkedListString *viruses = new LinkedListString();
    LinkedListCitizen *citizens = new LinkedListCitizen();

    ifstream name; // opening the file that contains the citizen Records
    name.open(fileName);

    while (getline(name, line)) // while we have lines in the file, get the line and store it in the variable line
    {
        int numWords;                                            // will store the size of the array that I keep every word of the line
        string *wordsOfLine = stringSeperator(&line, &numWords); // wordsOfLine will point to the array of strings that contains every word of the line
        if (wordsOfLine == NULL)
        {
            cout << "Error wordsOfLine is NULL !" << endl;
            return 0;
        }

        if (!errorChecking(numWords, wordsOfLine, citizens))
        {
            delete[] wordsOfLine;
            continue;
        }

        // checking if i have already the country in the list
        LinkedListStringNode *country = countries->findNode(wordsOfLine[3]);
        if (country == NULL) // the country does not exist in the list so i will insert it
        {
            countries->insertNode(wordsOfLine[3]);
            country = countries->findNode(wordsOfLine[3]);
        }

        // checking if i have already the virus in the list
        LinkedListStringNode *virus = viruses->findNode(wordsOfLine[5]);
        if (virus == NULL) // the virus does not exist in the list so i will insert it
        {
            viruses->insertNode(wordsOfLine[5]);
            virus = viruses->findNode(wordsOfLine[5]);
        }

        CitizenRecord *citizen;

        if (numWords == 8) // if it has 8 words it means it has also date
            citizen = new CitizenRecord(stoi(wordsOfLine[0]), wordsOfLine[1], wordsOfLine[2], country, stoi(wordsOfLine[4]), virus, wordsOfLine[6], wordsOfLine[7]);
        else if (numWords == 7) // if it has 7 words it means it has not date
            citizen = new CitizenRecord(stoi(wordsOfLine[0]), wordsOfLine[1], wordsOfLine[2], country, stoi(wordsOfLine[4]), virus, wordsOfLine[6], "");

        //elegxw an yparxei o citizen kai an sto citizen yparxei o virus petaw ton citizen , an den yparxei prosthetw to virus sth lista tou citizen
        citizens->insertNode(citizen);

        // citizen->print();
        // cout << endl;
        delete[] wordsOfLine;
    }

    citizens->print();

    delete countries;
    delete viruses;
    delete citizens;
    cout << "                             ---  THE VACCINE MONITOR PROGRAM ENDED  ---                                 " << endl;

    return 0;
}