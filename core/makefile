CC=gcc
CFLAGS=-ansi -Wall -pedantic

DEPS = header.h CuTest.h
OBJ = ctrlArgs.c CuTest.c allTests.c #getSearchParameters.o getCalendarSuite.o findAvailableDatesByLooking.o findAvailableDatesByRestructuring.o userOutput.o sharedFunctions.o

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

main: $(DEPS) $(OBJ) 
	$(CC) $@.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o *.out *.exe *.gch
	