#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "calendar.h"
#include "parser.h"

/* these should not be void xxx(void) functions */
void getSearchParameters(void);
void getCalenderSuite(void);
int  findAvailableDatesByLooking(void);
void findAvailableDatesByRestructuring(void);
void userOutput(void);

int main(void) {
    int foundDatesByLooking = 0;

    getSearchParameters();
    getCalenderSuite();
    foundDatesByLooking = findAvailableDatesByLooking();

    if (foundDatesByLooking) {
        findAvailableDatesByRestructuring();
    }
    
    userOutput();

    /* This should be abstracted further */
    /* Path relative from parser.o location */
    /* int parse_success = parse_file("test.ics");
    if (parse_success == EXIT_FAILURE) {
        printf("Failed to parse file test.ics");
        return EXIT_FAILURE;
    } */

    return EXIT_SUCCESS;
}

void getSearchParameters(void) {

}

void getCalenderSuite(void) {

}

int  findAvailableDatesByLooking(void) {
    return 1;
}

void findAvailableDatesByRestructuring(void) {

}

void userOutput(void) {
    
}
