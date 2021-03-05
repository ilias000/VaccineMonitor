FILE = -c inputFile 
BLOOMSIZE = -b 100000

CC = g++
CFLAGS = -Wall -g

PROGRAM = vaccineMonitor

OBJS = VaccineMonitor.o Functions.o CitizenRecord.o

$(PROGRAM): clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)
	./$(PROGRAM) $(FILE) $(BLOOMSIZE)

VaccineMonitor.o: VaccineMonitor.cpp Functions/Functions.h CitizenRecord/CitizenRecord.h
	$(CC) $(CFLAGS) -c VaccineMonitor.cpp 

Functions.o: Functions/Functions.cpp Functions/Functions.h
	$(CC) $(CFLAGS) -c Functions/Functions.cpp 

CitizenRecord.o: CitizenRecord/CitizenRecord.cpp CitizenRecord/CitizenRecord.h
	$(CC) $(CFLAGS) -c CitizenRecord/CitizenRecord.cpp 

clean:
	rm -f $(PROGRAM) $(OBJS)

val:
	valgrind ./$(PROGRAM) $(FILE) $(BLOOMSIZE)