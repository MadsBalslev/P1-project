#include "header.h"

int DEBUG = 0;

int main(int argc, char *argv[]) {
    int foundDatesByLooking = 0;

    ctrlAndDoArgs(argc, argv);
    /*getSearchParameters();*/
    /*getCalendarSuite();*/
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

void ctrlAndDoArgs(int argc, char *argv[]) {
    int i = 1;
    int argsValid = (argc < 2 ? 0 : 1);
    int icsFilesGot = 0;

    while (argsValid && i < argc) {
        argsValid = doArg(argv[i]);
        argsValid == icsFile ? icsFilesGot++ : DO_NOTHING;
        i++;
    }

    if (DEBUG) {
        printf("argsValid = %d\nicsFilesGot = %d\n", argsValid, icsFilesGot);
    }

    if (!argsValid || icsFilesGot < 1) {
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
