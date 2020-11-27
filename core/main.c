#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

int main(int argc, char *argv[]) {
    int foundDatesByLooking = 0;

    ctrlArgs(argc, argv);
    getSearchParameters();
    getCalendarSuite();
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

/**
 * @brief TEST TEST TEST!! Controls whether command-line arguments where valid.
 *  
 * Controls that the number of arguments (argc) gotten was over 1 and that the arguments where
 * in the format of *.ics. If this is not the case an error message is printed and the program
 * terminates. 
 *
 * @param argc number of arguments
 * @param argv arguments
 */
void ctrlArgs(int argc, char *argv[]) {
    ctrlArgsAmount(argc);
    ctrlArgsIsFile(argc, argv);
}

void getSearchParameters(void) {
}

void getCalendarSuite(void) {
}

int findAvailableDatesByLooking(void) {
    return 1;
}

void findAvailableDatesByRestructuring(void) {
}

void userOutput(void) {
}
