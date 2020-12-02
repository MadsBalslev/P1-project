#include "header.h"
int DEBUG = 0;

int main(int argc, char *argv[]) {
    int foundDatesByLooking = 0;
    searchParameters searchParametersMain;
    calendar **calendarSuite = (calendar **)malloc((argc - 1) * sizeof(calendar *));


    ctrlAndDoArgs(argc, argv);
    getSearchParameters(&searchParametersMain);
    getCalendarSuite(argc, argv, calendarSuite);
    
    /*printMetadataCalendarSuite(calendarSuite, 3);*/
    
    foundDatesByLooking = findAvailableDatesByLooking();

    if (foundDatesByLooking) {
        findAvailableDatesByRestructuring();
    }

    userOutput();
    free(calendarSuite);
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
 * @brief Controls and executes command-line arguments (only executes command-line options).
 * If all arguments are not valid, terminates program with an error message.
 *
 * All arguments are considered valid if they are either an *.ics file location or an option,
 * and when there are more than two arguments.
 *
 * @param argc number of arguments
 * @param argv array of argument strings
 */
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

/**
 * @brief Get the Search Parameters object
 * 
 * @param a 
 */
void getSearchParameters(searchParameters *a) {
    a->priority = getPriority();
    a->eventLen = getEventLen();
    getDates(&a->startDate, &a->endDate);
    getLimits(&a->lowerLimit, &a->upperLimit);

    if (DEBUG) {
        printf("Priority: %d\nEventLen: %d", a->priority, a->eventLen);
    }
}

int getCalendarSuite(int argc, char *argv[], calendar *calendarSuite[]) {
    int returnFlag = 0;

    returnFlag = getCalendarSuiteGetLocation(argc, argv, calendarSuite);
    errorHandling(!returnFlag, "!!!INVALID FILE LOCATION!!!");

    returnFlag = getCalendarSuiteGetEvents(calendarSuite);
    errorHandling(!returnFlag, "!!!ERROR IN *.ICS FILE!!!");

    /*(returnFlag == 2) ? (returnFlag = 1) : (returnFlag = 0);*/

    return returnFlag;
}

int findAvailableDatesByLooking(void) {
    return 1;
}

void findAvailableDatesByRestructuring(void) {
}

void userOutput(void) {
}
