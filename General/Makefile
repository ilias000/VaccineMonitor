FILE = -c inputFile 
BLOOMSIZE = -b 100000

CC = g++ -std=c++11
CFLAGS = -Wall -g

PROGRAM = vaccineMonitor

OBJS = VaccineMonitor.o Functions.o CitizenRecord.o LinkedListCitizen.o LinkedListString.o LinkedListVaccine.o BloomFilter.o SkipList.o

$(PROGRAM): clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

VaccineMonitor.o: VaccineMonitor.cpp
	$(CC) $(CFLAGS) -c $?

Functions.o: Functions/Functions.cpp
	$(CC) $(CFLAGS) -c $?

CitizenRecord.o: CitizenRecord/CitizenRecord.cpp
	$(CC) $(CFLAGS) -c $? 

LinkedListCitizen.o: LinkedList/LinkedListCitizen/LinkedListCitizen.cpp
	$(CC) $(CFLAGS) -c $?

LinkedListString.o: LinkedList/LinkedListString/LinkedListString.cpp
	$(CC) $(CFLAGS) -c $?
	
LinkedListVaccine.o: LinkedList/LinkedListVaccine/LinkedListVaccine.cpp
	$(CC) $(CFLAGS) -c $?

BloomFilter.o: BloomFilter/BloomFilter.cpp
	$(CC) $(CFLAGS) -c $?

SkipList.o: SkipList/SkipList.cpp
	$(CC) $(CFLAGS) -c $?

clean:
	rm -f $(PROGRAM) $(OBJS)

val:
	valgrind ./$(PROGRAM) $(FILE) $(BLOOMSIZE)
run:
	./$(PROGRAM) $(FILE) $(BLOOMSIZE)

