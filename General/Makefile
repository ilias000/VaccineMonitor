FILE = -c inputFile 
BLOOMSIZE = -b 100000

CC = g++ -std=c++11
CFLAGS = -Wall -g

PROGRAM = vaccineMonitor

OBJS = VaccineMonitor.o Functions.o CitizenRecord.o LinkedListCitizen.o LinkedListString.o LinkedListVaccine.o

$(PROGRAM): clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

VaccineMonitor.o: VaccineMonitor.cpp Functions/Functions.h CitizenRecord/CitizenRecord.h LinkedList/LinkedListString/LinkedListString.h LinkedList/LinkedListCitizen/LinkedListCitizen.h
	$(CC) $(CFLAGS) -c VaccineMonitor.cpp 

Functions.o: Functions/Functions.cpp Functions/Functions.h
	$(CC) $(CFLAGS) -c Functions/Functions.cpp 

CitizenRecord.o: CitizenRecord/CitizenRecord.cpp CitizenRecord/CitizenRecord.h
	$(CC) $(CFLAGS) -c CitizenRecord/CitizenRecord.cpp 

LinkedListCitizen.o: LinkedList/LinkedListCitizen/LinkedListCitizen.cpp LinkedList/LinkedListCitizen/LinkedListCitizen.cpp
	$(CC) $(CFLAGS) -c LinkedList/LinkedListCitizen/LinkedListCitizen.cpp

LinkedListString.o: LinkedList/LinkedListString/LinkedListString.cpp LinkedList/LinkedListString/LinkedListString.h
	$(CC) $(CFLAGS) -c LinkedList/LinkedListString/LinkedListString.cpp
	
LinkedListVaccine.o: LinkedList/LinkedListVaccine/LinkedListVaccine.cpp LinkedList/LinkedListVaccine/LinkedListVaccine.h
	$(CC) $(CFLAGS) -c LinkedList/LinkedListVaccine/LinkedListVaccine.cpp
	
clean:
	rm -f $(PROGRAM) $(OBJS)

val:
	valgrind ./$(PROGRAM) $(FILE) $(BLOOMSIZE)