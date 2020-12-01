#include "header.h"
extern int DEBUG;

int isTimeValid(tm time) {
    int returnFlag = 0;

    /*isTimeValid_sec(time.tm_sec);*/
    printf("0: %d\n", returnFlag);
    returnFlag += isTimeValid_min(time.tm_min);
    printf("1: %d\n", returnFlag);
    returnFlag += isTimeValid_hour(time.tm_hour);
    printf("2: %d\n", returnFlag);
    returnFlag += isTimeValid_mon(time.tm_mon);
    printf("3: %d\n", returnFlag);
    returnFlag += isTimeValid_mday(time.tm_mday);
    printf("4: %d\n", returnFlag);
    returnFlag += isTimeValid_year(time.tm_year);
    printf("5: %d\n", returnFlag);

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
            /* code */
            break;

        default:
            break;
    }
}

int isLeapYear(tm_year) {
    if (tm_year % 100 == 0 && tm_year % 400 != 0) {
        return 0;
    } else if (tm_year % 4 == 0) {
        return 1;
    } else {
        return 0;
    }
}


