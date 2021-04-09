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

