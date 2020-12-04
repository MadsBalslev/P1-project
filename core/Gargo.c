/**
 * @brief 
 * 
 *
 * 
 *
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

/* TODO: This shit doesn't work */
/*void addEventCal(event *newEvent, calendar *inputCal) {
    int eventNum = 0;
    eventLink *nextEvent, *newEventLink;*/

/* inputcal.firstevent = newEventLink */

/*newEventLink->currentEvent = newEvent;
    newEventLink->nextEventLink = NULL;

    while (nextEvent->nextEventLink != NULL) {
        nextEvent = nextEvent->nextEventLink;

        eventNum++;
        printf("Going to next event %d\n", eventNum);
    }*/

/*nextEvent->nextEventLink = newEventLink;


    Algorithm to insert node at the end of a Singly Linked List
    Begin:
        createSinglyLinkedList (head)
        alloc (newNode)
        If (newNode == NULL) then
            write ('Unable to allocate memory')
        End if
        Else then
            read (data)
            newNode.data ← data
            newNode.next ← NULL
            temp ← head
            While (temp.next != NULL) do
                temp ← temp.next
            End while
            temp.next ← newNode
        End else
    End
}*/

/*eventLink */ void addEventCalAlt(event *newEvent, calendar *inputCal) {
    eventLink *newLink;
    eventLink *lastEvent = inputCal->firstEvent;

    newLink = (eventLink *)malloc(sizeof(eventLink)); /* Memory leak */
    newLink->currentEvent = newEvent;
    newLink->nextEventLink = (eventLink *)malloc(sizeof(eventLink));
    newLink->nextEventLink = NULL;

    printf("1: %d\n", newLink->nextEventLink);

    if (lastEvent == NULL) {
        lastEvent = newLink;
        return;
    }

    newLink->nextEventLink = inputCal->firstEvent;

    printf("2: %d\n", newLink->nextEventLink);
    while (lastEvent->nextEventLink != NULL) {
        lastEvent = lastEvent->nextEventLink;
    }

    printf("4: %d\n", newLink->nextEventLink);
    lastEvent->nextEventLink = newLink;

    /*return newLink;*/
    /*return newLink;*/

    /*eventLink *temp, *pos;

    pos = (eventLink *)malloc(sizeof(eventLink));

    temp = (eventLink *)malloc(sizeof(eventLink));
    temp->currentEvent = (event *)malloc(sizeof(event));
    temp->nextEventLink = (eventLink *)malloc(sizeof(eventLink));

    temp->currentEvent = newEvent;
    temp->nextEventLink = NULL;

    if (inputCal->firstEvent == NULL) {
        inputCal->firstEvent = temp;
        printf("Kalenderen er ikke længere tom, som mit liv <3\n");
    } else {
        pos = inputCal->firstEvent;

        while (pos != NULL) {
            pos = pos->nextEventLink;
        }

        pos->nextEventLink = (eventLink *)malloc(sizeof(eventLink));

        pos->nextEventLink = temp;*/

    /*
        temp = inputCal->firstEvent;
        printf("jeg kom her\n");

        
        
        
        while (temp->nextEventLink != NULL) {
            temp = temp->nextEventLink;
            printf("Going to next event\n");
        }
        */
}