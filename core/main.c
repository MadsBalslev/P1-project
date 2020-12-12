#include "sp1sLib.h"
int DEBUG = 0;

/**
 * @brief This is where the magic happens 🤖
 * 
 * @param argc Amount of arguments provided as a command line input including the program itself
 * @param argv An array of all command line arguments including the program itself 
 * @return int The exit code of the program
 */
int main(int argc, char *argv[]) {
    int foundDatesByLooking = 0;
    searchParameters searchParametersMain;
    calendarSuite calendarSuiteMain;

    mallocCalendarSuite(ctrlAndDoArgs(argc, argv), &calendarSuiteMain);
    getCalendarSuite(argc, argv, &calendarSuiteMain);

    getSearchParameters(&searchParametersMain);

    foundDatesByLooking = findAvailableDates(&calendarSuiteMain, &searchParametersMain, bylooking);

    if (!foundDatesByLooking) {
        findAvailableDates(&calendarSuiteMain, &searchParametersMain, byRestructuring);
    }

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
    a->buffer  = getEventBuffer();
    getDates(&a->startDate, &a->endDate);
    getLimits(&a->lowerLimit, &a->upperLimit);

    if (DEBUG) {
        printf("Priority: %d\nEventLen: %d", a->priority, a->eventLen);
    }
}

/**
 * @brief Based on a number of filepaths to *.ics files, builds an array of pointers to linked
 * lists of calendar links/nodes and links/nodes data.
 *
 * Each linked list correspondes to each *.ics file gotten. Each linked list starts with a
 * node/link struct called calendar, this struct is documented in sp1sLib.h. After this the
 * linked list is made of node/link structs called eventLink, these contain data for one event
 * each, they are also documented in sp1sLib.h. 
 *
 * The function looks through argc amount of arguments, argv, not all argumets need to be
 * *.ics file paths, but all *.ics filepaths have to be valid, if this is not the case
 * function terminates program with an error message.
 *
 * @param argc number of arguments
 * @param argv arguments
 * @param[in, out] calendarSuite
 *
 * @warning This function does not control the validity of the data gotten from the *.ics
 * files. [errorHandling(!returnFlag, "!!!ERROR IN *.ICS FILE!!!");] does nothing at the
 * moment.
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
 * @param param A struct of search paramerters
 * @param searchMode Used to check if priority of param is used, or using default value
 * @return int Bool value telling if a possible date for event was found.
 */
int findAvailableDates(calendarSuite *suite, searchParameters *param, int searchMode) {
    int foundDate = 0, sumAllEvents = 0; 
    event **allEvents;
    tm freeSlot;

    sumAllEvents = findSumAllEvents(suite);
    if (DEBUG) {
        printf("\nsumAllEvents: %d", sumAllEvents);
    }

    allEvents = (event **)malloc(sumAllEvents * sizeof(event *));
    errorHandling(allEvents == NULL, "!!!FAILED TO ALLOCATE MEMORY STEP 3!!!");

    if (searchMode == bylooking) {
        calSuiteToEventArray(suite, allEvents, sumAllEvents, MAX_PRIORITY); /* <------ This should be account for elsewhere*/
    } else if (searchMode == byRestructuring) {
        calSuiteToEventArray(suite, allEvents, sumAllEvents, param->priority);
    }

    if (DEBUG) {
        printf("\nEVENT ARRAY:\n");
        printEventPtrArray(allEvents, sumAllEvents);
    }

    qsort(allEvents, sumAllEvents, sizeof(event *), endTimeCmp); /* Sorting array of events in chronological order by endTime */

    if (DEBUG) {
        printf("\nSORTED EVENT ARRAY:\n");
        printEventPtrArray(allEvents, sumAllEvents);
    }

    /* Find huller i events */
    freeSlot = lookForFreeSlot(allEvents, sumAllEvents, param);

    if(freeSlot.tm_year != -1) {
        printf("Free slot found at: %.2d/%.2d/%.4d %.2d:%.2d\n", 
                freeSlot.tm_mday, 
                freeSlot.tm_mon + 1, 
                freeSlot.tm_year + 1900,
                freeSlot.tm_hour,
                freeSlot.tm_min);
        foundDate = 1;
    } else {
        printf("Found no date :(\n");
    }


    free(allEvents); /* <------ MIGHT BREAK EVERYTHING */

    return foundDate;
}

void userOutput(void) {
}
