#include "sp1sLib.h"
extern int DEBUG;

/**
 * @brief Controls that a time is valid in terms of minutes, hours, month number, year, month
 * day.
 * 
 * The functions take leap years into account.
 *
 * @param time struct tm, from time.h, to be controlled 
 * @return 1 if time is valid, else 0
 */
int isTimeValid(tm time) {
    int returnFlag = 0;

    returnFlag += isTimeValid_min(time.tm_min);
    returnFlag += isTimeValid_hour(time.tm_hour);
    returnFlag += isTimeValid_mon(time.tm_mon);
    returnFlag += isTimeValid_year(time.tm_year);
    returnFlag += isTimeValid_mday(time.tm_year, time.tm_mon, time.tm_mday);

    if (returnFlag == 5) {
        returnFlag = 1;
    } else {
        returnFlag = 0;
    }
    return returnFlag;
}

/**
 * @brief Controls that tm_min == [0, 59].
 * 
 * @param tm_min member of struct tm from time.h
 * @return 1 if it’s within the boundary, else 0  
 */
int isTimeValid_min(int tm_min) {
    if (tm_min >= 0 && tm_min <= 59) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Controls that tm_hour == [0, 23].
 * 
 * @param tm_hour member of struct tm from time.h
 * @return 1 if it’s within the boundary, else 0  
 */
int isTimeValid_hour(int tm_hour) {
    if (tm_hour >= 0 && tm_hour <= 23) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Controls that tm_mon == [0, 11].
 * 
 * @param tm_mon member of struct tm from time.h
 * @return 1 if it’s within the boundary, else 0  
 */
int isTimeValid_mon(int tm_mon) {
    if (tm_mon >= 0 && tm_mon <= 11) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Controls that tm_year > 1900.
 * 
 * @param tm_year member of struct tm from time.h
 * @return 1 if it’s within the boundary, else 0  
 */
int isTimeValid_year(int tm_year) {
    if (tm_year > 1970) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Controls that a month day is valid depending on the year and month.
 * 
 * @param tm_year year
 * @param tm_mon month, january is month 0
 * @param tm_mday month day
 * @return 1 if the month day is valid, else 0
 */
int isTimeValid_mday(int tm_year, int tm_mon, int tm_mday) {
    if (tm_mday <= daysInMonth(tm_mon, tm_year) && tm_mday > 0) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Calculates number of days in a month depending on the month and year.
 * 
 * @param tm_mon month, january is month 0
 * @param tm_year year
 * @return number of days in month 
 */
int daysInMonth(int tm_mon, int tm_year) {
    int returnValue;

    enum month { january,
                 february,
                 march,
                 april,
                 may,
                 june,
                 july,
                 august,
                 september,
                 october,
                 november,
                 december };

    switch (tm_mon) {
        case january:
        case march:
        case may:
        case july:
        case august:
        case october:
        case december:
            returnValue = 31;
            break;
        case april:
        case june:
        case september:
        case november:
            returnValue = 30;
            break;
        case february:
            returnValue = daysInMonthFeb(tm_year);
            break;
        default:
            returnValue = -1;
            break;
    }

    return returnValue;
}

/**
 * @brief Calculates the number of days in february on a given year.
 *
 * @param tm_year year
 * @return number of days in february 
 */
int daysInMonthFeb(int tm_year) {
    if (isLeapYear(tm_year)) {
        return 29;
    } else {
        return 28;
    }
}

/**
 * @brief Controls is a year is a leap year.
 * 
 * @param tm_year year
 * @return 1 if the year is a leap year, else 0
 */
int isLeapYear(int tm_year) {
    if (tm_year % 100 == 0 && tm_year % 400 != 0) {
        return 0;
    } else if (tm_year % 4 == 0) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief If statement is true: print errorMessage and exit program returning EXIT_FAILURE.
 * 
 * @param statement Boolean expression.
 * @param errorMessage message to print if statement is true.
 */
void errorHandling(int statement, char errorMessage[]) {
    if (statement) {
        printf("\n%s\n", errorMessage);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Prints all data stored in calendarSuite.
 * 
 * @param calendarSuite Suite to print.
 */
void printCalendars(calendarSuite *calendarSuite) {
    int i;
    for (i = 0; i < calendarSuite->Arraylen; i++) {
        printMetadataCalendar(calendarSuite->calPtrArray[i]);
        printCalendar(calendarSuite->calPtrArray[i]);
    }
}

/**
 * @brief Prints all "readable" data in a calendar structure.
 * 
 * @param calendar Calendar structure to print.
 */
void printMetadataCalendar(const calendar *calendar) {
    printf("calName: %s\n", calendar->calName);
    printf("fileName: %s\n", calendar->fileName);
    printf("numOfEvents: %d\n\n", calendar->numOfEvents);
}

/**
 * @brief Prints data stored in the linked list of eventLinks pointed to by calendar.
 * 
 * @param calendar Pointer to calendar from where the linked list should be printed.
 */
void printCalendar(const calendar *calendar) {
    eventLink *cursor;
    int i = 1;

    cursor = calendar->firstEvent;
    printf("    EVENT: 0\n");
    printEvent(cursor->currentEvent);

    while (cursor->nextEventLink != NULL) {
        cursor = cursor->nextEventLink;
        printf("    EVENT: %d\n", i);
        printEvent(cursor->currentEvent);
        i++;
    }

    printf("Number of events: %d\n", calendar->numOfEvents);
}

/**
 * @brief Prints all data from one single event structure.
 * 
 * @param a Pointer to event structure.
 */
void printEvent(const event *a) {
    printf("    SUMMARY: %s\n", a->title);
    printf("    DTSTART: %.2d/%.2d/%.2d Time: %.2d:%.2d:%.2d\n",
           a->startTime.tm_year,
           a->startTime.tm_mon,
           a->startTime.tm_mday,
           a->startTime.tm_hour,
           a->startTime.tm_min,
           a->startTime.tm_sec);
    printf("    DTEND:   %.2d/%.2d/%.2d Time: %.2d:%.2d:%.2d\n",
           a->endTime.tm_year,
           a->endTime.tm_mon,
           a->endTime.tm_mday,
           a->endTime.tm_hour,
           a->endTime.tm_min,
           a->endTime.tm_sec);
    printf("    Priority: %d\n\n", a->priority);
}

/**
 * @brief Prints all data stored in calendar structs pointed to by calendarSuite.calPtrArray
 * 
 * @param calendarSuite Suite from where the data should be printed from.
 */
void printMetadataCalendarSuite(calendarSuite calendarSuite) {
    int i;
    for (i = 0; i < calendarSuite.Arraylen; i++) {
        printf("\nCALENDAR %d: \n", i);
        printMetadataCalendar(calendarSuite.calPtrArray[i]);
    }
}
