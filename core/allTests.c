#include "header.h"

extern int DEBUG;

void runAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, suite_ctrlAndDoArgs());

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