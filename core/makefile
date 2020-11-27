CC=gcc
CFLAGS=-ansi -Wall -pedantic

DEPS = header.h CuTest.h
OBJ = ctrlAndDoArgs.c CuTest.c #allTests.c getSearchParameters.c getCalendarSuite.c findAvailableDatesByLooking.c findAvailableDatesByRestructuring.c userOutput.c sharedFunctions.c

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

main: $(DEPS) $(OBJ) 
	$(CC) $@.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o *.out *.exe *.gch
	