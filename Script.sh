#! /bin/bash

countriesNamesFile=$1
virusesNamesFile=$2
maxRecordsNumber=$3
duplicatesAllowed=$4 # 1 true 

#diavazoume apo ta arxeiia kai ta vazoume stous pinakews
declare -a countriesArray;

while IFS= read -r line; do
    countriesArray+=("$line")
done < $countriesNamesFile

declare -a virusesArray;

while IFS= read -r line; do
    virusesArray+=("$line")
done < $virusesNamesFile


#ftiaxnw ta records
for (( i=0; i<$maxRecordsNumber; i++ )) do
    firstNameLength=((3 + $RANDOM % 12))
    lastNameLength=((3 + $RANDOM % 12))
    age=$((1 + $RANDOM % 120))
    firstName=$(head -3 /dev/urandom | tr -cd '[:alpha:]' | cut -c -$firstNameLength)
    lastName=$(head -3 /dev/urandom | tr -cd '[:alpha:]' | cut -c -$lastNameLength)
    countriesArrayLength=${#countriesArray[@]}
    virusesArrayLength=${#virusesArray[@]}
    randomCountryIndex=((0 + $RANDOM % $countriesArrayLength))
    randomVirusIndex=((0 + $RANDOM % $virusesArrayLength))
    country=${countriesArray[randomCountryIndex]}
    virus=${virusesArray[randomVirusIndex]}
    echo $firstName $lastName $country $age $virus >> citizenRecordsFile.txt
done