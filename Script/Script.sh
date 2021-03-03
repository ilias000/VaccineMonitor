#! /bin/bash

countriesNamesFile=$1
virusesNamesFile=$2
maxRecordsNumber=$3
duplicatesAllowed=$4 # 1 = true, 0 = False

#read from the file that contains the countries, the countries and inserting them to the array
declare -a countriesArray;

while IFS= read -r line; do
    countriesArray+=("$line")
done < $countriesNamesFile

declare -a virusesArray;

while IFS= read -r line; do
    virusesArray+=("$line")
done < $virusesNamesFile


declare -a idesArray;

#ftiaxnw ta records
for (( i=0; i<$maxRecordsNumber; i++ )) do
    firstNameLength=$((3 + $RANDOM % 12))
    lastNameLength=$((3 + $RANDOM % 12))
    age=$((1 + $RANDOM % 120))
    firstName=$(head -3 /dev/urandom | tr -cd '[:alpha:]' | cut -c -$firstNameLength)
    lastName=$(head -3 /dev/urandom | tr -cd '[:alpha:]' | cut -c -$lastNameLength)
    countriesArrayLength=${#countriesArray[@]}
    virusesArrayLength=${#virusesArray[@]}
    randomCountryIndex=$(($RANDOM % $countriesArrayLength))
    randomVirusIndex=$(($RANDOM % $virusesArrayLength))
    country=${countriesArray[randomCountryIndex]}
    virus=${virusesArray[randomVirusIndex]}
    hasDoneVaccine=$(($RANDOM % 2))
    date="$((1 + $RANDOM % 30))-$((1 + $RANDOM % 12))-$((2010 + $RANDOM % 10))"

    duplicate=0
    if [ $duplicatesAllowed -eq 1 ]
    then
        duplicate=$(($RANDOM % 2))
    fi

    lengthIdesArray=${#idesArray[@]}
    if [ $duplicate -eq 0 ]
    then
        isUnique=1
        while [ $isUnique -ne 0 ]
        do
            # id=$((1 + $RANDOM % 9999))
            # for (( k=0; k<$lengthIdesArray; k++ )) do
            #     if [ $id -eq ${idesArray[k]} ]
            #     then
            #         isUnique=0
            #         break
            #     fi
            # done
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