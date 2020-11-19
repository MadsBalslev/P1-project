#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 512

int parse_file(char *file_path) {
  FILE *fp; /* Declare en pointer til en FILE */
  char input[LINE_LEN];
  int line = 0;

  fp = fopen(file_path, "r"); /* Åbner den angivne fil i reading mode */
  if (fp == NULL) /* Hvis filen ikke findes / eller ikke kan åbnes */
    return EXIT_FAILURE;

  while (fgets(input, LINE_LEN, fp)) {
    line++;

    if(strstr(input, "DTSTART")) { /* Find linjer hvor der er DTSTART */
      printf("%d: %s", line, input);
    }
  }

  printf("\n");

  fclose(fp); /* Luk filen igen */

  return EXIT_SUCCESS;
}
