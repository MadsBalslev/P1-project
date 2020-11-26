CC=gcc
CFLAGS=-ansi -Wall -pedantic

DEPS = parser.h calendar.h
OBJ = parser.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) $@.c $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o *.out *.exe 
	