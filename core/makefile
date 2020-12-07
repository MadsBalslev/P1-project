CC=gcc
CFLAGS= -Wall -pedantic -g -ansi

DEPS = sp1sLib.h CuTest.h
OBJ = ctrlAndDoArgs.c CuTest.c allTests.c getSearchParameters.c helperFunctions.c getCalendarSuite.c #findAvailableDatesByLooking.c findAvailableDatesByRestructuring.c userOutput.c 

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

main: $(DEPS) $(OBJ) 
	$(CC) $@.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o *.out *.exe *.gch
	