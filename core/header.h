#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CuTest.h"

#define LINE_LEN 512
#define DO_NOTHING 0
#define INIT_TM \
    { 0, 0, 0, 1, 0, 2000, 0, 0, -1 }

typedef struct tm tm;

/**
 * @brief  Struct for holding event information.  
 * 
 */
typedef struct event {
    tm startTime;
    tm endTime;
    int priority;
    char title[LINE_LEN];
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
    int eventLen; /* in minutes */
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
void getDates(tm *startDate, tm *endDate);
void getLimits(tm *upperLimit, tm *lowerLimmit);

/* getCalendarSuite */
void getCalendarSuite(int argc, char *argv[], calendarSuite *calendarSuite);
int getCalendarSuiteGetFile(int argc, char *argv[], calendar *calendarSuite[]);
int getCalendarSuiteGetFileSingle(char arg[], calendar *calendar);
int getCalendarSuiteGetData(calendarSuite *calendarSuite);
int getCalendarSuiteGetDataSingle(calendar *calendar);
void addEventCal(event *newEvent, calendar *calendar);
/*eventLink */ void addEventCalAlt(event *newEvent, calendar *calendar);
void addEventCal(event *newEvent, calendar *calendar);
eventLink *mallocEventLink(event *event, eventLink *pointer);
int parse_file(char *);

int findAvailableDatesByLooking(void);
void findAvailableDatesByRestructuring(void);
void userOutput(void);

/* SharedFunctions */
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