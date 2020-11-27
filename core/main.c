#include "header.h"

int DEBUG = 0;

int main(int argc, char *argv[]) {
    int foundDatesByLooking = 0;

   
    getArgs(argc, argv);
    /*getSearchParameters();*/
    /*getCalendarSuite();*/
    foundDatesByLooking = findAvailableDatesByLooking();

    printf("%d", DEBUG);

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

void getArgs(int argc, char *argv[]) {
    int i = 1;
    int argsValid = (argc < 2 ? 0 : 1);

    while (argsValid) {
        argsValid = doArg(argv[i]);
        i++;
    } 

    if (!argsValid) {
        exitWithError();
    }
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
