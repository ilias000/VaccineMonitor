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


 ~VaccineMonitor.cpp~

  - I have two LinkedListString one for the countries and one for the viruses so if the same country or virus comes I don't have to allocate different memory.
  - I have another list LinkedListCitizen where I keep for every citizen the id, firstName, lastName, age ,country (it's a pointer to the LinkedListString of the specific country) and another list with all the viruses that I have information for the specific citizen.
  - I made a function StringSeparetor that I use to separate the record to words.
  - I use a function ErrorsChecking to check that the record has not errors.
  - After I have inisialize the data structures for every record I call the function CommandInterface that is responsible for the commands that the user will give.


 ~BloomFilter~

  - For the BloomFilter I have class LinkedListBloomFilter that has a pointer LinkedListStringNode that points at the node of the specific virus that is the BloomFilter for, a pointer BloomFilter that points to the filter and a pointer to the next BloomFilter.
  The BloomFilter is a class that has an integer size (bits of bloom filter) and a pointer char that points at the filter.


~CitizenRecord~

  - The CitizenRecord is a class that has for a citizen the id, firstname, lastname, a pointer LinkedListStringNode (that points to node that has the information for the specific country, so that I do not allocate extra memory), the age and a pointer LinkedListVaccine (that has for every virus that we have information for the specific citizen the information for the specific virus).
  
  
~Functions~

  - I have the functions :
                            - StringSeparator : takes a string and separates it to words.
                            - ErrorChecking : takes a record and checks :
                                                                          - the number of words of the record not to be < 7 or > 8.
                                                                          - not to be 7 words with YES.
                                                                          - not to be 8 words with NO.
                                                                          - not to be the id < 0 or > 9999.
                                                                          - the age not to be < 1 or > 120.
                                                                          - the 7th word to be Yes or NO.
                                                                          - if the 7th word is YES calls the function CheckDate for the 8th word that is the date.

- CheckDate : tekes a string and checks :
                                          - if it has only numbers and -
                                          - that the first and the last characters are numbers
                                          - the size of the string
                                          - that is in one of these forms : (d-mm-yyyy, d-m-yyyy, dd-mm-yyyy, dd-m-yyyy)
                                          - that the day is between 1 and 30
                                          - that the month is between 1 and 12
                                          - that the year is between 1900 and 2021.

- CommandInterface : reads the command that the user will give and if it is in right form executes the aditional energies.
- These commands (/populationStatus [country] virusName date1 date2 and /popStatusByAge [country] virusName date1 date2) does not work.

~LinkedList~

            ~LinkedListCitizen~

           - The LinkedListCitizen is a class that represents a list of LinkedListCitizenNode.
           - The LinkedListCitizenNode is a class that has a pointer to CitizenRecord and a pointer to the next node.
           - So at these list I will have the information that I need for every citizen.

           - The InsertNodeCommand function returns :
                    0. if for the specific id the new record has different credentials than the old one
                    1. if the insertion is done right
                    2. if the citizen has already the virus at his/her list with YES and the vaccinated of the new record is YES
                    3. if the citizen has already the virus at his/her list with YES and the vaccinated of the new record is NO
                    4. if the citizen has already the virus at his/her list with NO and the vaccinated of the new record is YES
                    5. if the citizen has already the virus at his/her list with NO and the vaccinated of the new record is NO

            ~LinkedListString~

            - The LinkedListString is a list of LinkedListStringNode.
            - The LinkedListStringNode has a string and a pointer to the next node.
            - I use these list to keep the names of the viruses, countries so when I want to use the node again of the specific virus/country simply I will put a pointer to these node.

            ~LinkedListVaccine~

            - The LinkedListVaccine is a list of LinkedListVaccineNode.
            - The LinkedListVaccineNode has a pointer to LinkedListStringNode that will point at the node of the specific virus, a string that keeps if the citizen has done the vaccine or not, a string that has the date that the vaccine was done and a pointer to the next node.
            - These list is used at the CitizenRecord class to keep the informations for all the viruses of the specific citizen.

~SkipList~
          General : 
                    - The layers will be at most 9.

          - I have these classes :
                              - ~SkipList~ : is a list of SkipList where every SkipList refers to one virus and it has a pointer to SkipListLayer that points to the first layer for the vaccinated, a pointer to SkipListLayer that points at the most first layer for the nonvaccinated and a pointer to the next SkipList.
                              - ~SkipListLayer~ : is a class that has a pointer SkipListNode that points at the first node of the specific layer, a pointer SkipListNode that points at the last node of the specific layer, a pointer SkipListLayer that points to the below layer and an integer that is the number of these layer.
                              - ~SkipListNode~ : is a class that has a pointer CitizenRecord that points to the information of the specific citizen, a pointer SkipListNode that points to the next node and a pointer SkipListNode that points to the below node.
 

