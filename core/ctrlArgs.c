#include "header.h"

/**
 * @brief Controls if argc is under 2.
 *
 * @param argc number of arguments
 * @return 0 if argc is under, else 1
 */
int ctrlArgsAmount(int argc) {
    if (argc < 2) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief Controls that all of the command-line arguments are in the right format and valid
 *
 * @param argc number of arguments
 * @param argv arguments
 * @return 1 if all commandline arguments are valid, else 0 
 */
int ctrlArgsIsValidType(int argc, char *argv[]) {
    int i = 1;
    int argsValid;
    do {
        argsValid = argIsValid(argv[i]);
        i++;
    } while (i < argc && argsValid);
    return argsValid;
}

/**
 * @brief 
 * 
 * @param arg 
 * @return int 
 */
int argIsValid(char arg[]) {
    if (isIcsFile(arg)) {
        return 1;
    } else if (isOption(arg)) {
        return 1;
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
    if (strlen(arg) < 5) {
        return 0;
    } else {
        return (strncmp(&arg[strlen(arg) - 4], ".ics", 4) == 0);
    }
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 */
void doOptions(int argc, char *argv[]) {
    int i = 1;
    do {
        doOptionsSingle(argv[i]);
        i++;
    } while (i < argc);
}

/**
 * @brief 
 * 
 * @param arg 
 */
void doOptionsSingle(char arg[]) {
    if (strncmp(arg, "--test", 6) == 0) {
        runAllTests();
        exit(EXIT_SUCCESS);
    }
}

/**
 * @brief Displays error message and terminates the program.
 */
void exitWithError(void) {
    printf("Invalid argument, Please provide one or more .ics files\n");
    exit(EXIT_FAILURE);
}