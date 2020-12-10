#include "sp1sLib.h"

/**
 * @brief Opens and stores file-pointer / file-path in calPtrArray.
 * 
 * Goes through argc number of arguments argv, if the argv is an *.ics file tries to open the
 * file. The file-path, and file-pointer is stored in calPtrArray, for each *.ics file.
 * 
 * @param argc number of arguments
 * @param argv arguments
 * @param calPtrArray output parameter
 * @return 1 if all file locations where valid, else 0 
 */
int getCalendarSuiteGetFile(int argc, char *argv[], calendar *calPtrArray[]) {
    int i = 1;
    int k = 0;
    int validFileLocation = 1;

    do {
        if (isIcsFile(argv[i])) {
            validFileLocation = getCalendarSuiteGetFileSingle(argv[i], calPtrArray[k]);
            k++;
        }
        i++;
    } while (i < argc && validFileLocation);

    return validFileLocation;
}

/**
 * @brief Tries to open arg as a file, stores the file-path and file-pointer in calendar.
 * 
 * @param arg file-path to an *.ics file
 * @param calendar Output parameter, where file-path and file-pointer should be stored
 * @return 1 if file-path was valid, else 0 
 */
int getCalendarSuiteGetFileSingle(char arg[], calendar *calendar) {
    int validFileLocation = 0;

    calendar->file = fopen(arg, "r");
    strcpy(calendar->fileName, arg);

    if (calendar->file == NULL) {
        validFileLocation = 0;
    } else {
        validFileLocation = 1;
    }
    return validFileLocation;
}

/**
 * @brief Builds a linked list of eventLinks, for each calendar pointed to by
 * calendarSuite.calPtrArray.
 *
 * This functions will also fclose the filepointer stored in each calendarSuite, when it has
 * read the data it needs.
 *
 * @param calendarSuite Suite of calendars from where the linked lists should be build.
 * @return Returns 1 if no error is found i files, else 0 (this is not implemented at the
 * moment). 
 */
int getCalendarSuiteGetData(calendarSuite *calendarSuite) {
    int i = 0, errorFlag = 1;

    while (i < calendarSuite->Arraylen && errorFlag) {
        errorFlag = getCalendarSuiteGetDataSingle(calendarSuite->calPtrArray[i]);
        fclose(calendarSuite->calPtrArray[i]->file);
        i++;
    }

    return errorFlag;
}

/**
 * @brief Builds a linked list from data pointed to by the FILE pointer file contained in
 * calendar, makes calendar.firstEvent point to the first link/nodes in this linked list of
 * eventLink.
 *
 * This functions scans through the file pointed to by the FILE pointer contained in calendar.
 * For each events the functions reads allocates space for this data in the heap, and points
 * to this data in the linked list that is created. The number of events in each calendar is
 * calculated and stored in calendar.numOfEvents.
 *
 * @param calendar Calendar from where the linked list should be build from.
 * @return 1.
 */
int getCalendarSuiteGetDataSingle(calendar *calendar) {
    event *newEvent;
    int isEvent = 0, numOfEvents = 0;
    char line[LINE_LEN], leftOverGarbage[LINE_LEN];

    while (fgets(line, LINE_LEN, calendar->file)) {
        if (strstr(line, "BEGIN:VEVENT")) { /* Find linjer hvor et event starter */
            isEvent = 1;
            numOfEvents++;
            newEvent = (event *)malloc(sizeof(event));
        }

        if (isEvent) {
            sscanf(line, "SUMMARY: %[^\n]", newEvent->title); /* Reads every character until -1 (EOF) */
            sscanf(line, "DTSTART:%4d%2d%2dT%2d%2d%2d%s",
                   &newEvent->startTime.tm_year,
                   &newEvent->startTime.tm_mon,
                   &newEvent->startTime.tm_mday,
                   &newEvent->startTime.tm_hour,
                   &newEvent->startTime.tm_min,
                   &newEvent->startTime.tm_sec,
                   leftOverGarbage);
            if (sscanf(line, "DESCRIPTION:%[0-9a-zA-Z ]", leftOverGarbage) && leftOverGarbage[0] != '$') {
                sscanf(line, "DESCRIPTION:$P%d$", &newEvent->priority);
            } else {
                sscanf(line, "DESCRIPTION:$P%d$", &newEvent->priority);
            }

            if (newEvent->priority < 0) {
                newEvent->priority = 0; 
            }

            sscanf(line, "DTEND:%4d%2d%2dT%2d%2d%2d%s",
                   &newEvent->endTime.tm_year,
                   &newEvent->endTime.tm_mon,
                   &newEvent->endTime.tm_mday,
                   &newEvent->endTime.tm_hour,
                   &newEvent->endTime.tm_min,
                   &newEvent->endTime.tm_sec,
                   leftOverGarbage);
        }

        if (strstr(line, "END:VEVENT")) {
            addEventCal(newEvent, calendar);
            isEvent = 0;
        }
    }
    calendar->numOfEvents = numOfEvents;
    return 1;
}

/**
 * @brief Adds an eventLink pointing to newEvent to the end of the linked list that is
 * inputCal.
 *
 * Allocates space for the new eventLink, then goes to the bottom of the linked list inputCal
 * and points the NULL pointer to the new eventLink.
 *
 * @param newEvent The new event to be added at the end of the linked list.
 * @param inputCal First element in the linked list where newEvent needs to be added.
 */
void addEventCal(event *newEvent, calendar *inputCal) {
    eventLink *cursor, *newLink;
    newLink = mallocEventLink(newEvent, NULL);

    if (inputCal->firstEvent == NULL) {
        inputCal->firstEvent = newLink;
    } else {
        cursor = inputCal->firstEvent;
        while (cursor->nextEventLink != NULL) {
            cursor = cursor->nextEventLink;
        }
        cursor->nextEventLink = newLink;
    }
}

/**
 * @brief Creates a new eventLink.
 *
 * Allocates space on the heap for a new evenLink, makes the eventLink point to event, and
 * pointer.
 *
 * @param event Event this link should point to.
 * @param pointer Next link this link should point to.
 * @return Pointer to the new eventLink that has been created.
 */
eventLink *mallocEventLink(event *event, eventLink *pointer) {
    eventLink *newLink;

    newLink = (eventLink *)malloc(sizeof(eventLink));
    newLink->currentEvent = event;
    /*newLink->nextEventLink = (eventLink *)malloc(sizeof(eventLink));*/ /* <----- this is unnecessary*/
    newLink->nextEventLink = pointer;

    return newLink;
}

/*                    ____________________
 *                   |                   |
 *                   |   -------------   |   
 *                   |   FUNCTION JAIL   |
 *                   |   -------------   | 
 *                   |___________________|
 *                      |             |
 *                   #####################
 *                   ##                 ##
 *                k  ##                 ##       k
 *             O  |  ## free(newEvent); ##    O  |
 *           ()Y==o  ##                 ##  ()Y==o
 *            /_\ |  ##                 ##   /_\ |
 *            _W_ |  #####################   _W_ |
 *                         LOOOOL
 * 
 */