#include "header.h"
extern int DEBUG;

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

int isTimeValid_min(int tm_min) {
    if (tm_min >= 0 && tm_min <= 59) {
        return 1;
    } else {
        return 0;
    }
}

int isTimeValid_hour(int tm_hour) {
    if (tm_hour >= 0 && tm_hour <= 23) {
        return 1;
    } else {
        return 0;
    }
}

int isTimeValid_mon(int tm_mon) {
    if (tm_mon >= 0 && tm_mon <= 11) {
        return 1;
    } else {
        return 0;
    }
}

int isTimeValid_year(int tm_year) {
    if (tm_year > 1900) {
        return 1;
    } else {
        return 0;
    }
}

int isTimeValid_mday(int tm_year, int tm_mon, int tm_mday) {
    if (tm_mday <= daysInMonth(tm_mon, tm_year) && tm_mday > 0) {
        return 1;
    } else {
        return 0;
    }
}

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
            returnValue = daysInMonThFeb(tm_year);
            break;
        default:
            returnValue = -1;
            break;
    }

    return returnValue;
}

int daysInMonThFeb(int tm_year) {
    if (isLeapYear(tm_year)) {
        return 29;
    } else {
        return 28;
    }
}

int isLeapYear(int tm_year) {
    if (tm_year % 100 == 0 && tm_year % 400 != 0) {
        return 0;
    } else if (tm_year % 4 == 0) {
        return 1;
    } else {
        return 0;
    }
}
