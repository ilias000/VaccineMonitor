CC = g++
CFLAGS = -Wall -g
 
PROGRAM = vaccineMonitor
 
OBJS = VaccineMonitor.o

$(PROGRAM): clean $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJS)
 
VaccineMonitor.o: 
	$(CC) $(CFLAGS) -c VaccineMonitor.cpp

clean:
	rm -f $(PROGRAM) $(OBJS)


FILE = -c citizenRecordsFile 
BLOOMSIZE = -b 100000

run: $(PROGRAM)
	./$(PROGRAM) $(FILE) $(BLOOMSIZE)

