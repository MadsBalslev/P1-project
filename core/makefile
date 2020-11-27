CC=gcc
CFLAGS=-ansi -Wall -pedantic

DEPS = header.h
OBJ = ctrlArgs.c #getSearchParameters.c getCalendarSuite.c findAvailableDatesByLooking.c findAvailableDatesByRestructuring.c userOutput.c sharedFunctions.c

#%.o: %.c $(DEPS)
	#$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) $(DEPS)
	$(CC) $@.c $^ $(CFLAGS)

allTests: $(DEPS) $(OBJ) CuTest.h CuTest.c
	$(CC) $@.c $^ $(CFLAGS) -o $@

.PHONY: clean

clean:
	rm -rf *.o *.out *.exe 
	