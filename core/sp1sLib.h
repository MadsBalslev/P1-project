#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CuTest.h"

#define LINE_LEN 512
#define DO_NOTHING 0
#define INIT_TM \
    { 0, 0, 0, 1, 0, 0, 0, 0, -1 }
#define MIN_TO_SEC 60
#define EPOCH 1900
#define MAX_PRIORITY 1000
/*#define timegm _mkgmtime*/ /* timegm for mingw */

typedef struct tm tm;

/**
 * @brief  Struct for holding event information.  
 * 
 */
typedef struct event {
    tm startTime;         /*!< The starting time of an event detailed by a tm struct from <time.h> */
    tm endTime;           /*!< The ending time of an event detailed by a tm struct from <time.h> */
    int priority;         /*!< The priority of an event. Defaults to 0 if no priority is given */
    char title[LINE_LEN]; /*!< The title of an event */
} event;

/**
 * @brief Struct for a linked list of event structs.
 * 
 */
typedef struct eventLink {
    event *currentEvent;
    struct eventLink *nextEventLink;
} eventLink;

/**
 * @brief Head of linked list of eventLinks. 
 *
 * contains metadata about the events in the eventLinks, a linked list like this is called a
 * calendar-list. Events form the same calendar are supposed to be stored in the same
 * calendar-list
 *
 */
typedef struct calendar {
    char calName[LINE_LEN];
    char fileName[LINE_LEN];
    int numOfEvents;
    FILE *file;
    eventLink *firstEvent;
} calendar;

/**
 * @brief Struct for search parameters used to scope the search of available dates in
 * calendar-lists.
 *
 */
typedef struct searchParameters {
    int priority;
    int eventLen; /*!< Length of the event in minutes */
    int buffer;   /*!< Buffer to be added at both start and end of event */
    tm startDate;
    tm endDate;
    tm upperLimit;
    tm lowerLimit;
} searchParameters;

/**
 * @brief struct for containing an array of pointer to calendar-lists. 
 * 
 * ArrayLen is the length of calPtrArray
 *
 */
typedef struct calendarSuite {
    calendar **calPtrArray;
    int Arraylen;
} calendarSuite;

enum argType { invalid,
               icsFile,
               option };

enum searchMode { bylooking,
                  byRestructuring };

enum lookForFreeSlotStatus { eol = -1, /* endOfLine */
                             look = -2 };

/* PROGRAM FUNCTIONS
 * ------------------------------------------------------------------------------------------ 
 */

/* ctrlAndDoArgs */
int ctrlAndDoArgs(int argc, char *argv[]);
void mallocCalendarSuite(int n, calendarSuite *calendarSuite);
int doArg(char arg[]);
int isIcsFile(char arg[]);
int isOption(char arg[]);
void doOption(char arg[]);
void exitWithError(void);

/* getSearchParameters */
void getSearchParameters(searchParameters *a);
int getPriority(void);
int getEventLen(void);
int getEventBuffer(void);
void getDates(tm *startDate, tm *endDate);
void getLimits(tm *lowerLimmit, tm *upperLimit);

/* getCalendarSuite */
void getCalendarSuite(int argc, char *argv[], calendarSuite *calendarSuite);
int getCalendarSuiteGetFile(int argc, char *argv[], calendar *calendarSuite[]);
int getCalendarSuiteGetFileSingle(char arg[], calendar *calendar);
int getCalendarSuiteGetData(calendarSuite *calendarSuite);
int getCalendarSuiteGetDataSingle(calendar *calendar);
void addEventCal(event *newEvent, calendar *calendar);
eventLink *mallocEventLink(event *eventP, eventLink *eventLinkP);

/* findAvailableDatesByLooking */
int findAvailableDates(calendarSuite *suite, searchParameters *param, int searchMode);
int findSumAllEvents(const calendarSuite *suite);
void calSuiteToEventArray(const calendarSuite *suite, event *eventPtrArray[], int sumAllEvents, int priority);
int endTimeCmp(const void *arg1, const void *arg2);
int eventStartsLater(event *event1, event *event2);
tm lookForFreeSlot(event *allEvents[], int arrLen, searchParameters *p);
tm lookForFreeSlotSingle(event *event, searchParameters *p, time_t *head);

int endOfLine(searchParameters *p, time_t head);
int canElongate(time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head, const searchParameters *p);
int canSwallow(time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head);
int stuck(time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head, const searchParameters *p);
tm stuckProcedure(time_t eventStartTimeUnix, time_t eventEndTimeUnix, searchParameters *p, time_t *head); 
int headWithinLimits(searchParameters *p, time_t head);  
void setHeadToNextLL (searchParameters *p, time_t *head);
void print_time_t(time_t time);
time_t getStartOfLine(const searchParameters *p);
time_t getEndOfLine(const searchParameters *p);


int withinScope(time_t unixCursor, const searchParameters *p);
tm convertUnixTime(time_t unix);
int eventBeginBeforeEnd(time_t *event1, time_t *event2);

void findAvailableDatesByRestructuring(calendarSuite *suite, const searchParameters *param);
void userOutput(void);

/* helperFunctions */
int isTimeValid(tm time);
int isTimeValid_min(int tm_min);
int isTimeValid_hour(int tm_hour);
int isTimeValid_mon(int tm_mon);
int isTimeValid_year(int tm_year);
int isTimeValid_mday(int tm_year, int tm_mon, int tm_mday);
int daysInMonth(int tm_mon, int tm_year);
int daysInMonthFeb(int tm_year);
int isLeapYear(int tm_year);
void errorHandling(int statement, char ErrorMessage[]);
void printMetadataCalendarSuite(calendarSuite calendarSuite);
void printMetadataCalendar(const calendar *calendar);
void printCalendar(const calendar *calendar);
void printCalendars(calendarSuite *calendarSuite);
void printEvent(const event *a);

void printEventPtrArray(event *allEvents[], int n);

/* UNIT TESTING FUNCTIONS
 * -------------------------------------------------------------------------------------------
 */

/* ctrlAndDoArgs */
void test1_doArg(CuTest *tc);
void test2_doArg(CuTest *tc);
void test3_doArg(CuTest *tc);
CuSuite *suite_ctrlAndDoArgs(void);

/* getCalendarSuite */
void test1_getCalendarSuiteGetFile(CuTest *tc);
void test2_getCalendarSuiteGetFile(CuTest *tc);
void test1_getCalendarSuiteGetFileSingle(CuTest *tc);
void test2_getCalendarSuiteGetFileSingle(CuTest *tc);
CuSuite *suite_getCalendarSuite(void);

/* sharedFunctions.c */
void test1_isTimeValid(CuTest *tc);
void test2_isTimeValid(CuTest *tc);
void test3_isTimeValid(CuTest *tc);
void test4_isTimeValid(CuTest *tc);
void test5_isTimeValid(CuTest *tc);
void test6_isTimeValid(CuTest *tc);
void test7_isTimeValid(CuTest *tc);
void test8_isTimeValid(CuTest *tc);
void test9_isTimeValid(CuTest *tc);
void test10_isTimeValid(CuTest *tc);
CuSuite *suite_sharedFunctions(void);

/* general */
void runAllTests(void);
