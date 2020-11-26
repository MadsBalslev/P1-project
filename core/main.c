#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "calendar.h"
#include "parser.h"

void ctrlArgs(int argc, char *argv[]);
void ctrlArgsAmount(int argc);
void ctrlArgsIsFile(int argc, char *argv[]);
void ctrlArgsIsFileSA(char arg[]);
int isIcsFile(char arg[]);
void exitWithError(void);

void getSearchParameters(void);
void getCalenderSuite(void);
int findAvailableDatesByLooking(void);
void findAvailableDatesByRestructuring(void);
void userOutput(void);

int main(int argc, char *argv[]) {
    int foundDatesByLooking = 0;

    ctrlArgs(argc, argv);
    getSearchParameters();
    getCalenderSuite();
    foundDatesByLooking = findAvailableDatesByLooking();

    if (foundDatesByLooking) {
        findAvailableDatesByRestructuring();
    }

    userOutput();

    /* This should be abstracted further */
    /* Path relative from parser.o location */
    /* int parse_success = parse_file(filepath);
    if (parse_success == EXIT_FAILURE) {
        printf("Failed to parse file %s", filepath);
        return EXIT_FAILURE;
    } */

    return EXIT_SUCCESS;
}

/**
 * @brief Controls whether command-line arguments where valid.
 *  
 * Controls that the number of arguments (argc) gotten was over 1 and that the arguments where
 * in the format of *.ics. If this is not the case an error message is printed and the program
 * terminates. 
 *
 * @param argc number of arguments
 * @param argv arguments
 */
void ctrlArgs(int argc, char *argv[]) {
    ctrlArgsAmount(argc);
    ctrlArgsIsFile(argc, argv);
}

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

void getSearchParameters(void) {
}

void getCalenderSuite(void) {
}

int findAvailableDatesByLooking(void) {
    return 1;
}

void findAvailableDatesByRestructuring(void) {
}

void userOutput(void) {
}
