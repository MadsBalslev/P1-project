#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calendar.h"
#include "../modules/parser.h"

int main(void) {

    parse_file("test.ics");

    return EXIT_SUCCESS;
}