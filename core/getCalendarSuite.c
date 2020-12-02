#include "header.h"

int getCalendarSuiteGetLocation(int argc, char *argv[], calendar *calendarSuite[]) {
    int i = 1;
    int k = 0;
    int validFileLocation = 0;

    do {
        if (isIcsFile(argv[i])) {
            validFileLocation = getCalendarSuiteGetLocationSingle(argv[i], calendarSuite[k]);
            k++;
        }
        i++;
    } while (i < argc && validFileLocation);

    return validFileLocation;
}

int getCalendarSuiteGetLocationSingle(char arg[], calendar *calendar) {
    int validFileLocation = 0;

    calendar->file = fopen(arg, "r");
    strcpy(calendar->fileName, arg);

    if (calendar->file == NULL) {
        validFileLocation = 0;
    } else {
        validFileLocation = 1;
    }

    return validFileLocation;
}

int getCalendarSuiteGetEvents(calendar *calendarSuite[]) {
    return 1;
}

/**
 * @brief Takes a char-pointer for the file path to the file, which will be parsed, 
 * and prints all calendar-events and the number of evetns
 * 
 * @param file_path 
 * @return int 
 */
int parse_file(char *file_path) {
    FILE *fp; /* Declare en pointer til en FILE */
    char input[LINE_LEN];
    int line = 0, isEvent, numOfEvents = 0;

    fp = fopen(file_path, "r"); /* Åbner den angivne fil i reading mode */
    if (fp == NULL)             /* Hvis filen ikke findes / eller ikke kan åbnes */
        return EXIT_FAILURE;

    while (fgets(input, LINE_LEN, fp)) {
        line++;

        if (strstr(input, "BEGIN:VEVENT")) { /* Find linjer hvor et event starter */
            isEvent = 1;
            numOfEvents++;
        }

        if (isEvent) {
            printf("%d: %s", line, input);
        }

        if (strstr(input, "END:VEVENT")) {
            isEvent = 0;
        }
    }

    printf("\n\n%d events in total\n\n", numOfEvents);

    fclose(fp); /* Luk filen igen */

    return EXIT_SUCCESS;
}
