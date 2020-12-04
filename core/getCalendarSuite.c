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

            addEventCalAlt(newEvent, calendar);
            isEvent = 0;
            free(newEvent);
        }
    }
    return 1;
}

/* TODO: This shit doesn't work */
/*void addEventCal(event *newEvent, calendar *inputCal) {
    int eventNum = 0;
    eventLink *nextEvent, *newEventLink;*/

/* inputcal.firstevent = newEventLink */

/*newEventLink->currentEvent = newEvent;
    newEventLink->nextEventLink = NULL;

    while (nextEvent->nextEventLink != NULL) {
        nextEvent = nextEvent->nextEventLink;

        eventNum++;
        printf("Going to next event %d\n", eventNum);
    }*/

/*nextEvent->nextEventLink = newEventLink;


    Algorithm to insert node at the end of a Singly Linked List
    Begin:
        createSinglyLinkedList (head)
        alloc (newNode)
        If (newNode == NULL) then
            write ('Unable to allocate memory')
        End if
        Else then
            read (data)
            newNode.data ← data
            newNode.next ← NULL
            temp ← head
            While (temp.next != NULL) do
                temp ← temp.next
            End while
            temp.next ← newNode
        End else
    End
}*/

void addEventCalAlt(event *newEvent, calendar *inputCal) {
    eventLink *newLink;

    newLink = (eventLink *)malloc(sizeof(eventLink));
    newLink->currentEvent = newEvent;
    newLink->nextEventLink = (eventLink *)malloc(sizeof(eventLink));
    newLink->nextEventLink = NULL;

    if (inputCal->firstEvent == NULL) {
        inputCal->firstEvent = newLink;
    } else {
        newLink->nextEventLink = inputCal->firstEvent;

        while (newLink->nextEventLink != NULL) {
            printf("%d\n", newLink->nextEventLink);
            newLink = newLink->nextEventLink;
        }
    }

    /*eventLink *temp, *pos;

    pos = (eventLink *)malloc(sizeof(eventLink));

    temp = (eventLink *)malloc(sizeof(eventLink));
    temp->currentEvent = (event *)malloc(sizeof(event));
    temp->nextEventLink = (eventLink *)malloc(sizeof(eventLink));

    temp->currentEvent = newEvent;
    temp->nextEventLink = NULL;

    if (inputCal->firstEvent == NULL) {
        inputCal->firstEvent = temp;
        printf("Kalenderen er ikke længere tom, som mit liv <3\n");
    } else {
        pos = inputCal->firstEvent;

        while (pos != NULL) {
            pos = pos->nextEventLink;
        }

        pos->nextEventLink = (eventLink *)malloc(sizeof(eventLink));

        pos->nextEventLink = temp;*/

    /*
        temp = inputCal->firstEvent;
        printf("jeg kom her\n");

        
        
        
        while (temp->nextEventLink != NULL) {
            temp = temp->nextEventLink;
            printf("Going to next event\n");
        }
        */
}
