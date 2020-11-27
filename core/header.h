#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CuTest.h"


/* PROGRAM FUNCTIONS
 * ------------------------------------------------------------------------------------------ 
 */

/* ctrlArgs */
void ctrlArgs(int argc, char *argv[]);
int ctrlArgsAmount(int argc);
int  ctrlArgsIsValidType(int argc, char *argv[]);
int argIsValid(char arg[]);
int isIcsFile(char arg[]);
int isOption(char arg[]);
void doOptions(int argc, char *argv[]);
void doOptionsSingle(char arg[]);
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

/* ctrlArgs */
void test1_ctrlArgsAmount(CuTest *tc);
void test2_ctrlArgsAmount(CuTest *tc);
/*void test_ctrlArgsIsFile(CuTest *tc);*/
CuSuite *suite_ctrlArgs(void);

/* general */
void runAllTests(void);