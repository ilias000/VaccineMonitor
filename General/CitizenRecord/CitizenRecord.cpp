#include "CitizenRecord.h"

#include <iostream>
using namespace std;

CitizenRecord::CitizenRecord(int id, string firstName, string lastName, string country, int age, string virusName, string vaccinated, string date) : id(id), firstName(firstName), lastName(lastName), country(country), age(age), virusName(virusName), vaccinated(vaccinated), date(date)
{
}

CitizenRecord::~CitizenRecord()
{
}

void CitizenRecord::print()
{
    cout << id << " " << firstName << " " << lastName << " " << country << " " << age << " " << virusName << " " << vaccinated << " " << date << endl;
}