#ifndef CITIZENRECORDS_H
#define CITIZENRECORDS_H

#include <string>

#include <iostream>
using namespace std;

class CitizenRecord
{
    int id;
    string firstName;
    string lastName;
    string country;
    int age;
    string virusName;
    string vaccinated;
    string date;

public:
    CitizenRecord(int, string, string, string, int, string, string, string);
    ~CitizenRecord();
    void print();
};

#endif