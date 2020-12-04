#include "header.h"

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
    int validFileLocation = 0;

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

int getCalendarSuiteGetData(calendarSuite *calendarSuite) {
    int i = 0;
    int errorFlag = 1;

    while (i < calendarSuite->Arraylen && errorFlag) {
        errorFlag = getCalendarSuiteGetDataSingle(calendarSuite->calPtrArray[i]);
        i++;
    }

    return errorFlag;
}

int getCalendarSuiteGetDataSingle(calendar *calendar) {
    event *newEvent;
    int isEvent = 0, numOfEvents = 0;
    char line[LINE_LEN], leftOverGarbage[LINE_LEN], description[LINE_LEN];

    while (fgets(line, LINE_LEN, calendar->file)) {
        if (strstr(line, "BEGIN:VEVENT")) { /* Find linjer hvor et event starter */
            isEvent = 1;
            numOfEvents++;
            newEvent = (event *)malloc(sizeof(event));
        }

        if (isEvent) {
            sscanf(line, "SUMMARY: %s", newEvent->title);
            sscanf(line, "DTSTART:%4d%2d%2dT%2d%2d%2d%s",
                   &newEvent->startTime.tm_year,
                   &newEvent->startTime.tm_mon,
                   &newEvent->startTime.tm_mday,
                   &newEvent->startTime.tm_hour,
                   &newEvent->startTime.tm_min,
                   &newEvent->startTime.tm_sec,
                   leftOverGarbage);
            sscanf(line, "DESCRIPTION:%s", description);

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
            printf("\n\nSUMMARY: %s\n", newEvent->title);
            printf("DTSTART: %d/%d/%d Time: %d:%d:%d\n",
                   newEvent->startTime.tm_year,
                   newEvent->startTime.tm_mon,
                   newEvent->startTime.tm_mday,
                   newEvent->startTime.tm_hour,
                   newEvent->startTime.tm_min,
                   newEvent->startTime.tm_sec);
            printf("DTEND:   %d/%d/%d Time: %d:%d:%d\n",
                   newEvent->endTime.tm_year,
                   newEvent->endTime.tm_mon,
                   newEvent->endTime.tm_mday,
                   newEvent->endTime.tm_hour,
                   newEvent->endTime.tm_min,
                   newEvent->endTime.tm_sec);
            printf("Priority: %d\n", newEvent->priority);

            addEventCal(newEvent, calendar);
            isEvent = 0;
            free(newEvent);
        }
    }
    return 1;
}

/**
 * @brief 
 * 
 * @param newEvent The new event to be added at the end of the linked list
 * @param inputCal The calendar from which the event comes
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
 * @brief 
 * 
 * @param event 
 * @param pointer 
 * @return eventLink* 
 */
eventLink *mallocEventLink(event *event, eventLink *pointer) {
    eventLink *newLink;

    newLink = (eventLink *)malloc(sizeof(eventLink)); /* Memory leak */
    newLink->currentEvent = event;
    newLink->nextEventLink = (eventLink *)malloc(sizeof(eventLink));
    newLink->nextEventLink = pointer;

    return newLink;
}
