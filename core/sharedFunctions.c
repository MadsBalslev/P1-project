#include "header.h"
extern int DEBUG;

int isTimeValid(tm time) {
    int returnFlag = 1;

    /*isTimeValid_sec(time.tm_sec);*/
    isTimeValid_min(time.tm_min);
    isTimeValid_hour(time.tm_hour);
    isTimeValid_mday(time.tm_mday);
    isTimeValid_mon(time.tm_mon);
    isTimeValid_year(time.tm_year);

    return returnFlag;
}

int isTimeValid_min(int tm_min) {
    return 1;
}

int isTimeValid_hour(int tm_hour) {
    return 1;
}

int isTimeValid_mday(int tm_mday) {
    return 1;
}

int isTimeValid_mon(int tm_mon) {
    return 1;
}

int isTimeValid_year(int tm_year) {
    return 1;
}


