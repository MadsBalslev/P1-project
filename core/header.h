#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CuTest.h"

#define DO_NOTHING 0
#define INIT_TM \
    { 0, 0, 0, 1, 0, 2000, 0, 0, -1 }

typedef struct tm tm;

typedef struct event {
    tm startTime;
    tm endTime;
    int priority;
    char *title;
} event;

typedef struct eventLink {
    event *currentEvent;
    struct eventLink *nextEventLink;
} eventLink;

typedef struct calendar {
    char *calName;
    int numOfEvents;
    event *firstEvent;
} calendar;

typedef struct searchParameters {
    int priority;
    int eventLen; /* in minutes */
    tm startDate;
    tm endDate;
    tm upperLimit;
    tm lowerLimit;
} searchParameters;

enum argType { invalid,
               icsFile,
               option };

/* PROGRAM FUNCTIONS
 * ------------------------------------------------------------------------------------------ 
 */

/* ctrlAndDoArgs */
void ctrlAndDoArgs(int argc, char *argv[]);
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
void getCalendarSuite(void);
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
int daysInMonThFeb(int tm_year);
int isLeapYear(int tm_year);

/* UNIT TESTING FUNCTIONS
 * -------------------------------------------------------------------------------------------
 */

/* ctrlAndDoArgs */
void test1_doArg(CuTest *tc);
void test2_doArg(CuTest *tc);
void test3_doArg(CuTest *tc);
CuSuite *suite_ctrlAndDoArgs(void);

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