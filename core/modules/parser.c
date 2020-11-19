#include <stdio.h>
#include <stdlib.h>

int parse_file(char *file_path) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  fp = fopen(file_path, "r"); /* Åbner den angivne fil i reading mode */
  if (fp == NULL) /* Hvis filen ikke findes / eller ikke kan åbnes */
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {
    printf("%s", line);
  }

  fclose(fp); /* Luk filen igen */
  if (line)
    free(line); /* Fjern linjer fra memory når vi er færdige */
  exit(EXIT_SUCCESS);
}