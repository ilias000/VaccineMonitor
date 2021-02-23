CC = g++
CFLAGS = -Wall -g
 
PROGRAM = vaccineMonitor
 
OBJS = VaccineMonitor.o

$(PROGRAM): clean $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)
 
vaccineMonitor.o: vaccineMonitor.cpp Point.h Square.h
    $(CC) $(CFLAGS) -c main.cpp
 
Point.o: Point.h
 
Square.o: Square.h Point.h

clean:
	rm -f $(PROGRAM) $(OBJS)

run: $(PROGRAM)
	./$(PROGRAM)

