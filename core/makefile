CC=gcc
CFLAGS=-ansi -Wall -pedantic

DEPS = header.h
OBJ = ctrlArgs.o getSearchParameters.o getCalendarSuite.o findAvailableDatesByLooking.o findAvailableDatesByRestructuring.o userOutput.o sharedFunctions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) $@.c $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -rf *.o *.out *.exe 
	