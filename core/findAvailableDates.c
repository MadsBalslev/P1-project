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
void calSuiteToEventArray(const calendarSuite *suite, int sumAllEvents, int priority, event *eventPtrArray[]) {
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
 * @brief Compares two events to determine which event start the earliest.
 *
 * @param arg1 first event to be compared
 * @param arg2 second event to be compared
 * @return 1 if the first event ends before the second, -1 if the second event ends before the
 * first, 0 if both events end at the same time. 
 */
int startTimeCmp(const void *arg1, const void *arg2) {
    event **event1 = (event **)arg1;
    event **event2 = (event **)arg2;

    if (*event1 == NULL && *event2 != NULL) {
        return 1;
    } else if (*event1 != NULL && *event2 == NULL) {
        return -1;
    } else if (*event1 == NULL && *event2 == NULL) {
        return 0;
    } else if (eventStartsEarlier(*event1, *event2)) {
        return 1;
    } else if (eventStartsEarlier(*event2, *event1)) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * @brief Determines if event1 starts earlier than event2.
 *
 * @param event1 pointer to event structure
 * @param event2 pointer to event structure
 * @return int 1 if event1 ends later than event 2, 0 if event 2 ends later than event1 or
 * they end at the same time
 */
int eventStartsEarlier(const event *event1, const event *event2) {
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

/**
 * @brief Looks for a free time slot, defined by p, in a sorted array of pointers to events.
 *
 * Iterating over allEvents, this functions looks a timeslot of lenght  eventLen + buffer * 2
 * (in minutes). The function will keep looking until:
 * - End of list is reached           (i < arrLen && allEvents[i] != NULL) and
 * - A date is found                  (dateFound.tm_year < 0)
 * - head has not gone over endOfLine (dateFound.tm_year != eol)
 *
 * @param p Search parameters, controls what timeslot loofForFreeSlot should look for, and
 * where it should look.
 * @param arrLen length of array allEvents
 * @param allEvents sorted array of pointers
 * @return If a date is found that date is returned as a tm structure. Else returns a date
 * where .tm_year < 0.
 * @pre enum lookForFreeSlotStatus { eol = -1, endOfLine  look = -2, redo = -3 }; should be in
 * header. allEvents should be sorted in acending order by starting date.
 */
tm lookForFreeSlot(const searchParameters *p, int arrLen, event *allEvents[]) {
    time_t head = getStartOfLine(p);
    tm dateFound;
    int i = 0;

    dateFound.tm_year = look;

    while (i < arrLen && allEvents[i] != NULL && dateFound.tm_year < 0 && dateFound.tm_year != eol) {
        if (DEBUG) printf("Event: %s\n", allEvents[i]->title);

        dateFound = lookForFreeSlotSingle(p, allEvents[i], &head);

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

/**
  * @brief Looks for a free time slot between head and event->startTime.
  *
  * - If head is at endOfLine: .tm_year in the return struct tm is set to eol. This causes
  *   lookForFreeSlot() to stop looking for an event.
  * - Else if head is able to elongate, head elongates meaning head is set to event->endTime
  *   (in unix time). lookForFreeSlot() should then iterates to next event.
  * - Else if head is able to swallow, head swallows meaning head is unchanged.
  *   lookForFreeSlot() should then iterates to next event.
  * - Else if head is stuck, stuck mening it found a time slot of lenght greater than eventLen
  *   + buffer * 2, lookForFreeSlot() either does not iterate if date was not within limits as
  *   defined by p, or causes lookForFreeSlot() to stop looking as a date was found.
  *
  * @param p Search parameters.
  * @param event Pointer to event to compare.
  * @param[in, out] head Current head to compare and change.
  * @return If a date is found that date is returned as a tm structure. Else returns a date
  * where .tm_year < 0.  
  * @pre enum lookForFreeSlotStatus { eol = -1, endOfLine  look = -2, redo = -3 }; should be
 * in header.
  */
tm lookForFreeSlotSingle(const searchParameters *p, event *event, time_t *head) {
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
    } else if (stuck(eventStartTimeUnix, *head, p)) {
        dateFound = stuckProcedure(p, head);
    }

    return dateFound;
}

/**
 * @brief Controls that head has not gone over the final time, called endOfLine, where an
 * event could be found as defined by p.
 *
 * endOfLine is given by getEndOfLine().
 *
 * @param p Search parameters, where endOfLine can be found.
 * @param head time_t to control.
 * @return 1 if head is a or over endOfLine. 
 */
int endOfLine(const searchParameters *p, time_t head) {
    time_t eolTime = getEndOfLine(p);
    return head >= eolTime;
}

/**
 * @brief Controls if head is considered able to elongate over event.
 *
 * Head is considered able to elongate if:
 * - head is smaller than eventEndTimeUnix and head is larger than or equal to
 *   eventStartTimeUnix
 * - head is smaller than eventStartTimeUnix, and the time between head and eventStartTimeUnix
 *   is smaller than: eventLen + buffer * 2 (unix time) 
 *
 * @param eventStartTimeUnix Start of event in unix time.
 * @param eventEndTimeUnix End of event in unix time. 
 * @param head Head to control.
 * @param p Search parameters, where eventLen and buffer are contained.
 * @return 1 if it is able to elongate, else 0.
 * @pre MIN_TO_SEC should be #defined as 60.
 */
int canElongate(time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head, const searchParameters *p) {
    return ((head < eventEndTimeUnix) && (head >= eventStartTimeUnix)) ||
           ((head < eventStartTimeUnix) && ((eventStartTimeUnix - head) < ((p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC))));
}

/**
 * @brief Controls if head is considered able to swallow event.
 *
 * Head is considered able to swallow event if: head is larger than both eventStartTimeUnix
 * and eventEndTimeUnix.
 *
 * @param eventStartTimeUnix Start of event in unix time.
 * @param eventEndTimeUnix End of event in unix time. 
 * @param head Head to control.
 * @return 1 if head is able to swallow, else 0.  
 */
int canSwallow(time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head) {
    return (head > eventEndTimeUnix) && (head > eventStartTimeUnix);
}

/**
 * @brief Controls if head is considered stuck.
 *
 * Head is considered stuck if head is less than evenStartTimeUnix and the time between head
 * and eventStartTimeUnix is greater or equal to: eventLen + buffer * 2 (unix time).
 *
 * @param eventStartTimeUnix Start time(unix) for an event.
 * @param head Head to control.
 * @param p Search parameters, where eventLen and buffer are contained.
 * @return 1 if head is stuck, else 0.
 * @pre MIN_TO_SEC should be #defined as 60. 
 */
int stuck(time_t eventStartTimeUnix, time_t head, const searchParameters *p) {
    return ((head < eventStartTimeUnix) && ((eventStartTimeUnix - head) >= ((p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC))));
}

/**
 * @brief Runs the procedure corresponding to when head is considered stuck.
 *
 * Checks if an event, as defined by p, starting at head is within limits, if this is the case
 * the date is returned. Else head is set to the next lowerLimit, and returns tm date where
 * .tm_year = redo.
 *
 * @param p Search parameters.
 * @param[in, out] head time_t to do the procedure on.
 * @return A valid tm time if a date is found within limits defined in p. Else if the date
 * found is invalid i.e. not within the limits defined in p, returns tm date where .tm_year =
 * redo.
 * @pre MIN_TO_SEC should be #defined as 60. enum redo should be equal to -3.
 */
tm stuckProcedure(const searchParameters *p, time_t *head) {
    tm dateFound;

    if (headWithinLimits(p, *head)) {
        if (DEBUG) printf("found date\n");
        *head += p->buffer * MIN_TO_SEC;
        dateFound = *localtime(head);
    } else {
        if (DEBUG) printf("going to next lowerLimit\n");
        setHeadToNextLL(p, head);
        dateFound.tm_year = redo;
    }

    return dateFound;
}

/**
 * @brief Controls that an event that starts at head, and is defined by p is within limits.
 * 
 * @param p Search paramters, where limits are defined, and where event is defined.
 * @param head Start time of event.
 * @return 1 if it is within limits, else 0.
 * @pre MIN_TO_SEC should be #defined as 60. 
 */
int headWithinLimits(const searchParameters *p, time_t head) {
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

/**
 * @brief Controls that time is within lowerLimit and upperLimit defined in p.
 * 
 * @param p Search paramters, where lowerLimit and upperLimit is defined.
 * @param time tm struct to control.
 * @return 1 if within the limits, else 0.
 */
int tmWithinLimits(const searchParameters *p, const tm *time) {
    if (time->tm_hour > p->lowerLimit.tm_hour && time->tm_hour < p->upperLimit.tm_hour) {
        return 1;
    } else if ((time->tm_hour == p->lowerLimit.tm_hour && time->tm_min >= p->lowerLimit.tm_min) ||
               (time->tm_hour == p->upperLimit.tm_hour && time->tm_min <= p->upperLimit.tm_min)) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Sets head to be the next lowerLimit
 * 
 * @param p Search paramters, where lowerLimit is defined.
 * @param[in, out] head Head to set.
 */
void setHeadToNextLL(const searchParameters *p, time_t *head) {
    tm head_tm = *localtime(head);

    if (underLowerLimit(p, &head_tm)) {
        goToLowerLimitThisDay(p, &head_tm);
    } else {
        goToLowerLimitNextDay(*head, p, &head_tm);
    }

    *head = mktime(&head_tm);
}

/**
 * @brief Controls if head_tm is over upperLimit.
 * 
 * @param p Search paramters, where upperLimit is defined.
 * @param head_tm tm structure to control
 * @return 1 if it is, else 0 
 */
int overUpperLimit(const searchParameters *p, const tm *head_tm) {
    if (head_tm->tm_hour > p->upperLimit.tm_hour) {
        return 1;
    } else if (head_tm->tm_hour == p->upperLimit.tm_hour && head_tm->tm_min > p->upperLimit.tm_min) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Controls if head_tm is under lowerLimit.
 * 
 * @param p Search paramters, where lowerLimit is defined.
 * @param head_tm tm structure to control
 * @return 1 if it is, else 0 
 */
int underLowerLimit(const searchParameters *p, const tm *head_tm) {
    if (head_tm->tm_hour < p->lowerLimit.tm_hour) {
        return 1;
    } else if (head_tm->tm_hour == p->lowerLimit.tm_hour && head_tm->tm_min < p->lowerLimit.tm_min) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Sets head_tm to lowerLimit the next day.
 * 
 * @param head head_tm in unix time
 * @param p Search paramters, where lowerLimit is defined.
 * @param[in, out] head_tm tm structure to change.
 * @pre UNIX_24H should be #defined as 60 * 60 * 24 or 86400.
 */
void goToLowerLimitNextDay(time_t head, const searchParameters *p, tm *head_tm) {
    head += UNIX_24H;
    *head_tm = *localtime(&head);
    goToLowerLimitThisDay(p, head_tm);
}

/**
 * @brief Sets head_tm to lowerLimit same day.
 * 
 * @param p Search paramters, where lowerLimit is defined.
 * @param head_tm tm structure to change.
 */
void goToLowerLimitThisDay(const searchParameters *p, tm *head_tm) {
    head_tm->tm_min = p->lowerLimit.tm_min;
    head_tm->tm_hour = p->lowerLimit.tm_hour;
}

/**
 * @brief Finds the earliest time an event can take place, according to p.
 * 
 * @param p Search parameters 
 * @return Latest time an event can take place as a time_t.
 * @pre INIT_TM should be #defined as { 0, 0, 0, 1, 0, 0, 0, 0, -1 }.  
 */
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

/**
 * @brief Finds the latest time an event can take place, according to p.
 * 
 * @param p Search parameters 
 * @return Latest time an event can take place as a time_t.
 * @pre INIT_TM should be #defined as { 0, 0, 0, 1, 0, 0, 0, 0, -1 }. 
 */
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

/**
 * @brief Converts a time_t to a tm structure, prints the tm structure.
 * 
 * @param time time_t to print.
 * @pre EPOCH should be #defined as 1900.
 */
void print_time_t(time_t time) {
    tm *time_tm = localtime(&time);

    printf("%.2d/%.2d/%.2d - %.2d:%.2d\n",
           time_tm->tm_mday,
           time_tm->tm_mon + 1,
           time_tm->tm_year + EPOCH,
           time_tm->tm_hour,
           time_tm->tm_min);
}