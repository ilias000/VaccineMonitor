#include "Functions.h"

#include <sstream>
#include <string>
#include <iostream>
#include <ctime>
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

void commandInterface(LinkedListString* countries, LinkedListString* viruses, LinkedListCitizen* citizens, LinkedListBloomFilter* bloomFilter, SkipList* skipList, int bloomSize)
{
    do
    {
        string command;
        getline(cin, command);

        int numWords;                                            // will store the size of the array that I keep every word of the line
        string* wordsOfCommand = stringSeperator(&command, &numWords); // wordsOfCommand will point to the array of strings that contains every word of the line
        if (wordsOfCommand == NULL)
        {
            cout << "Error wordsOfLine is NULL !" << endl;
            return;
        }

        if (numWords >= 1)
        {
            if (wordsOfCommand[0].compare("/vaccineStatusBloom") == 0)
            {
                cout << " Command : /vaccineStatusBloom" << endl;
                if (numWords == 3)
                {
                    if (viruses->findNode(wordsOfCommand[2]) != NULL) // if the virus exists
                    {
                        if (bloomFilter->getFilter(viruses->findNode(wordsOfCommand[2]))->find(stoi(wordsOfCommand[1])))
                            cout << "MAYBE" << endl;
                        else
                            cout << "NOT VACCINATED" << endl;
                    }
                    else
                        cout << "NOT VACCINATED" << endl;
                }
                else
                    cout << "ERROR: citizenId virusName not found !" << endl;
            }
            else if (wordsOfCommand[0].compare("/vaccineStatus") == 0)
            {
                cout << " Command : /vaccineStatus" << endl;
                if (numWords == 3)
                {
                    if (skipList->findVirus(wordsOfCommand[2]) != NULL)
                    {
                        SkipListNode* node = skipList->findVirus(wordsOfCommand[2])->findNodeVaccinated(stoi(wordsOfCommand[1]));
                        if (node != NULL)
                        {
                            cout << "VACCINATED ON " << node->getCitizen()->getViruses()->findNode(wordsOfCommand[2])->date << endl;
                        }
                        else
                            cout << "NOT VACCINATED" << endl;

                    }
                    else
                        cout << "NOT VACCINATED" << endl;
                }
                else if (numWords == 2)
                {
                    LinkedListStringNode* currentVirus = viruses->getStart();
                    while (currentVirus != NULL)
                    {
                        cout << currentVirus->name;
                        SkipListNode* node = skipList->findVirus(currentVirus->name)->findNodeVaccinated(stoi(wordsOfCommand[1]));
                        if (node != NULL)
                        {
                            if (node->getCitizen()->getViruses()->findNode(currentVirus->name)->vaccinated.compare("YES") == 0)
                                cout << " YES " << node->getCitizen()->getViruses()->findNode(currentVirus->name)->date << endl;
                            else
                                cout << " NO" << endl;
                        }
                        else
                            cout << " NO" << endl;
                        currentVirus = currentVirus->next;
                    }
                }
                else
                    cout << "ERROR: Give citizenId OR citizenId and virusName !" << endl;
            }
            else if ((wordsOfCommand[0].compare("/populationStatus") == 0) && ((numWords == 4) || (numWords == 5)))
            {
                if (numWords == 4)
                    cout << "The command is : " << wordsOfCommand[0] << " " << wordsOfCommand[1] << " " << wordsOfCommand[2] << " " << wordsOfCommand[3] << endl;
                else
                    cout << "The command is : " << wordsOfCommand[0] << " " << wordsOfCommand[1] << " " << wordsOfCommand[2] << " " << wordsOfCommand[3] << " " << wordsOfCommand[4] << endl;
                //TODO: Εάν υπάρχει ο ορισμός για date1 θα πρέπει να υπάρχει και ορισμός για date2, αλλιώς, θα τυπώνεται το μήνυμα λάθους ERROR στον χρήστη.
                // TODO: Να ελεγχει αν το date1 < date2
            }
            else if ((wordsOfCommand[0].compare("/popStatusByAge") == 0) && ((numWords == 4) || (numWords == 5)))
            {
                if (numWords == 4)
                    cout << "The command is : " << wordsOfCommand[0] << " " << wordsOfCommand[1] << " " << wordsOfCommand[2] << " " << wordsOfCommand[3] << endl;
                else
                    cout << "The command is : " << wordsOfCommand[0] << " " << wordsOfCommand[1] << " " << wordsOfCommand[2] << " " << wordsOfCommand[3] << " " << wordsOfCommand[4] << endl;
                //TODO: Εάν υπάρχει ο ορισμός για date1 θα πρέπει να υπάρχει και ορισμός για date2, αλλιώς, θα τυπώνεται το μήνυμα λάθους ERROR στον χρήστη.
                // TODO: Να ελεγχει αν το date1 < date2
            }
            else if ((wordsOfCommand[0].compare("/insertCitizenRecord") == 0))
            {
                cout << " Command : /insertCitizenRecord" << endl;
                if (numWords == 8)
                {
                    string* wordsOfRecord = new string[numWords - 1];
                    for (int i = 0; i < numWords - 1; i++)
                        wordsOfRecord[i] = wordsOfCommand[i + 1]; // taking the record
                    if (wordsOfCommand[7].compare("NO") == 0)
                    {
                        if (!errorChecking(numWords - 1, wordsOfRecord, citizens))
                        {
                            delete[] wordsOfCommand;
                            delete[] wordsOfRecord;
                            continue;
                        }

                        // checking if i have already the country in the list
                        LinkedListStringNode* country = countries->findNode(wordsOfRecord[3]);
                        if (country == NULL) // the country does not exist in the list so i will insert it
                        {
                            countries->insertNode(wordsOfRecord[3]);
                            country = countries->findNode(wordsOfRecord[3]);
                        }

                        // checking if i have already the virus in the list
                        LinkedListStringNode* virus = viruses->findNode(wordsOfRecord[5]);
                        if (virus == NULL) // the virus does not exist in the list so i will insert it
                        {
                            viruses->insertNode(wordsOfRecord[5]);
                            virus = viruses->findNode(wordsOfRecord[5]);
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

                        if (numWords - 1 == 8) // if it has 8 words it means it has also date
                            citizen = new CitizenRecord(stoi(wordsOfRecord[0]), wordsOfRecord[1], wordsOfRecord[2], country, stoi(wordsOfRecord[4]), virus, wordsOfRecord[6], wordsOfRecord[7]);
                        else if (numWords - 1 == 7) // if it has 7 words it means it has not date
                            citizen = new CitizenRecord(stoi(wordsOfRecord[0]), wordsOfRecord[1], wordsOfRecord[2], country, stoi(wordsOfRecord[4]), virus, wordsOfRecord[6], "");

                        int success = citizens->insertNodeCommand(&citizen);

                        if ((success == 1) && (wordsOfRecord[6].compare("YES") == 0)) // if the citizen inserted correctly and has done the vaccine we insert the citizen to the bloom filter of the specific virus
                        {
                            bloomFilter->getFilter(virus)->insert(stoi(wordsOfRecord[0]));
                            skipList->findVirus(virus)->insertNodeVaccinated(citizen);
                        }
                        else if ((success == 1) && (wordsOfRecord[6].compare("NO") == 0))
                            skipList->findVirus(virus)->insertNodeNonVaccinated(citizen);
                        else if ((success == 2) || (success == 3) || (success == 5))
                            delete citizen;
                        else if (success == 4)
                        {
                            skipList->findVirus(virus)->deleteNodeNonVaccinated(citizen->getId());
                            skipList->findVirus(virus)->insertNodeVaccinated(citizen);
                            bloomFilter->getFilter(virus)->insert(stoi(wordsOfRecord[0]));
                        }

                        delete[] wordsOfRecord;
                    }
                    else
                        cout << "ERROR: The record has 7 words but it is YES !" << endl;
                }
                else if (numWords == 9)
                {
                    string* wordsOfRecord = new string[numWords - 1];
                    for (int i = 0; i < numWords - 1; i++)
                        wordsOfRecord[i] = wordsOfCommand[i + 1]; // taking the record
                    if (wordsOfCommand[7].compare("YES") == 0)
                    {
                        if (!errorChecking(numWords - 1, wordsOfRecord, citizens))
                        {
                            delete[] wordsOfCommand;
                            delete[] wordsOfRecord;
                            continue;
                        }

                        // checking if i have already the country in the list
                        LinkedListStringNode* country = countries->findNode(wordsOfRecord[3]);
                        if (country == NULL) // the country does not exist in the list so i will insert it
                        {
                            countries->insertNode(wordsOfRecord[3]);
                            country = countries->findNode(wordsOfRecord[3]);
                        }

                        // checking if i have already the virus in the list
                        LinkedListStringNode* virus = viruses->findNode(wordsOfRecord[5]);
                        if (virus == NULL) // the virus does not exist in the list so i will insert it
                        {
                            viruses->insertNode(wordsOfRecord[5]);
                            virus = viruses->findNode(wordsOfRecord[5]);
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

                        if (numWords - 1 == 8) // if it has 8 words it means it has also date
                            citizen = new CitizenRecord(stoi(wordsOfRecord[0]), wordsOfRecord[1], wordsOfRecord[2], country, stoi(wordsOfRecord[4]), virus, wordsOfRecord[6], wordsOfRecord[7]);
                        else if (numWords - 1 == 7) // if it has 7 words it means it has not date
                            citizen = new CitizenRecord(stoi(wordsOfRecord[0]), wordsOfRecord[1], wordsOfRecord[2], country, stoi(wordsOfRecord[4]), virus, wordsOfRecord[6], "");

                        int success = citizens->insertNodeCommand(&citizen);
                        if ((success == 1) && (wordsOfRecord[6].compare("YES") == 0)) // if the citizen inserted correctly and has done the vaccine we insert the citizen to the bloom filter of the specific virus
                        {
                            bloomFilter->getFilter(virus)->insert(stoi(wordsOfRecord[0]));
                            skipList->findVirus(virus)->insertNodeVaccinated(citizen);
                        }
                        else if ((success == 1) && (wordsOfRecord[6].compare("NO") == 0))
                            skipList->findVirus(virus)->insertNodeNonVaccinated(citizen);
                        else if ((success == 2) || (success == 3) || (success == 5))
                            delete citizen;
                        else if (success == 4)
                        {   
                            skipList->findVirus(virus)->deleteNodeNonVaccinated(citizen->getId());
                            skipList->findVirus(virus)->insertNodeVaccinated(citizen);
                            bloomFilter->getFilter(virus)->insert(stoi(wordsOfRecord[0]));
                        }

                        delete[] wordsOfRecord;
                    }
                    else
                        cout << "ERROR: The record has 8 words but it is NO !" << endl;
                }
                else
                    cout << "ERROR: Give a right form for the record! " << endl;
            }
            else if (wordsOfCommand[0].compare("/vaccinateNow") == 0)
            {
                if (numWords == 7)
                {
                    string* wordsOfRecord = new string[8];
                    for (int i = 0; i < numWords - 1; i++)
                        wordsOfRecord[i] = wordsOfCommand[i + 1]; // taking the record

                    wordsOfRecord[6] = "YES";

                    time_t now = time(0); // Number of sec since January 1,1970

                    tm* ltm = localtime(&now);
                    string day = to_string(ltm->tm_mday);
                    string month = to_string(1 + ltm->tm_mon);
                    string year = to_string(1900 + ltm->tm_year);
                    wordsOfRecord[7] = day + "-" + month + "-" + year;

                    if (!errorChecking(8, wordsOfRecord, citizens))
                    {
                        delete[] wordsOfCommand;
                        delete[] wordsOfRecord;
                        continue;
                    }

                    // checking if i have already the country in the list
                    LinkedListStringNode* country = countries->findNode(wordsOfRecord[3]);
                    if (country == NULL) // the country does not exist in the list so i will insert it
                    {
                        countries->insertNode(wordsOfRecord[3]);
                        country = countries->findNode(wordsOfRecord[3]);
                    }

                    // checking if i have already the virus in the list
                    LinkedListStringNode* virus = viruses->findNode(wordsOfRecord[5]);
                    if (virus == NULL) // the virus does not exist in the list so i will insert it
                    {
                        viruses->insertNode(wordsOfRecord[5]);
                        virus = viruses->findNode(wordsOfRecord[5]);
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
                    
                    citizen = new CitizenRecord(stoi(wordsOfRecord[0]), wordsOfRecord[1], wordsOfRecord[2], country, stoi(wordsOfRecord[4]), virus, wordsOfRecord[6], wordsOfRecord[7]);

                    int success = citizens->insertNodeCommand(&citizen);
                    if (success == 1) // if the citizen inserted correctly and has done the vaccine we insert the citizen to the bloom filter of the specific virus
                    {
                        bloomFilter->getFilter(virus)->insert(stoi(wordsOfRecord[0]));
                        skipList->findVirus(virus)->insertNodeVaccinated(citizen);
                    }
                    else if ((success == 2) || (success == 3) || (success == 5))
                        delete citizen;
                    else if (success == 4)
                    {
                        skipList->findVirus(virus)->deleteNodeNonVaccinated(citizen->getId());
                        skipList->findVirus(virus)->insertNodeVaccinated(citizen);
                        bloomFilter->getFilter(virus)->insert(stoi(wordsOfRecord[0]));
                    }

                    delete[] wordsOfRecord;
                }
                else
                    cout << "ERROR: It should have (citizenID firstName lastName country age virusName)!" << endl;
            }
            else if (wordsOfCommand[0].compare("/list-nonVaccinated-Persons") == 0)
            {
                cout << " Command : /list-nonVaccinated-Persons" << endl;
                if (numWords == 2)
                {
                    if (skipList->findVirus(wordsOfCommand[1]) != NULL)
                    {
                        int count = 0;
                        skipList->findVirus(wordsOfCommand[1])->printNonVaccinatedLastLayer(count);
                        if (count == 0)
                            cout << "Everyone has been vaccinated! " << endl;
                    }
                    else
                        cout << "The virus does not exist!" << endl;
                }
                else
                    cout << "ERROR: Give virusName! " << endl;
            }
            else if ((wordsOfCommand[0].compare("/exit") == 0) && numWords == 1)
            {
                delete[] wordsOfCommand;
                return;
            }
            else
                cout << "ERROR : Wrong form of command !" << endl;
        }
        else 
            cout << "ERROR: NO COMMAND GIVEN!" << endl;
        if(wordsOfCommand != NULL)
            delete[] wordsOfCommand;
    } while (1);
}