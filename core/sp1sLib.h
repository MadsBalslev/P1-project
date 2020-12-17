/* !!! DO NOT AUTOFORMAT THIS FILE !!! */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CuTest.h"

#define LINE_LEN      512
#define DO_NOTHING      0
#define MIN_TO_SEC     60
#define EPOCH        1900
#define MAX_PRIORITY 1000

#define UNIX_24H 60 * 60 * 24;
#define INIT_TM \
    { 0, 0, 0, 1, 0, 0, 0, 0, -1 }

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
    event *currentEvent;             /*!< Event data */ 
    struct eventLink *nextEventLink; /*!< Next link i linked list */
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
    char calName[LINE_LEN];  /*!< Name of calendar */ 
    char fileName[LINE_LEN]; /*!< Filepath to *.ics file */
    int numOfEvents;         /*!< Number of events linked to this calendar */
    FILE *file;              /*!< Pointer to FILE */
    eventLink *firstEvent;   /*!< Pointer to first eventLink */
} calendar;

/**
 * @brief Struct for search parameters used to scope the search of available dates in
 * calendar-lists.
 *
 */
typedef struct searchParameters {
    int priority;  /*!< Priority of the event */
    int eventLen;  /*!< Length of the event in minutes */
    int buffer;    /*!< Buffer to be added at both start and end of event */
    tm startDate;  /*!< Earliest date event can take place */
    tm endDate;    /*!< Latest date event can take place */
    tm upperLimit; /*!< Earliest time event can take place. */
    tm lowerLimit; /*!< Latest time event can take place.*/ 
} searchParameters;

/**
 * @brief struct for containing an array of pointer to calendar-lists. 
 * 
 * ArrayLen is the length of calPtrArray
 *
 */
typedef struct calendarSuite {
    calendar **calPtrArray; /*!< Array of pointers to calendar structs*/
    int Arraylen;           /*!< lenght of above array */
} calendarSuite;

enum argType { invalid,
               icsFile,
               option };

enum searchMode { bylooking,
                  byRestructuring };

enum lookForFreeSlotStatus { eol = -1, /* endOfLine */
                             look = -2,
                             redo = -3 };

/* PROGRAM FUNCTIONS
 * ------------------------------------------------------------------------------------------ 
 */

/* ctrlAndDoArgs */
int  ctrlAndDoArgs      (int argc, char *argv[]);
void mallocCalendarSuite(int n, calendarSuite *calendarSuite);
int  doArg              (char arg[]);
int  isIcsFile          (char arg[]);
int  isOption           (char arg[]);
void doOption           (char arg[]);
void exitWithError      (void);

/* getSearchParameters */
void getSearchParameters(searchParameters *a);
int  getPriority        (void);
int  getEventLen        (void);
int  getEventBuffer     (void);
void getDates           (tm *startDate, tm *endDate);
void getLimits          (tm *lowerLimmit, tm *upperLimit);

/* getCalendarSuite */
void       getCalendarSuite             (int argc, char *argv[], calendarSuite *calendarSuite);
int        getCalendarSuiteGetFile      (int argc, char *argv[], calendar *calendarSuite[]);
int        getCalendarSuiteGetFileSingle(char arg[], calendar *calendar);
int        getCalendarSuiteGetData      (calendarSuite *calendarSuite);
int        getCalendarSuiteGetDataSingle(calendar *calendar);
void       addEventCal                  (event *newEvent, calendar *calendar);
eventLink *mallocEventLink              (event *eventP, eventLink *eventLinkP);

/* findAvailableDatesByLooking */
int    findAvailableDates   (calendarSuite *suite, const searchParameters *param, int searchMode);
int    findSumAllEvents     (const calendarSuite *suite);
void   calSuiteToEventArray (const calendarSuite *suite, int sumAllEvents, int priority, event *eventPtrArray[]);
int    startTimeCmp         (const void *arg1, const void *arg2);
int    eventStartsEarlier   (const event *event1, const event *event2);
tm     lookForFreeSlot      (const searchParameters *p, int arrLen, event *allEvents[]);
tm     lookForFreeSlotSingle(const searchParameters *p, event *event, time_t *head);
int    endOfLine            (const searchParameters *p, time_t head);
int    canElongate          (time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head, const searchParameters *p);
int    canSwallow           (time_t eventStartTimeUnix, time_t eventEndTimeUnix, time_t head);
int    stuck                (time_t eventStartTimeUnix, time_t head, const searchParameters *p);
tm     stuckProcedure       (const searchParameters *p, time_t *head);
int    headWithinLimits     (const searchParameters *p, time_t head);
int    tmWithinLimits       (const searchParameters *p, const tm *time);
void   setHeadToNextLL      (const searchParameters *p, time_t *head);
int    overUpperLimit       (const searchParameters *p, const tm *head_tm);
int    underLowerLimit      (const searchParameters *p, const tm *head_tm);
void   goToLowerLimitNextDay(time_t head, const searchParameters *p, tm *head_tm);
void   goToLowerLimitThisDay(const searchParameters *p, tm *head_tm);
time_t getStartOfLine       (const searchParameters *p);
time_t getEndOfLine         (const searchParameters *p);
void   print_time_t         (time_t time);

/* helperFunctions */
int  isTimeValid               (tm time);
int  isTimeValid_min           (int tm_min);
int  isTimeValid_hour          (int tm_hour);
int  isTimeValid_mon           (int tm_mon);
int  isTimeValid_year          (int tm_year);
int  isTimeValid_mday          (int tm_year, int tm_mon, int tm_mday);
int  daysInMonth               (int tm_mon, int tm_year);
int  daysInMonthFeb            (int tm_year);
int  isLeapYear                (int tm_year);
void errorHandling             (int statement, char ErrorMessage[]);
void printMetadataCalendarSuite(calendarSuite calendarSuite);
void printMetadataCalendar     (const calendar *calendar);
void printCalendar             (const calendar *calendar);
void printCalendars            (calendarSuite *calendarSuite);
void printEvent                (const event *a);
void printEventPtrArray        (event *allEvents[], int n);

/* UNIT TESTING FUNCTIONS
 * -------------------------------------------------------------------------------------------
 */
CuSuite *suite_ctrlAndDoArgs     (void);
CuSuite *suite_getCalendarSuite  (void);
CuSuite *suite_findAvaliableDates(void);
CuSuite *suite_sharedFunctions   (void);
void    runAllTests              (void);
