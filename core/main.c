#include "sp1sLib.h"
int DEBUG = 0;

/**
 * @brief This is where the magic happens 🤖
 *
 * @param argc Amount of arguments provided as a command line input including the program
 * itself.
 * @param argv An array of all command line arguments including the program itself.
 * @return The exit code of the program.
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
 * @param argc Number of arguments.
 * @param argv Array of argument strings.
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
 * @param n length of array.
 * @param[out] calendarSuite CalendarSuite to be allocated memory.
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
 * @brief Prompts user for search parameters, stores values in a.
 * 
 * Gets all of the search parameters and stores them in the struct.
 * It also prints out the priority and length of the event.
 * 
 * @param[out] a Where search parameters should be stored.
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
 * @param argc Number of arguments.
 * @param argv Arguments.
 * @param[in, out] calendarSuite suite where the calendar data should be stored.
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
 * @brief As of now finds one time slot in suite, as defined by param and searchMode.
 *
 * 1. The sum of all events across the whole suite is found.
 * 2. Space is allocated for an array of pointers to events(allEvents), the lenght of this
 *    array is equal to the sum of all events across the whole suite.
 * 3. The allEvents array is then filled with pointers to all events in suite. If searchMode
 *    == byRestructuring, events with a higher priority than param->priority are ignored.
 * 4. The allEvents array is sorted by endTime in ascending order.
 * 5. The functions tries to find one avalible date, and prints the result of the search on
 *    screen.
 *
 * @param[in, out] suite A pointer to a calendarSuite for the program to find a date in.
 * @param param A struct of search paramerters
 * @param searchMode Used to check if priority of param is used, or using default value
 * @return int Bool value telling if a possible date for event was found.
 */
int findAvailableDates(calendarSuite *suite, const searchParameters *param, int searchMode) {
    int foundDate = 0, sumAllEvents = 0; 
    event **allEvents;
    tm freeSlot;

    /* -1- */
    sumAllEvents = findSumAllEvents(suite);
    if (DEBUG) {
        printf("\nsumAllEvents: %d", sumAllEvents);
    }

    /* -2- */
    allEvents = (event **)malloc(sumAllEvents * sizeof(event *));
    errorHandling(allEvents == NULL, "!!!FAILED TO ALLOCATE MEMORY STEP 3!!!");

    /* -3- */
    if (searchMode == bylooking) {
        calSuiteToEventArray(suite, sumAllEvents, MAX_PRIORITY, allEvents); /* <------ This should be account for elsewhere*/
    } else if (searchMode == byRestructuring) {
        calSuiteToEventArray(suite, sumAllEvents, param->priority, allEvents);
    }
    if (DEBUG) {
        printf("\nEVENT ARRAY:\n");
        printEventPtrArray(allEvents, sumAllEvents);
    }

    /* -4- */
    qsort(allEvents, sumAllEvents, sizeof(event *), startTimeCmp); /* Sorting array of events in chronological order by endTime */
    if (DEBUG) {
        printf("\nSORTED EVENT ARRAY:\n");
        printEventPtrArray(allEvents, sumAllEvents);
    }

    /* -5- */
    freeSlot = lookForFreeSlot(param, sumAllEvents, allEvents);
    if(freeSlot.tm_year >= 0) {
        printf("Free slot found at: %.2d/%.2d/%.4d %.2d:%.2d\n", 
                freeSlot.tm_mday, 
                freeSlot.tm_mon + 1, 
                freeSlot.tm_year + EPOCH,
                freeSlot.tm_hour,
                freeSlot.tm_min);
        foundDate = 1;
    } else {
        printf("Found no date :(\n");
    }

    free(allEvents); 
    return foundDate;
}