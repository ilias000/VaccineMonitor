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

run: $(PROGRAM)
	./$(PROGRAM)

