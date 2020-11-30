#include "header.h"

extern int DEBUG;

void runAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    CuSuiteAddSuite(suite, suite_doArgs());

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
    int expected = 0;
    CuAssertIntEquals(tc, expected, actual);
}

CuSuite *suite_doArgs(void) {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test1_doArg);
    return suite;
}