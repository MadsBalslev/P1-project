#include "header.h"
extern int DEBUG;

/**
 * @brief Controls what a command line argument is considered, and executes options if command
 * line argument is an option. 
 *
 * @param arg argument to be controlled
 * @return enum icsFile if the argument is an *.ics file, enum option if the argument is an
 * option, else enum invalid. 
 */
int doArg(char arg[]) {
    if (isIcsFile(arg)) {
        return icsFile;
    } else if (isOption(arg)) {
        doOption(arg);
        return option;
    } else {
        return invalid;
    }
}

/**
 * @brief Controls if a string is considered an option from the command line.
 * 
 * @param arg string to be controlled
 * @return 1 if it is an option, else 0 
 */
int isOption(char arg[]) {
    if (!(strncmp(arg, "--", 2) == 0)) {
        return 0;
    } else if (strncmp(arg, "--test", 6) == 0) {
        return 1;
    } else if (strncmp(arg, "--debug", 7) == 0) {
        return 1;
    } else if (strncmp(arg, "--doNothing", 11) == 0) {
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
 * @brief Executes an option.
 * 
 * @param arg string of option to be executed
 */
void doOption(char arg[]) {
    if (strncmp(arg, "--test", 6) == 0) {
        runAllTests();
        exit(EXIT_SUCCESS);
    } else if (strncmp(arg, "--debug", 7) == 0) {
        DEBUG = 1;
    } else if (strncmp(arg, "--doNothing", 11) == 0) {
        /* do nothing */
    }
}

/**
 * @brief Displays error message and terminates the program.
 */
void exitWithError(void) {
    printf("Invalid argument, Please provide one or more .ics files\n");
    exit(EXIT_FAILURE);
}
