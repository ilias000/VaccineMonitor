#include <string>
#include <fstream>
#include <cstring>
#include <sys/stat.h>

#include <iostream>
using namespace std;

#include "Functions/Functions.h"
#include "CitizenRecord/CitizenRecord.h"

int main(int argc, char *argv[])
{
    cout << "                             --- THE VACCINE MONITOR PROGRAM STARTED ---                                 " << endl;
    string extensionOfFileName = (".txt");
    string fileName;
    int bloomSize; // size of bloom filter (bytes)
    string line;   // will store one line of the file each time

    if (argc < 5) // checking the general form of the execution command
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
    struct stat buffer;

    int fileNameLength = fileName.length();
    char *fileNameChar = new char[fileNameLength + 1];
    strcpy(fileNameChar, fileName.c_str());
    if (stat(fileNameChar, &buffer) != 0) // checking if the file exist
    {
        cout << "The file : " << fileName << "does not exist!" << endl;
        delete fileNameChar;
        return 0;
    }
    delete fileNameChar;

    ifstream name; // opening the file that contains the citizen Records
    name.open(fileName);

    while (getline(name, line)) // while we have lines in the file, get the line and store it in the variable line
    {
        int numWords;                                            // will store the size of the array that I keep every word of the line
        string *wordsOfLine = stringSeperator(&line, &numWords); // wordsOfLine will point to the array of strings that contains every word of the line
        if (wordsOfLine == NULL)
            return 0;

        // for (int i = 0; i < numWords; i++)
        //     cout << wordsOfLine[i] << " ";
        // cout << endl;
        CitizenRecord *citizen; // creating a citizen

        if (numWords == 8) // if it has 8 it means it has also date
            citizen = new CitizenRecord(stoi(wordsOfLine[0]), wordsOfLine[1], wordsOfLine[2], wordsOfLine[3], stoi(wordsOfLine[4]), wordsOfLine[5], wordsOfLine[6], wordsOfLine[7]);
        else // it has not date
            citizen = new CitizenRecord(stoi(wordsOfLine[0]), wordsOfLine[1], wordsOfLine[2], wordsOfLine[3], stoi(wordsOfLine[4]), wordsOfLine[5], wordsOfLine[6], "");

        citizen->print();
        cout << endl;
        delete[] wordsOfLine;
        delete citizen;
    }

    cout << "                             ---  THE VACCINE MONITOR PROGRAM ENDED  ---                                 " << endl;

    return 0;
}