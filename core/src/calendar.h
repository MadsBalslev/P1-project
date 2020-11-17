typedef struct tm tm;

typedef struct event {
    char name[40];
    char description[280];
    tm startTime; /* burde være tm */
    tm endTime;   /* burde være tm */
    char tags[100][5];
} event;