#include "sp1sLib.h"

extern int DEBUG;

void runAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, suite_ctrlAndDoArgs());
    CuSuiteAddSuite(suite, suite_getCalendarSuite());
    CuSuiteAddSuite(suite, suite_findAvaliableDates());
    CuSuiteAddSuite(suite, suite_sharedFunctions());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

/* ctrlArgs 
 * -------------------------------------------------------------------------------------------
 */
void test1_doArg(CuTest *tc) {
    char input[] = "test";
    int actual = doArg(input);
    int expected = invalid;
    CuAssertIntEquals(tc, expected, actual);
}

void test2_doArg(CuTest *tc) {
    char input[] = "--doNothing";
    int actual = doArg(input);
    int expected = option;
    CuAssertIntEquals(tc, expected, actual);
}

void test3_doArg(CuTest *tc) {
    char input[] = "*.ics";
    int actual = doArg(input);
    int expected = icsFile;
    CuAssertIntEquals(tc, expected, actual);
}

CuSuite *suite_ctrlAndDoArgs(void) {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test1_doArg);
    SUITE_ADD_TEST(suite, test2_doArg);
    SUITE_ADD_TEST(suite, test3_doArg);
    return suite;
}

/* getCalendarSuite.c
 * -------------------------------------------------------------------------------------------
 */
void test1_getCalendarSuiteGetFile(CuTest *tc) {
    int actual;
    int expected;
    int input1 = 4;
    char *input2[] = {"a", ".\\sample-ics-files\\cal1.ics", ".\\sample-ics-files\\cal2.ics", ".\\sample-ics-files\\cal3.ics"};
    calendarSuite input3;
    mallocCalendarSuite(3, &input3);
    actual = getCalendarSuiteGetFile(input1, input2, input3.calPtrArray);
    expected = 1;
    free(input3.calPtrArray);
    CuAssertIntEquals(tc, expected, actual);
}

void test2_getCalendarSuiteGetFile(CuTest *tc) {
    int actual;
    int expected;
    int input1 = 4;
    char *input2[] = {"a", ".\\sample-ics-files\\notAValidFileLocation.ics", ".\\sample-ics-files\\cal2.ics", ".\\sample-ics-files\\cal3.ics"};
    calendarSuite input3;
    mallocCalendarSuite(3, &input3);
    actual = getCalendarSuiteGetFile(input1, input2, input3.calPtrArray);
    expected = 0;
    free(input3.calPtrArray);
    CuAssertIntEquals(tc, expected, actual);
}

void test1_getCalendarSuiteGetFileSingle(CuTest *tc) {
    char input1[] = ".\\sample-ics-files\\cal1.ics";
    calendar input2;
    int actual = getCalendarSuiteGetFileSingle(input1, &input2);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test2_getCalendarSuiteGetFileSingle(CuTest *tc) {
    char input1[] = ".\\sample-ics-files\\notAValidFileLocation.ics";
    calendar input2;
    int actual = getCalendarSuiteGetFileSingle(input1, &input2);
    int expected = 0;
    CuAssertIntEquals(tc, expected, actual);
}

CuSuite *suite_getCalendarSuite(void) {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test1_getCalendarSuiteGetFile);
    SUITE_ADD_TEST(suite, test2_getCalendarSuiteGetFile);
    SUITE_ADD_TEST(suite, test1_getCalendarSuiteGetFileSingle);
    SUITE_ADD_TEST(suite, test2_getCalendarSuiteGetFileSingle);
    return suite;
}

/* findAvaliableDates.c
 * -------------------------------------------------------------------------------------------
*/
void test1_underLowerLimit(CuTest *tc) {
    int actual, expected;
    searchParameters p;
    tm head;

    p.lowerLimit.tm_hour = 8;
    p.lowerLimit.tm_min = 0;

    head.tm_hour = 10;
    head.tm_min = 30;

    actual = underLowerLimit(&p, &head);
    expected = 0;

    CuAssertIntEquals(tc, expected, actual);
}

void test2_underLowerLimit(CuTest *tc) {
    int actual, expected;
    searchParameters p;
    tm head;

    p.lowerLimit.tm_hour = 8;
    p.lowerLimit.tm_min = 0;

    head.tm_hour = 8;
    head.tm_min = 0;

    actual = underLowerLimit(&p, &head);
    expected = 0;

    CuAssertIntEquals(tc, expected, actual);
}

void test3_underLowerLimit(CuTest *tc) {
    int actual, expected;
    searchParameters p;
    tm head;

    p.lowerLimit.tm_hour = 8;
    p.lowerLimit.tm_min = 0;

    head.tm_hour = 7;
    head.tm_min = 50;

    actual = underLowerLimit(&p, &head);
    expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}

void test1_tmWithinLimits(CuTest *tc) {
    int actual, expected;
    searchParameters p;
    tm head;

    p.lowerLimit.tm_hour = 8;
    p.lowerLimit.tm_min = 0;
    p.upperLimit.tm_hour = 16;
    p.upperLimit.tm_min = 0;

    head.tm_hour = 10;
    head.tm_min = 30;

    actual = tmWithinLimits(&p, &head);
    expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}

void test2_tmWithinLimits(CuTest *tc) {
    int actual, expected;
    searchParameters p;
    tm head;

    p.lowerLimit.tm_hour = 8;
    p.lowerLimit.tm_min = 0;
    p.upperLimit.tm_hour = 16;
    p.upperLimit.tm_min = 0;

    head.tm_hour = 8;
    head.tm_min = 0;

    actual = tmWithinLimits(&p, &head);
    expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}

void test3_tmWithinLimits(CuTest *tc) {
    int actual, expected;
    searchParameters p;
    tm head;

    p.lowerLimit.tm_hour = 8;
    p.lowerLimit.tm_min = 0;
    p.upperLimit.tm_hour = 16;
    p.upperLimit.tm_min = 0;

    head.tm_hour = 7;
    head.tm_min = 50;

    actual = tmWithinLimits(&p, &head);
    expected = 0;

    CuAssertIntEquals(tc, expected, actual);
}

void test1_headWithinLimits(CuTest *tc) {
    int actual, expected;
    searchParameters p;
    time_t unixHead;

    p.lowerLimit.tm_hour = 8;
    p.lowerLimit.tm_min = 0;
    p.upperLimit.tm_hour = 16;
    p.upperLimit.tm_min = 0;
    p.eventLen = 60;
    p.buffer = 10;

    /* 04/01/2021 15:00 */
    unixHead = 1609772400;

    actual = headWithinLimits(&p, unixHead);
    expected = 0;

    CuAssertIntEquals(tc, expected, actual);
}

void test2_headWithinLimits(CuTest *tc) {
    int actual, expected;
    searchParameters p;
    time_t unixHead;

    p.lowerLimit.tm_hour = 8;
    p.lowerLimit.tm_min = 0;
    p.upperLimit.tm_hour = 16;
    p.upperLimit.tm_min = 0;
    p.eventLen = 60;
    p.buffer = 10;

    /* 04/01/2021 10:00 */
    unixHead = 1609754400;

    actual = headWithinLimits(&p, unixHead);
    expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}

void test1_canElongate(CuTest *tc) {
    searchParameters p;
    time_t eventStartTimeUnix, eventEndTimeUnix, head;
    int actual, expected;

    p.eventLen = 60;
    p.buffer = 10;

    /* 04/01/2021 10:00 */
    head = 1609754400;

    /* 04/01/2021 13:00 */
    eventStartTimeUnix = 1609765200;
    /* 04/01/2021 15:00 */
    eventEndTimeUnix = 1609772400;

    actual = canElongate(eventStartTimeUnix, eventEndTimeUnix, head, &p);
    expected = 0;

    CuAssertIntEquals(tc, expected, actual);
}

void test2_canElongate(CuTest *tc) {
    searchParameters p;
    time_t eventStartTimeUnix, eventEndTimeUnix, head;
    int actual, expected;

    p.eventLen = 60;
    p.buffer = 10;

    /* 04/01/2021 10:00 */
    head = 1609754400;

    /* 04/01/2021 10:30 */
    eventStartTimeUnix = 1609756200;
    /* 04/01/2021 15:00 */
    eventEndTimeUnix = 1609772400;

    actual = canElongate(eventStartTimeUnix, eventEndTimeUnix, head, &p);
    expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}

void test3_canElongate(CuTest *tc) {
    searchParameters p;
    time_t eventStartTimeUnix, eventEndTimeUnix, head;
    int actual, expected;

    p.eventLen = 60;
    p.buffer = 10;

    /* 04/01/2021 10:00 */
    head = 1609754400;

    /* 04/01/2021 09:00 */
    eventStartTimeUnix = 1609750800;
    /* 04/01/2021 15:00 */
    eventEndTimeUnix = 1609772400;

    actual = canElongate(eventStartTimeUnix, eventEndTimeUnix, head, &p);
    expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}

void test1_endOfLine(CuTest *tc) {
    searchParameters p;
    time_t head;
    int actual, expected;

    p.upperLimit.tm_hour = 16;
    p.upperLimit.tm_min = 0;
    p.endDate.tm_year = 121;
    p.endDate.tm_mon = 0;
    p.endDate.tm_mday = 4;

    /* 04/01/2021 19:00 */
    head = 1609786800;

    actual = endOfLine(&p, head);
    expected = 1;

    CuAssertIntEquals(tc, expected, actual);
}

void test2_endOfLine(CuTest *tc) {
    searchParameters p;
    time_t head;
    int actual, expected;

    p.upperLimit.tm_hour = 16;
    p.upperLimit.tm_min = 0;
    p.endDate.tm_year = 121;
    p.endDate.tm_mon = 1;
    p.endDate.tm_mday = 4;

    /* 04/01/2021 12:00 */
    head = 1609761600;

    actual = endOfLine(&p, head);
    expected = 0;

    CuAssertIntEquals(tc, expected, actual);
}

void test1_canSwallow(CuTest *tc) {
    time_t eventStartTime, eventEndTime, head;
    int actual, expected;

    /* 04/01/2021 08:00 */
    eventStartTime = 1609747200;
    /* 04/01/2021 14:00 */
    eventEndTime = 1609768800;
    /* 04/01/2021 15:00 */
    head = 1609772400;

    actual = canSwallow(eventStartTime, eventEndTime, head);
    expected = 1;

    CuAssertIntEquals(tc, expected, actual);        
}

void test2_canSwallow(CuTest *tc) {
    time_t eventStartTime, eventEndTime, head;
    int actual, expected;

    /* 04/01/2021 08:00 */
    eventStartTime = 1609747200;
    /* 04/01/2021 14:00 */
    eventEndTime = 1609768800;
    /* 04/01/2021 12:00 */
    head = 1609761600;       

    actual = canSwallow(eventStartTime, eventEndTime, head);
    expected = 0;

    CuAssertIntEquals(tc, expected, actual);    
}

void test1_goToLowerLimitThisDay(CuTest *tc) {
    searchParameters input1;
    tm input2;
    int expected1;
    int expected2;

    input1.lowerLimit.tm_min  = 15;
    input1.lowerLimit.tm_hour = 06;

    input2.tm_min  = 00;
    input2.tm_hour = 00;

    expected1 = 15;
    expected2 = 06;

    goToLowerLimitThisDay(&input1, &input2);

    CuAssertIntEquals(tc, expected1, input2.tm_min);
    CuAssertIntEquals(tc, expected2, input2.tm_hour);
}

void test1_goToLowerLimitNextDay(CuTest *tc) {
    time_t input1;
    searchParameters input2;
    tm input3;
    int expected1 = 00;  
    int expected2 = 15;
    int expected3 = 06;
    int expected4 = 01;
    int expected5 = 00;
    int expected6 = 2021 - EPOCH;

    input2.lowerLimit.tm_min  = 15;
    input2.lowerLimit.tm_hour = 06;

    input3.tm_sec  = 00;
    input3.tm_min  = 00;
    input3.tm_hour = 00;
    input3.tm_mday = 31;
    input3.tm_mon  = 11;
    input3.tm_year = 2020 - EPOCH;

    input1 = mktime(&input3);

    goToLowerLimitNextDay(input1, &input2, &input3);

    CuAssertIntEquals(tc, expected1, input3.tm_sec);
    CuAssertIntEquals(tc, expected2, input3.tm_min);
    CuAssertIntEquals(tc, expected3, input3.tm_hour);
    CuAssertIntEquals(tc, expected4, input3.tm_mday);
    CuAssertIntEquals(tc, expected5, input3.tm_mon);
    CuAssertIntEquals(tc, expected6, input3.tm_year);
}

void test2_goToLowerLimitNextDay(CuTest *tc) {
    time_t input1;
    searchParameters input2;
    tm input3;
    int expected1 = 00;  
    int expected2 = 15;
    int expected3 = 06;
    int expected4 = 01;
    int expected5 = 02;
    int expected6 = 2003 - EPOCH;

    input2.lowerLimit.tm_min  = 15;
    input2.lowerLimit.tm_hour = 06;

    input3.tm_sec  = 00;
    input3.tm_min  = 00;
    input3.tm_hour = 00;
    input3.tm_mday = 28;
    input3.tm_mon  = 01;
    input3.tm_year = 2003 - EPOCH;

    input1 = mktime(&input3);

    goToLowerLimitNextDay(input1, &input2, &input3);

    CuAssertIntEquals(tc, expected1, input3.tm_sec);
    CuAssertIntEquals(tc, expected2, input3.tm_min);
    CuAssertIntEquals(tc, expected3, input3.tm_hour);
    CuAssertIntEquals(tc, expected4, input3.tm_mday);
    CuAssertIntEquals(tc, expected5, input3.tm_mon);
    CuAssertIntEquals(tc, expected6, input3.tm_year);
}

void test3_goToLowerLimitNextDay(CuTest *tc) {
    time_t input1;
    searchParameters input2;
    tm input3;
    int expected1 = 00;  
    int expected2 = 15;
    int expected3 = 06;
    int expected4 = 01;
    int expected5 = 02;
    int expected6 = 2004 - EPOCH;

    input2.lowerLimit.tm_min  = 15;
    input2.lowerLimit.tm_hour = 06;

    input3.tm_sec  = 00;
    input3.tm_min  = 00;
    input3.tm_hour = 00;
    input3.tm_mday = 29;
    input3.tm_mon  = 01;
    input3.tm_year = 2004 - EPOCH;

    input1 = mktime(&input3);

    goToLowerLimitNextDay(input1, &input2, &input3);

    CuAssertIntEquals(tc, expected1, input3.tm_sec);
    CuAssertIntEquals(tc, expected2, input3.tm_min);
    CuAssertIntEquals(tc, expected3, input3.tm_hour);
    CuAssertIntEquals(tc, expected4, input3.tm_mday);
    CuAssertIntEquals(tc, expected5, input3.tm_mon);
    CuAssertIntEquals(tc, expected6, input3.tm_year);
}

void test1_eventStartsEarlier(CuTest *tc) {
    event input1;
    event input2;
    int actual;
    int expected = 0;
    tm init = INIT_TM;
    
    input1.startTime = init;
    input1.endTime = init;
    
    input2.startTime = init;
    input2.endTime = init;

    input2.startTime.tm_min  = 16;
    input2.startTime.tm_hour = 16;
    input2.startTime.tm_mon  = 02;
    input2.startTime.tm_mday = 02;

    actual = eventStartsEarlier(&input1, &input2);
    CuAssertIntEquals(tc, expected, actual);
}

void test2_eventStartsEarlier(CuTest *tc) {
    event input1;
    event input2;
    int actual;
    int expected = 1;
    tm init = INIT_TM;
    
    input1.startTime = init;
    input1.endTime = init;
    
    input2.startTime = init;
    input2.endTime = init;

    input1.startTime.tm_min  = 16;
    input1.startTime.tm_hour = 16;
    input1.startTime.tm_mon  = 02;
    input1.startTime.tm_mday = 02;

    actual = eventStartsEarlier(&input1, &input2);
    CuAssertIntEquals(tc, expected, actual);

}

CuSuite *suite_findAvaliableDates(void) {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test1_underLowerLimit);
    SUITE_ADD_TEST(suite, test2_underLowerLimit);
    SUITE_ADD_TEST(suite, test3_underLowerLimit);
    SUITE_ADD_TEST(suite, test1_tmWithinLimits);
    SUITE_ADD_TEST(suite, test2_tmWithinLimits);
    SUITE_ADD_TEST(suite, test3_tmWithinLimits);
    SUITE_ADD_TEST(suite, test1_headWithinLimits);
    SUITE_ADD_TEST(suite, test2_headWithinLimits);
    SUITE_ADD_TEST(suite, test1_canElongate);
    SUITE_ADD_TEST(suite, test2_canElongate);
    SUITE_ADD_TEST(suite, test3_canElongate);
    SUITE_ADD_TEST(suite, test1_endOfLine);
    SUITE_ADD_TEST(suite, test2_endOfLine);
    SUITE_ADD_TEST(suite, test1_canSwallow);
    SUITE_ADD_TEST(suite, test2_canSwallow);
    SUITE_ADD_TEST(suite, test1_goToLowerLimitThisDay);
    SUITE_ADD_TEST(suite, test1_goToLowerLimitNextDay);
    SUITE_ADD_TEST(suite, test2_goToLowerLimitNextDay);
    SUITE_ADD_TEST(suite, test3_goToLowerLimitNextDay);
    SUITE_ADD_TEST(suite, test1_eventStartsEarlier);
    SUITE_ADD_TEST(suite, test2_goToLowerLimitNextDay);
    
    return suite;
}

/* SharedFunctions.c
 * -------------------------------------------------------------------------------------------
 */
void test1_isTimeValid(CuTest *tc) {
    tm input = INIT_TM;
    int actual = isTimeValid(input);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test2_isTimeValid(CuTest *tc) {
    tm input = {0, 25, 20, 16, 4, 2009, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test3_isTimeValid(CuTest *tc) {
    tm input = {0, 0, 0, 29, 2, 2004, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test4_isTimeValid(CuTest *tc) {
    tm input = {0, 0, 0, 30, 1, 2004, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 0;
    CuAssertIntEquals(tc, expected, actual);
}

void test5_isTimeValid(CuTest *tc) {
    tm input = {0, 0, 0, 28, 1, 2005, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test6_isTimeValid(CuTest *tc) {
    tm input = {0, 0, 0, 31, 0, 2005, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test7_isTimeValid(CuTest *tc) {
    tm input = {0, 0, 0, 32, 0, 2005, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 0;
    CuAssertIntEquals(tc, expected, actual);
}

void test8_isTimeValid(CuTest *tc) {
    tm input = {0, 0, 0, 30, 3, 2005, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test9_isTimeValid(CuTest *tc) {
    tm input = {0, 0, 0, 31, 3, 2005, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 0;
    CuAssertIntEquals(tc, expected, actual);
}

void test10_isTimeValid(CuTest *tc) {
    tm input = {0, 61, 25, 1, 0, 2000, 0, 0, -1};
    int actual = isTimeValid(input);
    int expected = 0;
    CuAssertIntEquals(tc, expected, actual);
}

CuSuite *suite_sharedFunctions(void) {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test1_isTimeValid);
    SUITE_ADD_TEST(suite, test2_isTimeValid);
    SUITE_ADD_TEST(suite, test3_isTimeValid);
    SUITE_ADD_TEST(suite, test4_isTimeValid);
    SUITE_ADD_TEST(suite, test5_isTimeValid);
    SUITE_ADD_TEST(suite, test6_isTimeValid);
    SUITE_ADD_TEST(suite, test7_isTimeValid);
    SUITE_ADD_TEST(suite, test8_isTimeValid);
    SUITE_ADD_TEST(suite, test9_isTimeValid);
    SUITE_ADD_TEST(suite, test10_isTimeValid);
    return suite;
}
