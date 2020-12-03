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
    char line[LINE_LEN], leftOverGarbage[LINE_LEN];

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
            sscanf(line, "DESCRIPTION:$P%d$%s", &newEvent->priority, leftOverGarbage);
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
            printf("SUMMARY: %s\n", newEvent->title);
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

void addEventCal(event *newEvent, calendar *inputCal) {
    int i = 0;
    eventLink *nextEvent = inputCal->firstEvent, *newEventLink;

    newEventLink->currentEvent = newEvent;
    newEventLink->nextEventLink = NULL;

    while (nextEvent != NULL) {
        i++;
        printf("Going to next event %d\n", i);
        nextEvent = nextEvent->nextEventLink;
    }

    nextEvent->nextEventLink = newEventLink;
}


/**
 * @brief Takes a char-pointer for the file path to the file, which will be parsed, 
 * and prints all calendar-events and the number of evetns
 * 
 * @param file_path 
 * @return int 
 */
int parse_file(char *file_path) {
    FILE *fp; /* Declare en pointer til en FILE */
    char input[LINE_LEN];
    int line = 0, isEvent, numOfEvents = 0;

    fp = fopen(file_path, "r"); /* Åbner den angivne fil i reading mode */
    if (fp == NULL)             /* Hvis filen ikke findes / eller ikke kan åbnes */
        return EXIT_FAILURE;

    while (fgets(input, LINE_LEN, fp)) {
        line++;

        if (strstr(input, "BEGIN:VEVENT")) { /* Find linjer hvor et event starter */
            isEvent = 1;
            numOfEvents++;
        }

        if (isEvent) {
            printf("%d: %s", line, input);
        }

        if (strstr(input, "END:VEVENT")) {
            isEvent = 0;
        }
    }

    printf("\n\n%d events in total\n\n", numOfEvents);

    fclose(fp); /* Luk filen igen */

    return EXIT_SUCCESS;
}
