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

    printf("ArrayLen: %d\n", suite->Arraylen);
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
    } else if (eventEndsLater(*event1, *event2)) {
        return 1;
    } else if (eventEndsLater(*event2, *event1)) {
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
int eventEndsLater(event *event1, event *event2) {
    if (event1->endTime.tm_year > event2->endTime.tm_year) { /* Check year */
        return 1;
    } else if (event1->endTime.tm_year < event2->endTime.tm_year) {
        return 0;
    } else if (event1->endTime.tm_mon > event2->endTime.tm_mon) { /* Check month */
        return 1;
    } else if (event1->endTime.tm_year < event2->endTime.tm_year) {
        return 0;
    } else if (event1->endTime.tm_mday > event2->endTime.tm_mday) { /* Check day */
        return 1;
    } else if (event1->endTime.tm_mday < event2->endTime.tm_mday) {
        return 0;
    } else if (event1->endTime.tm_hour > event2->endTime.tm_hour) { /* Check hour */
        return 1;
    } else if (event1->endTime.tm_hour < event2->endTime.tm_hour) {
        return 0;
    } else if (event1->endTime.tm_min > event2->endTime.tm_min) { /* Check min */
        return 1;
    } else if (event1->endTime.tm_min < event2->endTime.tm_min) {
        return 0;
    } else if (event1->endTime.tm_sec > event2->endTime.tm_sec) { /* Check secs */
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



/* 1. Sammenflet alle overlappende events til ét samlet event */

/* 2. Find ledig tid mellem sammenflettede events */

/* Hvis ikke det lykkedes at finde hultid uden i kalender med alle events:
   3. Fjern alle events med lavere prioritet end ønskede event */

/* 4. Sammenflet alle overlappende events til ét samlet event */

/* 5. Find ledig tid mellem sammenflettede events */

/* Output fund til bruger */