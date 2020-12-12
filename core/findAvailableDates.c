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
 * @brief Iterates through all events from all calendar-files and adds them all to one big
 * array
 *
 * The function loops through all calendars and adds all the events to one array. An event
 * will only be added to the array if it has priority over the event we are finding an
 * avaliable slot for. 
 *
 * @param suite the suite of calendars to look through
 * @param eventPtrArray The array to put all events into
 * @param sumAllEvents The amount of events across all calendar files
 * @param priority The priority of the event the user wants to find an avaliable time slot
 * for. Defaults to 1000
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
 * @return int 1 if event1 ends later than event 2, 0 if event 2 ends later than event1 or
 * they end at the same time
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
    time_t head = getStartOfLine(p);
    tm dateFound;
    int i = 0;

    dateFound.tm_year = look;

    while (i < arrLen && allEvents[i] != NULL && dateFound.tm_year < 0 && dateFound.tm_year != eol) {
        if (DEBUG) printf("Event: %s\n", allEvents[i]->title);

        dateFound = lookForFreeSlotSingle(allEvents[i], p, &head);

        if (DEBUG) {
            printf("head: ");
            print_time_t(head);
            printf("\n");
        }

        if (dateFound.tm_year != redo) {
            i++;
        }
    }

    return dateFound;
}

tm lookForFreeSlotSingle(event *event, searchParameters *p, time_t *head) {
    time_t eventStartTimeUnix = mktime(&event->startTime);
    time_t eventEndTimeUnix = mktime(&event->endTime);
    tm dateFound;
    dateFound.tm_year = look;

    if (endOfLine(p, *head)) {
        if (DEBUG) printf("endOfLine\n");
        dateFound.tm_year = eol;
    } else if (canElongate(eventStartTimeUnix, eventEndTimeUnix, *head, p)) {
        if (DEBUG) printf("elongate\n");
        *head = eventEndTimeUnix;
    } else if (canSwallow(eventStartTimeUnix, eventEndTimeUnix, *head)) {
        if (DEBUG) printf("swallow\n");
    } else if (stuck(eventStartTimeUnix, eventEndTimeUnix, *head, p)) {
        dateFound = stuckProcedure(eventStartTimeUnix, eventEndTimeUnix, p, head);
    }

    return dateFound;
}

int endOfLine(searchParameters *p, time_t head) {
    time_t eolTime = getEndOfLine(p);
    return head >= eolTime;
}

int canElongate(time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head, const searchParameters *p) {
    return ((head < eventEndTimeUnix) && (head >= eventStartTimeUnix)) ||
           ((head < eventStartTimeUnix) && ((eventStartTimeUnix - head) < ((p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC))));
}

int canSwallow(time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head) {
    return (head > eventEndTimeUnix) && (head > eventStartTimeUnix);
}

int stuck(time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head, const searchParameters *p) {
    return ((head < eventStartTimeUnix) && ((eventStartTimeUnix - head) >= ((p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC))));
}

tm stuckProcedure(time_t eventStartTimeUnix, time_t eventEndTimeUnix, searchParameters *p, time_t *head) {
    tm dateFound;

    if (headWithinLimits(p, *head)) {
        if (DEBUG) printf("stuck but found date\n");
        *head += p->buffer * MIN_TO_SEC;
        dateFound = *localtime(head);
    } else {
        if (DEBUG) printf("stuck but got on\n");
        setHeadToNextLL(p, head);
        dateFound.tm_year = redo;
    }

    return dateFound;
}

int headWithinLimits(searchParameters *p, time_t head) {
    int returnFlag = 0;
    tm tm_headStart;
    tm tm_headEnd;
    time_t headEnd;

    headEnd = head + (p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC);

    tm_headStart = *localtime(&head);
    tm_headEnd = *localtime(&headEnd);

    returnFlag += tmWithinLimits(p, &tm_headStart);
    returnFlag += tmWithinLimits(p, &tm_headEnd);

    if (returnFlag == 2) {
        returnFlag = 1;
    } else {
        returnFlag = 0;
    }

    return returnFlag;
}

int tmWithinLimits(searchParameters *p, tm *time) {
    if (time->tm_hour > p->lowerLimit.tm_hour && time->tm_hour < p->upperLimit.tm_hour) {
        return 1;
    } else if ((time->tm_hour == p->lowerLimit.tm_hour && time->tm_min >= p->lowerLimit.tm_min) &&
               (time->tm_hour == p->upperLimit.tm_hour && time->tm_min <= p->upperLimit.tm_min)) {
        return 1;
    } else {
        return 0;
    }
}

/* THIS FUNCTIONS IS VERY BROKEN ATM */
void setHeadToNextLL(searchParameters *p, time_t *head) {
    tm head_tm = *localtime(head);

    head_tm.tm_mday += 1;
    head_tm.tm_min = p->lowerLimit.tm_min;
    head_tm.tm_hour = p->lowerLimit.tm_hour;

    *head = mktime(&head_tm);
}

time_t getStartOfLine(const searchParameters *p) {
    tm time_tm = INIT_TM;
    time_t time;

    time_tm.tm_min = p->lowerLimit.tm_min;
    time_tm.tm_hour = p->lowerLimit.tm_hour;
    time_tm.tm_mday = p->startDate.tm_mday;
    time_tm.tm_mon = p->startDate.tm_mon;
    time_tm.tm_year = p->startDate.tm_year;

    time = mktime(&time_tm);

    return time;
}

time_t getEndOfLine(const searchParameters *p) {
    tm time_tm = INIT_TM;
    time_t time;

    time_tm.tm_min = p->upperLimit.tm_min;
    time_tm.tm_hour = p->upperLimit.tm_hour;
    time_tm.tm_mday = p->endDate.tm_mday;
    time_tm.tm_mon = p->endDate.tm_mon;
    time_tm.tm_year = p->endDate.tm_year;

    time = mktime(&time_tm);

    return time;
}

void print_time_t(time_t time) {
    tm *time_tm = localtime(&time);

    printf("%.2d/%.2d/%.2d - %.2d:%.2d\n",
           time_tm->tm_mday,
           time_tm->tm_mon + 1,
           time_tm->tm_year + EPOCH,
           time_tm->tm_hour,
           time_tm->tm_min);
}
