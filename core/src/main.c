#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../modules/calendar.h"
#include "../modules/parser.h"

int main(void) {
    
    int parse_success = parse_file("test.ics"); /* Path relative from parser.o location */
    if (parse_success == EXIT_FAILURE) {
        printf("Failed to parse file test.ics");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
