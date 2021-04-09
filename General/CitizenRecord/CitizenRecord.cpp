#include "CitizenRecord.h"

#include "../LinkedList/LinkedListString/LinkedListString.h"

#include <iostream>
using namespace std;

CitizenRecord::CitizenRecord(int id, string firstName, string lastName, LinkedListStringNode* country, int age, LinkedListStringNode* virusName, string vaccinated, string date) : id(id), firstName(firstName), lastName(lastName), country(country), age(age)
{
    viruses = new LinkedListVaccine();
    viruses->insertNode(virusName, vaccinated, date);
}

CitizenRecord::~CitizenRecord()
{
    delete viruses;
}

void CitizenRecord::print() // prints the record
{
    cout << id << " " << firstName << " " << lastName << " " << country->name << " " << age << " : ";
    viruses->print();
}

void CitizenRecord::printInfo() // prints the information of the citizen (not the viruses)
{
    cout << id << " " << firstName << " " << lastName << " " << country->name << " " << age << " : ";
}