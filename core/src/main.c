#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calendar.h"
#include "../modules/parser.h"

int main(void) {

    parse_file("test.ics"); /* Path relative from parser.o location */

    return EXIT_SUCCESS;
}
