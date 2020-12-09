#include "sp1sLib.h"
int DEBUG = 0;

int main(int argc, char *argv[]) {
    int foundDatesByLooking = 0;
    searchParameters searchParametersMain;
    calendarSuite calendarSuiteMain;

    mallocCalendarSuite(ctrlAndDoArgs(argc, argv), &calendarSuiteMain);
    getCalendarSuite(argc, argv, &calendarSuiteMain);

    getSearchParameters(&searchParametersMain);
    foundDatesByLooking = findAvailableDatesByLooking(&calendarSuiteMain);

    if (!foundDatesByLooking) {
        findAvailableDatesByRestructuring();
    }
    userOutput();

    free(calendarSuiteMain.calPtrArray);
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
int ctrlAndDoArgs(int argc, char *argv[]) {
    int i = 1;
    int argsValid = argc >= 2;
    int icsFilesGot = 0;

    while (argsValid && i < argc) {
        argsValid = doArg(argv[i]);
        if (argsValid == icsFile) {
            icsFilesGot++;
        }
        i++;
    }

    if (DEBUG) {
        printf("argsValid = %d\nicsFilesGot = %d\n", argsValid, icsFilesGot);
    }

    if (!argsValid || icsFilesGot < 1) {
        exitWithError();
    }

    return icsFilesGot;
}

/**
 * @brief Allocates memory for an calendarSuite.calPtrArray of length n.
 * 
 * Terminates the program if it fails to allocate memory.
 * 
 * @param n length of array
 * @param calendarSuite output parameter, calendarSuite to be allocated memory
 */
void mallocCalendarSuite(int n, calendarSuite *calendarSuite) {
    int i = 0;

    calendarSuite->Arraylen = n;
    calendarSuite->calPtrArray = (calendar **)malloc((n) * sizeof(calendar *));
    errorHandling(calendarSuite->calPtrArray == NULL, "!!!FAILED TO ALLOCATE MEMORY STEP 1!!!");

    while (i < n) {
        calendarSuite->calPtrArray[i] = (calendar *)malloc(sizeof(calendar));
        calendarSuite->calPtrArray[i]->firstEvent = NULL;
        errorHandling(calendarSuite->calPtrArray[i] == NULL, "!!!FAILED TO ALLOCATE MEMORY STEP 2!!!");
        i++;
    }
}

/**
 * @brief 
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

/**
 * @brief !!!THIS FUNCTION IS NOT FINISHED!!!
 * 
 * @param argc 
 * @param argv 
 * @param calendarSuite 
 */
void getCalendarSuite(int argc, char *argv[], calendarSuite *calendarSuite) {
    int returnFlag = 0;

    returnFlag = getCalendarSuiteGetFile(argc, argv, calendarSuite->calPtrArray);
    errorHandling(!returnFlag, "!!!INVALID FILE LOCATION!!!");

    returnFlag = getCalendarSuiteGetData(calendarSuite);
    errorHandling(!returnFlag, "!!!ERROR IN *.ICS FILE!!!");

    if (DEBUG) {
        printf("\nICS FILE DATA GOT:\n\n");
        printCalendars(calendarSuite);
    }
}

/**
 * @brief 
 * 
 * @param suite A pointer to a calendarSuite for the program to find a date in.
 * @return int Bool value telling if a possible date for event was found.
 */
int findAvailableDatesByLooking(calendarSuite *suite) {
    int foundDate = 0;
    int sumAllEvents = 0;
    event **allEvents;

    sumAllEvents = findSumAllEvents(suite);
    printf("\nsumAllEvents: %d", sumAllEvents);

    allEvents = (event **)malloc(sumAllEvents * sizeof(event *));
    errorHandling(allEvents == NULL, "!!!FAILED TO ALLOCATE MEMORY STEP 3!!!");

    calSuiteToEventArray(suite, allEvents, sumAllEvents);
    /*sortEventArray();*/

    free(allEvents); /* <------ MIGHT BREAK EVERYTHING */
    return foundDate;
}

int findSumAllEvents(const calendarSuite *suite) {
    int i = 0, sum = 0;

    while (i < suite->Arraylen) {
        sum += suite->calPtrArray[i]->numOfEvents;
        i++;
    }

    return sum;
}

void calSuiteToEventArray(const calendarSuite *suite, event *eventPtrArray[], int sumAllEvents) {
    int i = 0, k;
    eventLink *cursor;

    printf("ArrayLen: %d\n", suite->Arraylen);
    for (k = 0; k < suite->Arraylen; k++) {
        cursor = suite->calPtrArray[k]->firstEvent;
        while(cursor != NULL) {
            eventPtrArray[i] = cursor->currentEvent;

            cursor = cursor->nextEventLink;
            printf("\n%s\n", eventPtrArray[i]->title);
            i++;
        }
    }
}

void findAvailableDatesByRestructuring(void) {
}

void userOutput(void) {
}
