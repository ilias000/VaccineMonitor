#include "Functions/Functions.h"
#include "CitizenRecord/CitizenRecord.h"
#include "LinkedList/LinkedListString/LinkedListString.h"
#include "LinkedList/LinkedListCitizen/LinkedListCitizen.h"
#include "BloomFilter/BloomFilter.h"
#include "SkipList/SkipList.h"

#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <sys/stat.h>

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
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

    if (!fstream{ fileName }) // checking if the file exist
    {
        cout << "The file : " << fileName << " does not exist!" << endl;
        return 0;
    }

    LinkedListString* countries = new LinkedListString(); // the list of all the countries
    LinkedListString* viruses = new LinkedListString(); // the list of all the viruses
    LinkedListCitizen* citizens = new LinkedListCitizen(); // the list of all the citizens
    LinkedListBloomFilter* bloomFilter = NULL; // the list of all the bloomFilters for every virus
    SkipList* skipList = NULL; // the list of all the skipLists for every virus


    ifstream name; // opening the file that contains the citizen Records
    name.open(fileName);

    while (getline(name, line)) // while we have lines in the file, get the line and store it in the variable line
    {
        int numWords;                                            // will store the size of the array that I keep every word of the line
        string* wordsOfLine = stringSeperator(&line, &numWords); // wordsOfLine will point to the array of strings that contains every word of the line
        if (wordsOfLine == NULL)
        {
            cout << "Error wordsOfLine is NULL !" << endl;
            return 0;
        }

        if (!errorChecking(numWords, wordsOfLine, citizens)) // checking that the record has not any errors
        {
            delete[] wordsOfLine;
            continue;
        }

        // checking if i have already the country in the list
        LinkedListStringNode* country = countries->findNode(wordsOfLine[3]);
        if (country == NULL) // the country does not exist in the list so i will insert it
        {
            countries->insertNode(wordsOfLine[3]);
            country = countries->findNode(wordsOfLine[3]);
        }

        // checking if i have already the virus in the list
        LinkedListStringNode* virus = viruses->findNode(wordsOfLine[5]);
        if (virus == NULL) // the virus does not exist in the list so i will insert it
        {
            viruses->insertNode(wordsOfLine[5]);
            virus = viruses->findNode(wordsOfLine[5]);
            if (bloomFilter == NULL) // creating a bloom filter for the specific virus
                bloomFilter = new LinkedListBloomFilter(virus, bloomSize);
            else
                bloomFilter->insert(virus, bloomSize);
            if (skipList == NULL) // creating a skip list for the specific virus
                skipList = new SkipList(virus);
            else
                skipList->insertVirus(virus);
        }

        CitizenRecord* citizen;

        if (numWords == 8) // if it has 8 words it means it has also date
            citizen = new CitizenRecord(stoi(wordsOfLine[0]), wordsOfLine[1], wordsOfLine[2], country, stoi(wordsOfLine[4]), virus, wordsOfLine[6], wordsOfLine[7]);
        else if (numWords == 7) // if it has 7 words it means it has not date
            citizen = new CitizenRecord(stoi(wordsOfLine[0]), wordsOfLine[1], wordsOfLine[2], country, stoi(wordsOfLine[4]), virus, wordsOfLine[6], "");

        int success = citizens->insertNode(&citizen);
        if ((success) && (wordsOfLine[6].compare("YES") == 0)) // if the citizen inserted correctly and has done the vaccine we insert the citizen to the bloom filter and vaccine skipList of the specific virus
        {
            bloomFilter->getFilter(virus)->insert(stoi(wordsOfLine[0]));
            skipList->findVirus(virus)->insertNodeVaccinated(citizen);
        }
        else if ((success) && (wordsOfLine[6].compare("NO") == 0)) // we insert the citizen to the non vaccinated skipList of the specific virus
            skipList->findVirus(virus)->insertNodeNonVaccinated(citizen);

        delete[] wordsOfLine;
    }
    commandInterface(countries, viruses, citizens, bloomFilter, skipList, bloomSize); // The interface for the commands that the user can give

    delete countries;
    delete viruses;
    delete citizens;
    delete bloomFilter;
    delete skipList;
    cout << "                             ---  THE VACCINE MONITOR PROGRAM ENDED  ---                                 " << endl;

    return 0;
}