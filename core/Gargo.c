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

/* 1. Sammenflet alle overlappende events til ét samlet event */

tm *lookForFreeSlotAlt(event *allEvents[], int arrLen, searchParameters *p) {
    tm cursor, *freeSlot = NULL, *tempSlot;
    time_t unixCursor;
    int i;

    cursor.tm_year = p->startDate.tm_year;
    cursor.tm_mon = p->startDate.tm_mon;
    cursor.tm_mday = p->startDate.tm_mday;
    cursor.tm_hour = p->lowerLimit.tm_hour;
    cursor.tm_min = p->lowerLimit.tm_min;

    unixCursor = mktime(&cursor);

    for (i = 0; i < arrLen || allEvents[i] != NULL; i++) {
        time_t unixStart = mktime(&allEvents[i]->startTime);
        time_t unixEnd = mktime(&allEvents[i]->endTime);

        if (unixCursor > unixStart && unixCursor < unixEnd) {
            unixCursor = unixEnd;
            printf("New cursor: %ld\n", unixCursor);
        } else if (unixCursor < unixStart && unixStart - unixCursor >= ((p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC))) {
            if (withinScope(unixCursor, p)) {
                break;
            }
        } else if (unixCursor < unixStart && unixStart - unixCursor < ((p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC))) {
            unixCursor = unixEnd;
        }

        tempSlot = localtime(&unixCursor);
        printf("cursor was: %.2d/%.2d/%.4d %.2d:%.2d\n", tempSlot->tm_mday, tempSlot->tm_mon + 1, tempSlot->tm_year + 1900, tempSlot->tm_hour, tempSlot->tm_min);
    }

    unixCursor = unixCursor + (p->buffer * MIN_TO_SEC);

    freeSlot = localtime(&unixCursor);

    return freeSlot;
}

int withinScope(time_t unixCursor, const searchParameters *p) {
    tm *cursorStart;
    tm *cursorEnd;

    cursorStart = localtime(&unixCursor);
    cursorEnd = localtime(&unixCursor + (p->eventLen * MIN_TO_SEC) + (2 * p->buffer * MIN_TO_SEC));

    if ((cursorStart->tm_hour >= p->lowerLimit.tm_hour) && (cursorEnd->tm_hour <= p->upperLimit.tm_hour)) {
        return 1;
    } else {
        return 0;
    }
}

/*tm convertUnixTime(time_t inputUnix) {
    tm convertedTime;

    convertedTime = *localtime(inputUnix);

    return convertedTime;
}*/

/**
 * @brief Checks if an event begins before the event of previous event
 * 
 * @param event1 
 * @param event2 
 * @return int 
 */
/*int eventBeginBeforeEnd(time_t *event1, time_t *event2) {
    if (event2 <= event1) {
        return 1;
    } else {
        return 0;
    }
}*/

/*int tmCmp(tm t1, tm t2) {
    if (t1.tm_year > t2.tm_year) { 
        return 1;
    } else if (t1.tm_year < t2.tm_year) {
        return 0;
    } else if (t1.tm_mon > t2.tm_mon) { 
        return 1;
    } else if (t1.tm_year < t2.tm_year) {
        return 0;
    } else if (t1.tm_mday > t2.tm_mday) { 
        return 1;
    } else if (t1.tm_mday < t2.tm_mday) {
        return 0;
    } else if (t1.tm_hour > t2.tm_hour) { 
        return 1;
    } else if (t1.tm_hour < t2.tm_hour) {
        return 0;
    } else if (t1.tm_min > t2.tm_min) { 
        return 1;
    } else if (t1.tm_min < t2.tm_min) {
        return 0;
    } else if (t1.tm_sec > t2.tm_sec) { 
        return 1;
    } else {
        return 1;
    }
}*/

/* 2. Find ledig tid mellem sammenflettede events */

/* Hvis ikke det lykkedes at finde hultid uden i kalender med alle events:
   3. Fjern alle events med lavere prioritet end ønskede event */

/* 4. Sammenflet alle overlappende events til ét samlet event */

/* 5. Find ledig tid mellem sammenflettede events */

/* Output fund til bruger */