CC=gcc
CFLAGS=-ansi -Wall -pedantic -g

DEPS = header.h CuTest.h
OBJ = ctrlAndDoArgs.c CuTest.c allTests.c getSearchParameters.c sharedFunctions.c getCalendarSuite.c #findAvailableDatesByLooking.c findAvailableDatesByRestructuring.c userOutput.c 

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

main: $(DEPS) $(OBJ) 
	$(CC) $@.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o *.out *.exe *.gch
	