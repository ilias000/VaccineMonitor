#! /bin/bash

countriesNamesFile=$1 # taking the first argumnet and saving it to the countriesNamesFile
virusesNamesFile=$2 # taking the second argumnet and saving it to the virusesNamesFile
maxRecordsNumber=$3 # taking the third argumnet and saving it to the maxRecordsNumber
duplicatesAllowed=$4 # taking the fourth argumnet and saving it to the maxRecordsNumber (1 = true, 0 = False)


declare -a countriesArray; # creating an array to store coutries names

while IFS= read -r line; do # read from the file that contains the countriesNames, the countries names and inserting them to the array
    countriesArray+=("$line")
done < $countriesNamesFile

declare -a virusesArray; # creating an array to store viruses names

while IFS= read -r line; do # read from the file that contains the virusesNames, the viruses names and inserting them to the array
    virusesArray+=("$line")
done < $virusesNamesFile


declare -a idesArray; # creating an array to store the ides i use so i know if i have already use an id 

# creating the records
for (( i=0; i<$maxRecordsNumber; i++ )) do # for as many records as the user wants

    firstNameLength=$((3 + $RANDOM % 10)) # random number [3, 12] for the length of the first name
    lastNameLength=$((3 + $RANDOM % 10)) # random number [3, 12] for the length of the last name
    age=$((1 + $RANDOM % 120)) # random number [1, 120] for the length of the last name

    firstName=$(head -3 /dev/urandom | tr -cd '[:alpha:]' | cut -c -$firstNameLength) # taking firstNameLength random numbers to create the firstName
    lastName=$(head -3 /dev/urandom | tr -cd '[:alpha:]' | cut -c -$lastNameLength) # taking LastNameLength random numbers to create the lastName
    
    countriesArrayLength=${#countriesArray[@]}
    virusesArrayLength=${#virusesArray[@]}
    randomCountryIndex=$(($RANDOM % $countriesArrayLength))
    randomVirusIndex=$(($RANDOM % $virusesArrayLength))
    country=${countriesArray[randomCountryIndex]}
    virus=${virusesArray[randomVirusIndex]}
    hasDoneVaccine=$(($RANDOM % 2))
    date="$((1 + $RANDOM % 30))-$((1 + $RANDOM % 12))-$((2010 + $RANDOM % 10))"


    lengthIdesArray=${#idesArray[@]}
    duplicate=0
    if [[ $duplicatesAllowed -eq 1 ]] && [[ $lengthIdesArray -ne 0 ]]
    then
        duplicate=$(($RANDOM % 5))
    fi

    if [ $duplicate -ne 4 ]
    then
        isUnique=1
        while [ $isUnique -ne 0 ]
        do
            id=$((1 + $RANDOM % 9999))
            isUnique=0
            for (( k=0; k<$lengthIdesArray; k++ )) do
                if [ $id -eq ${idesArray[k]} ]
                then
                    isUnique=1
                    break
                fi
            done
        done
    else
        randomId=$(($RANDOM % $lengthIdesArray))
        id=${idesArray[randomId]}
    fi
    
    idesArray+=("$id")
    if [ $hasDoneVaccine -eq 0 ]
    then
        echo $id $firstName $lastName $country $age "NO" $virus >> ../main/citizenRecordsFile.txt
    else
        echo $id $firstName $lastName $country $age "YES" $virus $date >> ../main/citizenRecordsFile.txt
    fi
done