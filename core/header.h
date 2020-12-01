#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CuTest.h"

#define DO_NOTHING 0

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
void doIcsFile(char arg[]);
void exitWithError(void);

/* getSearchParameters */
void getSearchParameters(void);

/* getCalendarSuite */
void getCalendarSuite(void);
int parse_file(char *);

int findAvailableDatesByLooking(void);
void findAvailableDatesByRestructuring(void);
void userOutput(void);

/* UNIT TESTING FUNCTIONS
 * -------------------------------------------------------------------------------------------
 */

/* ctrlAndDoArgs */
void test1_doArg(CuTest *tc);
CuSuite *suite_ctrlAndDoArgs(void);

/* general */
void runAllTests(void);