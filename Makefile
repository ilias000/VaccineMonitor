FILE = -c citizenRecordsFile 
BLOOMSIZE = -b 100000

CC = g++
CFLAGS = -Wall -g
 
PROGRAM = vaccineMonitorExe
 
OBJS = VaccineMonitor.o Functions.o

$(PROGRAM): clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM) 

VaccineMonitor.o: VaccineMonitor.cpp Functions.h
	$(CC) $(CFLAGS) -c VaccineMonitor.cpp -o VaccineMonitor.o

Functions.o: Functions.cpp Functions.h
	$(CC) $(CFLAGS) -c Functions.cpp -o Functions.o
 
clean:
	rm -f $(PROGRAM) $(OBJS)

run: $(PROGRAM)
	./$(PROGRAM) $(FILE) $(BLOOMSIZE)

