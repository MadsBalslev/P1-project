#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CuTest.h"

/* ctrl Args */
void ctrlArgs(int argc, char *argv[]);
int ctrlArgsAmount(int argc);
int ctrlArgsIsFile(int argc, char *argv[]);
int isIcsFile(char arg[]);
void exitWithError(void);

/* getSearchParameters */
void getSearchParameters(void);

/* getCalendarSuite */
void getCalendarSuite(void);
int parse_file(char *);

int findAvailableDatesByLooking(void);
void findAvailableDatesByRestructuring(void);
void userOutput(void);

