#include "sp1sLib.h"
extern int DEBUG;

/**
 * @brief Get the Priority object
 *
 * Here we ask for a priority for the event. Once the user has given us a valid input, then we
 * return the priority from the function.
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
 *
 * Here we ask for the length of the event in minutes, and check if it's a valid and positiv
 * input we are getting. If yes, then we return the length from the function.
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
 * @brief Prompts user: Enter how much buffer time should be in beginning and end of event.
 * 
 * Input by user can not be under 0.
 * 
 * @return Buffer entered.  
 */
int getEventBuffer(void) {
    int eventBuffer = 0;
    int validInput = 0;
    do {
        printf("Enter how much buffer time should be in beginning and end of event in minutes> ");
        validInput = scanf(" %d", &eventBuffer);
        fflush(stdin);
    } while (!validInput || eventBuffer < 0);

    return eventBuffer;
}

/**
 * @brief Get the Dates object
 * 
 * 
 * First we ask for a start date, and reduce the value by 1. We do this because tm_mon in the
 * tm struct, uses months after january, so if we want the event to start in february, the
 * input needs to be 1 because february is one month after january. We do this for the endDate
 * for the event as well. And to end it off we print the dates and confirm the start- and end
 * dates, if DEBUG == 1.
 * 
 * @param startDate 
 * @param endDate 
 */
void getDates(tm *startDate, tm *endDate) {
    int validInput = 0;
    tm tempStartDate = INIT_TM;
    tm tempEndDate = INIT_TM; 

    do {
        printf("Enter the earliest date the event can take place in the format: dd/mm/yyyy> ");
        scanf(" %d/%d/%d", &tempStartDate.tm_mday, &tempStartDate.tm_mon, &tempStartDate.tm_year);
        tempStartDate.tm_mon--;
        tempStartDate.tm_year = tempStartDate.tm_year - EPOCH;
        validInput = isTimeValid(tempStartDate);
        fflush(stdin);
    } while (!validInput);

    do {
        printf("Enter the latest date the event can take place in the format: dd/mm/yyyy> ");
        scanf(" %d/%d/%d", &tempEndDate.tm_mday, &tempEndDate.tm_mon, &tempEndDate.tm_year);
        tempEndDate.tm_mon--;
        tempEndDate.tm_year = tempEndDate.tm_year - EPOCH;
        validInput = isTimeValid(tempEndDate);
        fflush(stdin);
    } while (!validInput);

    if (DEBUG) {
        printf("tempStartDate: %.2d/%.2d/%.4d\n", tempStartDate.tm_mday, tempStartDate.tm_mon, tempStartDate.tm_year + EPOCH);
        printf("tempEndDate: %.2d/%.2d/%.4d\n", tempEndDate.tm_mday, tempEndDate.tm_mon, tempEndDate.tm_year + EPOCH);
    }

    *startDate = tempStartDate;
    *endDate = tempEndDate;
}

/**
 * @brief Get the Limits object
 * 
 * Here we ask how much the event can be moved witin the same day, so only hours and minutes.
 * We do this for both the upper- and lower limit. And at the end of the function we print,
 * and confirm the upper- and lower limit, if DEBUG == 1.
 * 
 * @param upperLimit 
 * @param lowerLimmit 
 */
void getLimits(tm *lowerLimmit, tm *upperLimit) {
    int validInput = 0;
    tm tempLowerLimit = INIT_TM;
    tm tempUpperLimit = INIT_TM;

    do {
        printf("Enter the earliest time the event can take place in the format: HH:MM>  ");
        scanf(" %d:%d", &tempLowerLimit.tm_hour, &tempLowerLimit.tm_min);
        validInput = isTimeValid(tempLowerLimit);
        fflush(stdin);
    } while (!validInput);

    do {
        printf("Enter the latest time the event can take place in the format: HH:MM>  ");
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
