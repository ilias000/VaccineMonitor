#!/bin/bash

if [ "$#" -ne 4 ]; then # checking if the number of arguments is correct
    echo "Illegal number of arguments"
    exit
else
    echo "Correct number of arguments"
fi

virusesNamesFile=$1 # taking the first argumnet and saving it to the virusesNamesFile

if [ ! -f "$virusesNamesFile" ]; then # checking if the file that contains the viruses names exist
    echo "$virusesNamesFile does not exist."
    exit
else
    echo "$virusesNamesFile does exist."
fi

countriesNamesFile=$2 # taking the second argumnet and saving it to the countriesNamesFile

if [ ! -f "$countriesNamesFile" ]; then # checking if the file that contains the countries names exist
    echo "$countriesNamesFile does not exist."
    exit
else
    echo "$countriesNamesFile does exist."
fi

maxRecordsNumber=$3 # taking the third argumnet and saving it to the maxRecordsNumber
duplicatesAllowed=$4 # taking the fourth argumnet and saving it to the duplicatesAllowed (1 = true, 0 = False)

declare -a countriesArray; # creating an array to store coutries names

while IFS= read -r line; do # read from the file countriesFile, the countries names and inserting them to the array
    countriesArray+=("$line")
done < $countriesNamesFile

declare -a virusesArray; # creating an array to store viruses names

while IFS= read -r line; do # read from the file virusesFile, the viruses names and inserting them to the array
    virusesArray+=("$line")
done < $virusesNamesFile

declare -a citizensIdsArray; # creating an array to store the ids i use so i can choose an id from this array if i want duplicate
declare -A citizenIdMap # creating an associative array with key the ID and values citizenID, firstName, lastName, country, age

# creating the records
for (( i=0; i<$maxRecordsNumber; i++ )) do # for as many records as the user wants

    virus=${virusesArray[$(($RANDOM % ${#virusesArray[@]}))]} # finding a random index for virusesArray array and storing the name of the random virus
    hasDoneVaccine=$(($RANDOM % 2)) # randomly deciding if the citizen has done the vaccine or not
    lengthcitizensIdsArray=${#citizensIdsArray[@]} # storing the size of the citizensIdsArray array
    duplicate=0

    #VALE AN EXEIS FTIAXEI PANW APO 10.000 OXI DUPLICATE NA FTIAXNEI MONO DUPLICATE TA YPOLOIPA GIATI DEN EXEIS ALLA ID NA DWSEIS


    if [[ $duplicatesAllowed -eq 1 ]] && [[ $lengthcitizensIdsArray -ne 0 ]] # if the user wants duplicates and we have at least already one id
    then
        duplicate=$(($RANDOM % 5)) # deciding if the specific id will be duplicate or not (if duplicate == 1 it will be duplicate id)
    fi

    if [ $duplicate -ne 1 ] # if duplicate is 0 or 2 or 3 or 4 the id will not be duplicate
    then
        # i will find a random id [0,9999] but i have to check that is not duplicate
        isUnique=0 # is 0 so it will enter the while the first time (i convert the while to do while) 1 = is unique 0 = is not unique
        while [ $isUnique -eq 0 ] # while the id is not unique i will choose another random id
        do
            isUnique=1
            id=$(($RANDOM % 10000)) # choosing a random number [0, 9999] for the id
            if [ ${citizenIdMap[$id]+_} ] # if exists already i have used this id
            then
                isUnique=0 # the id is not unique
                break
            fi
        done
        firstName=$(cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w $((3 + $RANDOM % 10)) | head -n 1) # taking random number [3, 12] random letters to create the firstName
        lastName=$(cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w $((3 + $RANDOM % 10)) | head -n 1) # taking random number [3, 12]  random letters to create the lastName
        country=${countriesArray[$(($RANDOM % ${#countriesArray[@]}))]} # finding a random index for countriesArray array and storing the name of the random country
        age=$((1 + $RANDOM % 120)) # random number [1, 120] for the age
        citizenIdMap+=([$id]="$id $firstName $lastName $country $age")
        citizensIdsArray+=("$id") # inserting the new id to the array of ids 
    else # the duplicate is 1 so the id will be duplicate
        id=${citizensIdsArray[$(($RANDOM % $lengthcitizensIdsArray))]} # choosing a random id from the ids that i already have used
    fi

    destinationFilePath=../General/inputFile.txt
    if [ $hasDoneVaccine -eq 0 ] # if the citizen has not done the vaccine 
    then
        dateProbability=$(($RANDOM % 5)) # deciding if the specific citizen record will have date while the citizen has not done the vaccine (if dateProbability == 1 it will have date so the record will be inconsistent)
        if [ $dateProbability -ne 1 ] # if dateProbability is 0 or 2 or 3 or 4 the record will not have date
        then
            echo ${citizenIdMap[$id]} $virus "NO" >> $destinationFilePath
        else # the dateProbability is 1 so the record will have date (so it will be inconsistent)
            date="$((1 + $RANDOM % 30))-$((1 + $RANDOM % 12))-$((2010 + $RANDOM % 11))" # randomly choosing a date that the citizen has done the vaccine [2010, 2020]
            echo ${citizenIdMap[$id]} $virus "NO" $date >> $destinationFilePath
        fi
    else # if the citizen has done the vaccine
        date="$((1 + $RANDOM % 30))-$((1 + $RANDOM % 12))-$((2010 + $RANDOM % 11))" # randomly choosing a date that the citizen has done the vaccine [2010, 2020]
        echo ${citizenIdMap[$id]} $virus "YES" $date >> $destinationFilePath
    fi
done
echo "The file was created successfully at : " $destinationFilePath