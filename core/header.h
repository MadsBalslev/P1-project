void ctrlArgs(int argc, char *argv[]);
void ctrlArgsAmount(int argc);
void ctrlArgsIsFile(int argc, char *argv[]);
void ctrlArgsIsFileSA(char arg[]);
int isIcsFile(char arg[]);
void exitWithError(void);

void getSearchParameters(void);
int parse_file(char *);

void getCalendarSuite(void);
int findAvailableDatesByLooking(void);
void findAvailableDatesByRestructuring(void);
void userOutput(void);

