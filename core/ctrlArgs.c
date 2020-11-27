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
 * @brief Controls that all of the command-line arguments are in the format *.ics.
 *
 * @param argc number of arguments
 * @param argv arguments
 * @return 1 if all commandline arguments are in the fornat *.ics, else 0 
 */
int ctrlArgsIsFile(int argc, char *argv[]) {
    int i = 1;
    int argsValid;
    do {
        argsValid = isIcsFile(argv[i]);
        i++;
    } while (i < argc && argsValid);
    return argsValid;
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
 * @brief Displays error message and terminates the program.
 */
void exitWithError(void) {
    printf("Invalid argument, Please provide one or more .ics files\n");
    exit(EXIT_FAILURE);
}