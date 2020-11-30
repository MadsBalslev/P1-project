#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CuTest.h"

#define DO_NOTHING 0

struct event {
  tm startTime;
  tm endTime;
  int priority;
  char *title;
  struct event *nextEvent;
};
typedef struct event event;

struct calendar {
  char *calName;
  int numOfEvents;
  event *firstEvent;
};
typedef struct calendar calendar;

enum argType { icsFile = 1,
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
CuSuite *suite_doArgs(void);

/* general */
void runAllTests(void);