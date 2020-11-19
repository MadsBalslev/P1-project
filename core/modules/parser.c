#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 512

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
