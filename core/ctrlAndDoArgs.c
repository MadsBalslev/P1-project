#include "header.h"

extern int DEBUG;

/**
 * @brief 
 * 
 * @param arg 
 * @return int 
 */
int doArg(char arg[]) {
    if (isIcsFile(arg)) {
        doIcsFile(arg);
        return icsFile;
    } else if (isOption(arg)) {
        doOption(arg);
        return option;
    } else {
        return 0;
    }
}

/**
 * @brief 
 * 
 * @param arg 
 * @return int 
 */
int isOption(char arg[]) {
    if (strncmp(arg, "--test", 6) == 0) {
        return 1;
    } else if (strncmp(arg, "--debug", 7) == 0) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Controls that a string ends with ".ics".
 * 
 * @param arg string to control
 * @return 1 if it does end with ".ics", else 0
 */
int isIcsFile(char arg[]) {
    if ((strlen(arg)) < 5) {
        return 0;
    } else {
        return (strncmp(&arg[strlen(arg) - 4], ".ics", 4) == 0);
    }
}

/**
 * @brief 
 * 
 * @param arg 
 */
void doOption(char arg[]) {
    if (strncmp(arg, "--test", 6) == 0) {
        runAllTests();
        exit(EXIT_SUCCESS);
    }
    if (strncmp(arg, "--debug", 7) == 0) {
        DEBUG = 1;
    }
}

/**
 * @brief Displays error message and terminates the program.
 */
void exitWithError(void) {
    printf("Invalid argument, Please provide one or more .ics files\n");
    exit(EXIT_FAILURE);
}

void doIcsFile(char arg[]) {
}
