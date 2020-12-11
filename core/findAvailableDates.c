#include "sp1sLib.h"
extern int DEBUG;

/**
 * @brief Finds the sum of all events in a given calendarSuite.
 * 
 * The sum is found by adding up all the sums found in suite->calPtrArray[i]->numOfEvents.
 * 
 * @param suite calendarSuite where sum of all events should be found
 * @return sum of all events in calendarSuite
 */
int findSumAllEvents(const calendarSuite *suite) {
    int i = 0, sum = 0;

    while (i < suite->Arraylen) {
        sum += suite->calPtrArray[i]->numOfEvents;
        i++;
    }

    return sum;
}

/**
 * @brief Iterates through all events from all calendar-files and adds them all to one big array
 * 
 * The function loops through all calendars and adds all the events to one array. An event will only be added
 * to the array if it has priority over the event we are finding an avaliable slot for. 
 * 
 * @param suite the suite of calendars to look through
 * @param eventPtrArray The array to put all events into
 * @param sumAllEvents The amount of events across all calendar files
 * @param priority The priority of the event the user wants to find an avaliable time slot for. Defaults to 1000
 */
void calSuiteToEventArray(const calendarSuite *suite, event *eventPtrArray[], int sumAllEvents, int priority) {
    int i = 0, k;
    eventLink *cursor;

    for (k = 0; k < suite->Arraylen; k++) {
        cursor = suite->calPtrArray[k]->firstEvent;
        while (cursor != NULL) {
            if (cursor->currentEvent->priority <= priority) {
                eventPtrArray[i] = cursor->currentEvent;
            } else {
                eventPtrArray[i] = NULL;
            }

            cursor = cursor->nextEventLink;
            i++;
        }
    }
}

/**
 * @brief Compares two events to determine which event ends the latest.
 *
 * @param arg1 first event to be compared
 * @param arg2 second event to be compared
 * @return 1 if the first event ends before the second, -1 if the second event ends before the
 * first, 0 if both events end at the same time. 
 */
int endTimeCmp(const void *arg1, const void *arg2) {
    event **event1 = (event **)arg1;
    event **event2 = (event **)arg2;

    if (*event1 == NULL && *event2 != NULL) {
        return 1;
    } else if (*event1 != NULL && *event2 == NULL) {
        return -1;
    } else if (*event1 == NULL && *event2 == NULL) {
        return 0;
    } else if (eventStartsLater(*event1, *event2)) {
        return 1;
    } else if (eventStartsLater(*event2, *event1)) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * @brief Determines if event1 ends later than event2.
 * 
 * @param event1 pointer to event structure
 * @param event2 pointer to event structure
 * @return int 1 if event1 ends later than event 2, 0 if event 2 ends later than event1 or they end at the same time
 */
int eventStartsLater(event *event1, event *event2) {
    if (event1->startTime.tm_year > event2->startTime.tm_year) { /* Check year */
        return 1;
    } else if (event1->startTime.tm_year < event2->startTime.tm_year) {
        return 0;
    } else if (event1->startTime.tm_mon > event2->startTime.tm_mon) { /* Check month */
        return 1;
    } else if (event1->startTime.tm_year < event2->startTime.tm_year) {
        return 0;
    } else if (event1->startTime.tm_mday > event2->startTime.tm_mday) { /* Check day */
        return 1;
    } else if (event1->startTime.tm_mday < event2->startTime.tm_mday) {
        return 0;
    } else if (event1->startTime.tm_hour > event2->startTime.tm_hour) { /* Check hour */
        return 1;
    } else if (event1->startTime.tm_hour < event2->startTime.tm_hour) {
        return 0;
    } else if (event1->startTime.tm_min > event2->startTime.tm_min) { /* Check min */
        return 1;
    } else if (event1->startTime.tm_min < event2->startTime.tm_min) {
        return 0;
    } else if (event1->startTime.tm_sec > event2->startTime.tm_sec) { /* Check secs */
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Prints all event data in a given array of pointer to events of length n.
 * 
 * @param allEvents pointer to array of pointers to events
 * @param n length of array to be printed
 */
void printEventPtrArray(event *allEvents[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (allEvents[i] != NULL) {
            printEvent(allEvents[i]);
        }
    }
}

tm lookForFreeSlot(event *allEvents[], int arrLen, searchParameters *p) {
    tm dateFound;
    time_t head;
    int i = 0;

    dateFound.tm_year = -1;
    head = mktime(&p->lowerLimit) + mktime(&p->startDate);

    while (i < arrLen && allEvents[i] != NULL && dateFound.tm_year != -1) {
        dateFound = lookForFreeSlotSingle(allEvents[i], p, &head);
        i++;
    }

    return dateFound;
}

tm lookForFreeSlotSingle(event *event, searchParameters *p, time_t *head) {
    tm dateFound;
    dateFound.tm_year = -2;
    

    if (endOfLine(event, p, head)) {
        dateFound.tm_year = -1;
    } else if (canGo(event, p, head)) {
        go(event, p, head);
    } else if (canSwallow(event, p, head)) {
        swallow(event, p, head);
    } else if (stuck(event, p, head)) {
        dateFound = *localtime(head);
    }

    return dateFound;
}

int endOfLine(event *event, searchParameters *p, time_t *head) {
    time_t eolTime = mktime(&p->upperLimit) + mktime(&p->endDate);
    return *head >= eolTime;
}

int canGo(const event *event, const searchParameters *p, const time_t *head) {
    return 1;
}

int canSwallow(const event *event, const searchParameters *p, const time_t *head) {
    return 1;
}


int stuck(const event *event, const searchParameters *p, const time_t *head) {
    return 1;
}

void go(const event *event, const searchParameters *p, time_t *head) {
}

void swallow(const event *event, const searchParameters *p, time_t *head) {
    
}

/* 1. Sammenflet alle overlappende events til ét samlet event */

tm *lookForFreeSlotAlt(event *allEvents[], int arrLen, searchParameters *p) {
    tm cursor, *freeSlot = NULL, *tempSlot;
    time_t unixCursor;
    int i;

    cursor.tm_year = p->startDate.tm_year;
    cursor.tm_mon = p->startDate.tm_mon;
    cursor.tm_mday = p->startDate.tm_mday;
    cursor.tm_hour = p->lowerLimit.tm_hour;
    cursor.tm_min = p->lowerLimit.tm_min;

    unixCursor = mktime(&cursor);

    for (i = 0; i < arrLen || allEvents[i] != NULL; i++) {
        time_t unixStart = mktime(&allEvents[i]->startTime);
        time_t unixEnd = mktime(&allEvents[i]->endTime);

        if (unixCursor > unixStart && unixCursor < unixEnd) {
            unixCursor = unixEnd;
            printf("New cursor: %ld\n", unixCursor);
        } else if (unixCursor < unixStart && unixStart - unixCursor >= ((p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC))) {
            if (withinScope(unixCursor, p)) {
                break;
            }
        } else if (unixCursor < unixStart && unixStart - unixCursor < ((p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC))) {
            unixCursor = unixEnd;
        }

        tempSlot = localtime(&unixCursor);
        printf("cursor was: %.2d/%.2d/%.4d %.2d:%.2d\n", tempSlot->tm_mday, tempSlot->tm_mon + 1, tempSlot->tm_year + 1900, tempSlot->tm_hour, tempSlot->tm_min);
    }

    unixCursor = unixCursor + (p->buffer * MIN_TO_SEC);

    freeSlot = localtime(&unixCursor);

    return freeSlot;
}

int withinScope(time_t unixCursor, const searchParameters *p) {
    tm *cursorStart;
    tm *cursorEnd;

    cursorStart = localtime(&unixCursor);
    cursorEnd = localtime(&unixCursor + (p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC));

    if ((cursorStart->tm_hour >= p->lowerLimit.tm_hour) && (cursorEnd->tm_hour <= p->upperLimit.tm_hour)) {
        return 1;
    } else {
        return 0;
    }
}

/*tm convertUnixTime(time_t inputUnix) {
    tm convertedTime;

    convertedTime = *localtime(inputUnix);

    return convertedTime;
}*/

/**
 * @brief Checks if an event begins before the event of previous event
 * 
 * @param event1 
 * @param event2 
 * @return int 
 */
/*int eventBeginBeforeEnd(time_t *event1, time_t *event2) {
    if (event2 <= event1) {
        return 1;
    } else {
        return 0;
    }
}*/

/*int tmCmp(tm t1, tm t2) {
    if (t1.tm_year > t2.tm_year) { 
        return 1;
    } else if (t1.tm_year < t2.tm_year) {
        return 0;
    } else if (t1.tm_mon > t2.tm_mon) { 
        return 1;
    } else if (t1.tm_year < t2.tm_year) {
        return 0;
    } else if (t1.tm_mday > t2.tm_mday) { 
        return 1;
    } else if (t1.tm_mday < t2.tm_mday) {
        return 0;
    } else if (t1.tm_hour > t2.tm_hour) { 
        return 1;
    } else if (t1.tm_hour < t2.tm_hour) {
        return 0;
    } else if (t1.tm_min > t2.tm_min) { 
        return 1;
    } else if (t1.tm_min < t2.tm_min) {
        return 0;
    } else if (t1.tm_sec > t2.tm_sec) { 
        return 1;
    } else {
        return 1;
    }
}*/

/* 2. Find ledig tid mellem sammenflettede events */

/* Hvis ikke det lykkedes at finde hultid uden i kalender med alle events:
   3. Fjern alle events med lavere prioritet end ønskede event */

/* 4. Sammenflet alle overlappende events til ét samlet event */

/* 5. Find ledig tid mellem sammenflettede events */

/* Output fund til bruger */
