#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tm tm;

typedef struct event {
  char eventName[42];
  char description[280];
  tm startTime;
  tm endTime;
  char tags [100][3];
} event;

int main(void) {
  return EXIT_SUCCESS;
}