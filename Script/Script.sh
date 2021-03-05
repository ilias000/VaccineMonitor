#! /bin/bash

countriesNamesFile=$1 # taking the first argumnet and saving it to the countriesNamesFile
virusesNamesFile=$2 # taking the second argumnet and saving it to the virusesNamesFile
maxRecordsNumber=$3 # taking the third argumnet and saving it to the maxRecordsNumber
duplicatesAllowed=$4 # taking the fourth argumnet and saving it to the maxRecordsNumber (1 = true, 0 = False)


declare -a countriesArray; # creating an array to store coutries names

while IFS= read -r line; do # read from the file countriesNames that contains , the countries names and inserting them to the array
    countriesArray+=("$line")
done < $countriesNamesFile

declare -a virusesArray; # creating an array to store viruses names

while IFS= read -r line; do # read from the file virusesNames that contains, the viruses names and inserting them to the array
    virusesArray+=("$line")
done < $virusesNamesFile

declare -a idesArray; # creating an array to store the ides i use so i know if i have already use an id 

# creating the records
for (( i=0; i<$maxRecordsNumber; i++ )) do # for as many records as the user wants

    firstNameLength=$((3 + $RANDOM % 10)) # random number [3, 12] for the length of the first name
    lastNameLength=$((3 + $RANDOM % 10)) # random number [3, 12] for the length of the last name
    age=$((1 + $RANDOM % 120)) # random number [1, 120] for the age

    firstName=$(cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w $firstNameLength | head -n 1) # taking firstNameLength random letters to create the firstName
    lastName=$(cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w $lastNameLength | head -n 1) # taking LastNameLength random letters to create the lastName

    countriesArrayLength=${#countriesArray[@]} # storing the size of the countriesArray array
    virusesArrayLength=${#virusesArray[@]} # storing the size of the virusesArray array

    randomCountryIndex=$(($RANDOM % $countriesArrayLength)) # finding a random index for countriesArray array
    randomVirusIndex=$(($RANDOM % $virusesArrayLength)) # finding a random index for virusesArray array

    country=${countriesArray[randomCountryIndex]} # storing the name of the random country
    virus=${virusesArray[randomVirusIndex]} # storing the name of the random virus

    hasDoneVaccine=$(($RANDOM % 2)) # randomly deciding if the citizen has done the vaccine or not

    lengthIdesArray=${#idesArray[@]} # storing the size of the idesArray array
    duplicate=0
    if [[ $duplicatesAllowed -eq 1 ]] && [[ $lengthIdesArray -ne 0 ]] # if the user wants duplicates and we have at least already one id
    then
        duplicate=$(($RANDOM % 5)) # deciding if the specific id will be duplicate or not (if duplicate == 1 it will be duplicate id)
    fi

    if [ $duplicate -ne 1 ] # if duplicate is 0 or 2 or 3 or 4 the id will not be duplicate
    then
        # i will find a random id [1,9999] but i have to check that is not duplicate
        isUnique=0 # is 0 so it will enter the while the first time (i convert the while to do while) 1 = is unique 0 = is not unique
        while [ $isUnique -eq 0 ] # while the id i choose is not unique i will choose another random id
        do
            isUnique=1
            id=$((1 + $RANDOM % 9999)) # choosing a random number [1, 9999] for the id
            for (( k=0; k<$lengthIdesArray; k++ )) do # checking every id that i already used to see if it is the same with the one i chose
                if [ $id -eq ${idesArray[k]} ]
                then
                    isUnique=0 # the id is not unique
                    break
                fi
            done
        done
    else # the duplicate is 1 so the id will be duplicate
        randomId=$(($RANDOM % $lengthIdesArray)) # choosing a random id from the ides that i already have used
        id=${idesArray[randomId]}
    fi
    
    idesArray+=("$id") # inserting the new id to the array of ides 
    if [ $hasDoneVaccine -eq 0 ] # if the citizen has not done the vaccine 
    then
        echo $id $firstName $lastName $country $age "NO" $virus >> ../main/citizenRecordsFile.txt
    else # if the citizen has done the vaccine
        date="$((1 + $RANDOM % 30))-$((1 + $RANDOM % 12))-$((2010 + $RANDOM % 11))" # randomly choosing a date that the citizen has done the vaccine [2010, 2020]
        echo $id $firstName $lastName $country $age "YES" $virus $date >> ../main/citizenRecordsFile.txt
    fi
done