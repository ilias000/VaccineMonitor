FILE = -c inputFile 
BLOOMSIZE = -b 100000

CC = g++
CFLAGS = -Wall -g
 
PROGRAM = vaccineMonitor
 
OBJS = VaccineMonitor.o Functions.o CitizenRecord.o

$(PROGRAM): clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM) 

VaccineMonitor.o: VaccineMonitor.cpp Functions.h CitizenRecord.h
	$(CC) $(CFLAGS) -c VaccineMonitor.cpp 

Functions.o: Functions.cpp Functions.h
	$(CC) $(CFLAGS) -c Functions.cpp 

CitizenRecord.o: CitizenRecord.cpp CitizenRecord.h
	$(CC) $(CFLAGS) -c CitizenRecord.cpp 
 
clean:
	rm -f $(PROGRAM) $(OBJS)

run: 
	./$(PROGRAM) $(FILE) $(BLOOMSIZE)

