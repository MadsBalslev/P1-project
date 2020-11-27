#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

/**
 * @brief Controls if argc is under 2, if this is the case the program if this is the case an
 * error message is printed and the program terminates.
 *
 * @param argc number of arguments
 */
void ctrlArgsAmount(int argc) {
    if (argc < 2) {
        exitWithError();
    }
}

/**
 * @brief Controls that all of the command-line arguments are in the format *.ics, if this is
 * not the case an error message is printed and the program terminates.
 *
 * @param argc number of arguments
 * @param argv arguments
 */
void ctrlArgsIsFile(int argc, char *argv[]) {
    int i = 1;
    while (i < argc) {
        ctrlArgsIsFileSA(argv[i]);
        i++;
    }
}

/**
 * @brief Controls that a string ends with ".ics", if this is not the case an error message is
 * printed and the program terminates.
 * 
 * @param arg string to control 
 */
void ctrlArgsIsFileSA(char arg[]) {
    if (!isIcsFile(arg)) {
        exitWithError();
    }
}

/**
 * @brief Controls that a string ends with ".ics".
 * 
 * @param argv string to control
 * @return 1 if arg is on the form *.ics, else 0 
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