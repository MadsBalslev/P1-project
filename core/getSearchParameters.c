#include "header.h"
extern int DEBUG;

/**
 * @brief Get the Priority object
 * 
 * @return int 
 */
int getPriority(void) {
    int priority = 0;
    int validInput = 0;
    do {
        printf("Enter a priority for the event> ");
        validInput = scanf(" %d", &priority);
        fflush(stdin);
    } while (!validInput || priority < 0);
    return priority;
}

/**
 * @brief Get the Event Len object
 * 
 * @return int 
 */
int getEventLen(void) {
    int eventLen = 0;
    int validInput = 0;
    do {
        printf("Enter estimated length of the event in minutes> ");
        validInput = scanf(" %d", &eventLen);
        fflush(stdin);
    } while (!validInput || eventLen < 0);

    return eventLen;
}

/**
 * @brief Get the Dates object
 * 
 * @param startDate 
 * @param endDate 
 */
void getDates(tm *startDate, tm *endDate) {
    int validInput = 0;
    tm tempStartDate = INIT_TM;
    tm tempEndDate = INIT_TM; 

    do {
        printf("Enter a starting date on the form dd/mm/yyyy> ");
        scanf(" %d/%d/%d", &tempStartDate.tm_mday, &tempStartDate.tm_mon, &tempStartDate.tm_year);
        tempStartDate.tm_mon--;
        validInput = isTimeValid(tempStartDate);
        fflush(stdin);
    } while (!validInput);

    do {
        printf("Enter an end date on the form dd/mm/yyyy> ");
        scanf(" %d/%d/%d", &tempEndDate.tm_mday, &tempEndDate.tm_mon, &tempEndDate.tm_year);
        tempEndDate.tm_mon--;
        validInput = isTimeValid(tempEndDate);
        fflush(stdin);
    } while (!validInput);

    if (DEBUG) {
        printf("tempStartDate: %.2d/%.2d/%.4d\n", tempStartDate.tm_mday, tempStartDate.tm_mon, tempStartDate.tm_year);
        printf("tempEndDate: %.2d/%.2d/%.4d\n   ", tempEndDate.tm_mday, tempEndDate.tm_mon, tempEndDate.tm_year);
    }

    *startDate = tempStartDate;
    *endDate = tempEndDate;
}

/**
 * @brief Get the Limits object
 * 
 * @param upperLimit 
 * @param lowerLimmit 
 */
void getLimits(tm *upperLimit, tm *lowerLimmit) {
    int validInput = 0;
    tm tempLowerLimit = INIT_TM;
    tm tempUpperLimit = INIT_TM;

    do {
        printf("Enter the earliest time the event can take place on the form HH:MM>  ");
        scanf(" %d:%d", &tempLowerLimit.tm_hour, &tempLowerLimit.tm_min);
        validInput = isTimeValid(tempLowerLimit);
        fflush(stdin);
    } while (!validInput);

    do {
        printf("Enter the latest time the event can take place on the form HH:MM>  ");
        scanf(" %d:%d", &tempUpperLimit.tm_hour, &tempUpperLimit.tm_min);
        validInput = isTimeValid(tempUpperLimit);
        fflush(stdin);
    } while (!validInput);

    if (DEBUG) {
        printf("%.2d:%.2d\n", tempLowerLimit.tm_hour, tempLowerLimit.tm_min);
        printf("%.2d:%.2d\n", tempUpperLimit.tm_hour, tempUpperLimit.tm_min);
    }

    *lowerLimmit = tempLowerLimit;
    *upperLimit = tempUpperLimit;
}