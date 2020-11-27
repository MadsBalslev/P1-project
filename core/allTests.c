#include "header.h"


/* ctrlArgs */
void test1_ctrlArgsAmount(CuTest *tc);
void test2_ctrlArgsAmount(CuTest *tc);
/*void test_ctrlArgsIsFile(CuTest *tc);*/
CuSuite *suite_ctrlArgs(void);

/* general */
void RunAllTests(void);


int main(void) {
    RunAllTests();
    return EXIT_SUCCESS;
}

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    CuSuiteAddSuite(suite, suite_ctrlArgs());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

/* ctrlArgs 
 * -------------------------------------------------------------------------------------------
 */
void test1_ctrlArgsAmount(CuTest *tc) {
    int input = 4;
    int actual = ctrlArgsAmount(input);
    int expected = 1;
    CuAssertIntEquals(tc, expected, actual);
}

void test2_ctrlArgsAmount(CuTest *tc) {
    int input = 1;
    int actual = ctrlArgsAmount(input);
    int expected = 0;
    CuAssertIntEquals(tc, expected, actual);
}

CuSuite *suite_ctrlArgs(void) {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test1_ctrlArgsAmount);
    SUITE_ADD_TEST(suite, test2_ctrlArgsAmount);
    return suite;
}