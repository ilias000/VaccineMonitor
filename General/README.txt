System Programming - 1st Project, Spring Semester 2021

Name :     Ilias
Surename : Piotopoulos
A.M. :     1115201800335


~GENERAL INSTRUCTIONS~

I assume that :
- The execution command will be :     
    ./vaccineMonitor -c citizenRecordsFile –b bloomSize   OR  ./vaccineMonitor –b bloomSize -c citizenRecordsFile  

- The citizenRecordsFile will be given with out the .txt extension.  
- To change the name of the citizenRecordsFile to another file, it should be changed at the Makefile the value of :  FILE = -c inputFile  TO FILE = -c *new_name_file*

- To change the size of the bloom filter in *bytes*, it should be changed at the Makefile the value of :      
BLOOMSIZE = -b 100000  TO  BLOOMSIZE = -b *new_size_of_bloom_filter_in_bytes*

- To change the execution command from :  
./vaccineMonitor -c citizenRecordsFile –b bloomSize
 TO  
./vaccineMonitor –b bloomSize -c citizenRecordsFile
 it should be changed at the Makefile the value of :  
 val:
	valgrind ./$(PROGRAM) $(FILE) $(BLOOMSIZE)
 run:
	./$(PROGRAM) $(FILE) $(BLOOMSIZE)
TO
 val:
	valgrind ./$(PROGRAM) $(BLOOMSIZE) $(FILE)
 run:
	./$(PROGRAM) $(BLOOMSIZE) $(FILE)


~Compilation & Execution~

- Compilation Command : make
- Execution Command :
    make run
    OR
    ./vaccineMonitor -c inputFile -b 100000   
    OR 
    ./vaccineMonitor -b 100000 -c inputFile  
- Execution Command with Valgrind : make val
- Clean command : make clean

~Script~

General Informations

- The execution command will be :   
  ./testFile.sh virusesFile.txt countriesFile.txt 100 1  

- I check if i have given all 4 arguments needed.  
- I check if the virusesFile exists.  
- I check if the countriesFile exists.  
- If the user wants duplicate ids i found for every record a random number from 0 to 5 and if it is 1 then the specific record will have for id an id that has been already used else will have a different one.  
- The records that are duplicate have the same citizenID, firstName, lastName, country and age.    
- If for the specific record the citizen has not done the vaccine i found a random number from 0 to 5 and if it is 1 then the record will also have a date so it will be inconsistent.
- If i have to create more than 10.000 records and i have already used 10.000 different id regardless if the user wants duplicate or not, the other records will be duplicate because i dont have other id to use.

~VaccineMonitor~

General Informations

- I have separate my code in folders so it is easier to read use and maintain.
- I have complete all the parts of the Project corectly except from the commands :
 /populationStatus [country] virusName date1 date2 
 and
 /popStatusByAge [country] virusName date1 date2
 because i did not had enough time.


 VaccineMonitor.cpp

  - I have two LinkedListString one for the countries and one for the viruses so if the same country or virus comes I don't have to allocate different memory.
  - I have another list LinkedListCitizen where I keep for every citizen the id, firstName, lastName, age ,country (it's a pointer to the LinkedListString of the specific country) and another list with all the viruses that I have information for the specific citizen.
  - I made a function StringSeparetor that I use to separate the record to words.
  - I use a function ErrorsChecking to check that the record has not errors.
  - After I have inisialize the data structures for every record I call the function CommandInterface that is responsible for the commands that the user will give.


 BloomFilter

 This folder has all the files for the bloomFilter.



 CitizenRecord

 This folde
 
 
 Functions




 LinkedList




 SkipList

 - The layers will be at most 9.
- At the LinkedListCitizen at InsertNodeCommand function returns :

0. if the id has different credentials
1. if the insertion is done right
2. if the citizen has already the virus at his/her list with YES and the vaccinated of the new record is YES
3. if the citizen has already the virus at his/her list with YES and the vaccinated of the new record is NO
4. if the citizen has already the virus at his/her list with NO and the vaccinated of the new record is YES
5. if the citizen has already the virus at his/her list with NO and the vaccinated of the new record is NO

