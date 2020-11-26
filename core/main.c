#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "calendar.h"
#include "parser.h"

/* these should not be void xxx(void) functions */
void checkArgs(int);
void getSearchParameters(void);
void getCalenderSuite(void);
int findAvailableDatesByLooking(void);
void findAvailableDatesByRestructuring(void);
void userOutput(void);

int main(int argc, char *argv[]) {
    int foundDatesByLooking = 0;
    char *filepath;

    /* Få fil som commandline argument */
    checkArgs(argc);
    filepath = argv[2];

    getSearchParameters();
    getCalenderSuite();
    foundDatesByLooking = findAvailableDatesByLooking();

    if (foundDatesByLooking) {
        findAvailableDatesByRestructuring();
    }

    userOutput();

    /* This should be abstracted further */
    /* Path relative from parser.o location */
    /* int parse_success = parse_file(filepath);
    if (parse_success == EXIT_FAILURE) {
        printf("Failed to parse file %s", filepath);
        return EXIT_FAILURE;
    } */

    return EXIT_SUCCESS;
}

void checkArgs(int argc) {
    if (argc < 2) {
        printf("Please provide one or more .ics files\n");
        exit(EXIT_FAILURE);
    }
}

void getSearchParameters(void) {
}

void getCalenderSuite(void) {
}

int findAvailableDatesByLooking(void) {
    return 1;
}

void findAvailableDatesByRestructuring(void) {
}

void userOutput(void) {
}
