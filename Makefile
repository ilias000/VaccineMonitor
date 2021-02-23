CC = g++
CFLAGS = -Wall -g
 
PROGRAM = vaccineMonitor
 
OBJS = VaccineMonitor.o

$(PROGRAM): clean $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)
 
clean:
	rm -f $(PROGRAM) $(OBJS)

run: $(PROGRAM)
	./$(PROGRAM)

