#include "header.h"

extern int DEBUG;

void runAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, suite_ctrlAndDoArgs());
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
    tm input = {0, 0, 0, 30, 2, 2004, 0, 0, -1};
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
    return suite;
}

