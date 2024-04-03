#include "proj1.h"
#include "aux.h"

// AUXILIARY FUNCTIONS

// Miscellaneous functions

/**
 * @brief Round a float's decimals to two digits
 *
 * @param num
 * @return float
 */
float roundToTwoDecimals(float num) {
    return (float)((int)(num * 100 + 0.5)) / 100;
}

/**
 * @brief Custom bubble sort function for sorting array of strings
 *
 * @param strings
 * @param numStrings
 */
void bubbleSort(char **strings, int numStrings) {
    for (int i = 0; i < numStrings - 1; i++) {
        for (int j = 0; j < numStrings - i - 1; j++) {
            // Compare current and next strings
            if (strcmp(strings[j], strings[j + 1]) > 0) {
                // Swap strings
                char *temp = strings[j];
                strings[j] = strings[j + 1];
                strings[j + 1] = temp;
            }
        }
    }
}

// Date and Time related functions

/**
 * @brief return number of days of a given month
 *
 * @param month
 * @return int
 */
int daysInMonth(int month) {
    switch (month) {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return 28;
    default:
        return 31;
    }
}

/**
 * @brief return number of days of a given year
 *
 * @param year
 * @return int
 */
int daysInYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        // Leap year
        return 366;
    else
        return 365;
}

/**
 * @brief split a date string into year, month and day ints
 *
 * @param date_str
 * @param day
 * @param month
 * @param year
 */
void extractDateComponents(const char *date_str, int *day,
                           int *month, int *year) {

    // Make a copy because strtok modifies the string
    char *date_copy = strdup(date_str);
    char *token = strtok(date_copy, "-");
    *day = atoi(token);

    token = strtok(NULL, "-");
    *month = atoi(token);

    token = strtok(NULL, "-");
    *year = atoi(token);

    // Free the allocated memory
    free(date_copy);
}

/**
 * @brief split a time string into hour and minute ints
 *
 * @param time_str
 * @param hour
 * @param minute
 */
void extractTimeComponents(const char *time_str, int *hour, int *minute) {

    // Make a copy because strtok modifies the string
    char *time_copy = strdup(time_str);
    char *token;
    token = strtok(time_copy, ":");
    *hour = atoi(token);

    token = strtok(NULL, ":");
    *minute = atoi(token);

    // Free the allocated memory
    free(time_copy);
}

/**
 * @brief compare 2 dates
 *
 * @param date1
 * @param date2
 * @return int
 */
int compareDate(const char *date1, const char *date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1, "%2d-%2d-%4d", &day1, &month1, &year1);
    sscanf(date2, "%2d-%2d-%4d", &day2, &month2, &year2);

    if (year1 < year2 || (year1 == year2 &&
                          (month1 < month2 ||
                           (month1 == month2 && (day1 < day2))))) {
        // date1 is before date2
        return -1;
    } else if (year1 == year2 && month1 == month2 && day1 == day2) {
        // date1 is equal to date2
        return 0;
    } else {
        // date1 is after date2
        return 1;
    }
}

/**
 * @brief compare 2 times
 *
 * @param time1
 * @param time2
 * @return int
 */
int compareTime(const char *time1, const char *time2) {
    int hour1, minute1;
    int hour2, minute2;

    sscanf(time1, "%2d:%2d", &hour1, &minute1);
    sscanf(time2, "%2d:%2d", &hour2, &minute2);

    if (hour1 < hour2 || (hour1 == hour2 && minute1 < minute2)) {
        // time1 is before time2
        return -1;
    } else if (hour1 == hour2 && minute1 == minute2) {
        // time1 is equal to time2
        return 0;
    } else {
        // time1 is after time2
        return 1;
    }
}

/**
 * @brief compare 2 date-time entries
 *
 * @param date1
 * @param time1
 * @param date2
 * @param time2
 * @return int
 */
int compareDateTime(const char *date1, const char *time1,
                    const char *date2, const char *time2) {
    int dateComparison = compareDate(date1, date2);

    if (dateComparison != 0) {
        // Return result of date comparison if dates are not equal
        return dateComparison;
    }

    // Dates are equal, so return time comparison
    return compareTime(time1, time2);
}

/**
 * @brief check if given date is valid
 *
 * @param date
 * @return int
 */
int isValidDate(const char *date) {
    int day, month, year;
    if (sscanf(date, "%2d-%2d-%4d", &day, &month, &year) == 3) {
        // Validate day, month, and year
        if (year >= 0 && month >= 1 && month <= 12) {
            // Validate day based on the month
            if (day >= 1 && day <= daysInMonth(month)) {
                // Valid date
                return 1;
            }
        }
    }

    // Invalid date
    return 0;
}

/**
 * @brief check if given date is valid for f command (valid date +
 * + cant be after date of latest event)
 *
 * @param date
 * @param events
 * @return int
 */
int isValidFDate(const char *date, EntryExitEvent **events, int numEvents) {
    return (isValidDate(date) &&
            compareDate(date, events[numEvents - 1]->date) <= 0);
}

/**
 * @brief check if given time is valid
 *
 * @param hour
 * @return int
 */
int isValidTime(const char *hour) {
    int hours, minute;
    if (sscanf(hour, "%2d:%2d", &hours, &minute) == 2) {
        // Validate hour and minute according to your requirements
        if (hours >= 0 && hours <= 23 && minute >= 0 && minute <= 59) {
            // Valid Date
            return 1;
        }
    }

    // Invalid time
    return 0;
}

/**
 * @brief check if given date-time entry is valid
 *
 * @param date
 * @param hour
 * @param lastEntry
 * @return int
 */
int isValidDateTime(const char *date, const char *hour,
                    EntryExitEvent *lastEntry) {
    if (isValidTime(hour) && isValidDate(date)) {
        // If both time and date are valid,
        // check if they are after last event
        if (lastEntry == NULL ||
            (compareDateTime(date, hour,
                             lastEntry->date, lastEntry->time) >= 0)) {
            // Valid date-time
            return 1;
        }
    }

    // Invalid date-time
    return 0;
}

/**
 * @brief function to check if an exit date-time is valid
 *
 * @param plate
 * @param date
 * @param hour
 * @param events
 * @param numEvents
 * @return int
 */
int isValidExitDateTime(const char *plate,
                        const char *date, const char *hour,
                        EntryExitEvent **events, int numEvents) {
    int numResults;

    // Get entries and exits for the specified license plate
    EntryExitEvent *results =
        getVehiclesEntriesAndExits(plate, events, numEvents, &numResults);

    if (results != NULL && numResults > 0) {
        // Get the last element of vehicle's entries and exits array
        EntryExitEvent vehicleLastEvent = results[numResults - 1];

        // Get the last event (of any vehicle)
        EntryExitEvent *lastEvent = getLastEntry(events, numEvents);

        // Check if the vehicle's last event is an entry and
        // is after last event
        if (vehicleLastEvent.isEntry == 1 &&
            isValidDateTime(date, hour, lastEvent)) {
            // Check if exit date-time is after vehicle's last event
            if ((compareDate(date, vehicleLastEvent.date) == 1) ||
                (compareDate(date, vehicleLastEvent.date) == 0 &&
                 compareTime(hour, vehicleLastEvent.time) >= 0)) {
                // Valid exit date-time, free allocated mem and return 1
                free(results);
                return 1;
            }
        }
    }

    // Invalid exit date-time, free allocated mem and return 0
    free(results);
    return 0;
}

// Parking Lot and Vehicle related functions

/**
 * @brief check if given parking name exists
 *
 * @param parkingLots
 * @param numParkingLots
 * @param name
 * @return int
 */
int parkingExists(const ParkingLot *parkingLots, int numParkingLots,
                  const char *name) {
    for (int i = 0; i < numParkingLots; i++) {
        if (strcmp(parkingLots[i].name, name) == 0) {
            // Parking name already exists
            return 1;
        }
    }

    // Parking name does not exist
    return 0;
}

/**
 * @brief get a ParkingLot by its name
 *
 * @param parkingLots
 * @param numParkingLots
 * @param name
 * @return ParkingLot*
 */
ParkingLot *getParkingLotByName(ParkingLot *parkingLots, int numParkingLots,
                                const char *name) {
    for (int i = 0; i < numParkingLots; i++) {
        if (strcmp(parkingLots[i].name, name) == 0) {
            // Return a pointer to the found ParkingLot
            return &parkingLots[i];
        }
    }

    // ParkingLot with the specified name not found
    return NULL;
}

/**
 * @brief check if given license plate is valid
 *
 * @param plate
 * @return int
 */
int isValidLicensePlate(const char *plate) {
    // Count letter blocks, digit blocks
    // Flag to see if character before is a letter (1 if yes, 0 if no)
    // Flag to see if character before is a digit (1 if yes, 0 if no)
    int letterCount = 0, digitCount = 0, isLetterBlock = 0, isDigitBlock = 0;

    // Check if plate has correct length
    if (strlen(plate) != PLATE_LEN)
        return 0;

    // Iterate through each character in the license plate to check its validity
    for (int i = 0; i < PLATE_LEN; i++) {
        // Check if character is a letter, digit or '-'
        if (isupper(plate[i])) {
            // Finishes a letter block, +1 to letterCount and reset flag
            if (isLetterBlock)
                letterCount++, isLetterBlock = 0;

            // Invalid, can't have a letter and digit in same block
            else if (isDigitBlock)
                return 0;

            // Starts a letter block
            else
                isLetterBlock = 1;

        } else if (isdigit(plate[i])) {
            // Finishes a digit block, +1 to digitCount and reset flag
            if (isDigitBlock)
                digitCount++, isDigitBlock = 0;

            // Invalid, can't have a letter and digit in same block
            else if (isLetterBlock)
                return 0;

            // Starts a digit block
            else
                isDigitBlock = 1;

        } else if (plate[i] == '-' && (i != 2 && i != 5)) {
            // Check if '-' is in valid position
            return 0;
        }
    }
    return (letterCount > 0 && letterCount + digitCount == 3)   // altered to allow 3 pairs of letters
               ? 1  // valid license plate
               : 0; // invalid license plate
}

/**
 * @brief add given plate a parkingLots' plates array
 *
 * @param parkingLot
 * @param plate
 */
void addPlateToLot(ParkingLot *parkingLot, const char *plate) {
    // Allocate memory for the new plate
    char *newPlate = strdup(plate);

    // Check for successful memory allocation
    if (newPlate == NULL) {
        // Handle memory allocation failure
        // For simplicity, we print an error message and return
        printf("Error: Failed to allocate memory for the plate.\n");
        return;
    }

    // Resize the plates array
    char **temp = realloc(parkingLot->plates,
                          (parkingLot->numPlates + 1) * sizeof(char *));

    // Check for successful memory allocation
    if (temp == NULL) {
        // Handle memory reallocation failure
        printf("Error: Failed to realloc memory for plates array.\n");
        free(newPlate);
        return;
    }
    parkingLot->plates = temp;

    // Add the new plate to the array
    parkingLot->plates[parkingLot->numPlates++] = newPlate;

    // Decrement availableSpots
    if (parkingLot->availableSpots > 0) {
        parkingLot->availableSpots--;
    }

}

/**
 * @brief remove given plate from a parkingLots' plates array
 *
 * @param parkingLot
 * @param plate
 */
void removePlateFromLot(ParkingLot *parkingLot, const char *plate) {
    // Find the plate in the plates array
    for (int i = 0; i < parkingLot->numPlates; ++i) {
        if (strcmp(parkingLot->plates[i], plate) == 0) {
            // Plate found, free its memory
            free(parkingLot->plates[i]);

            // Shift remaining plates to fill the gap
            for (int j = i; j < parkingLot->numPlates - 1; ++j) {
                // Assign the value of the next plate to the current plate
                parkingLot->plates[j] = parkingLot->plates[j + 1];
            }

            // Resize the plates array
            parkingLot->plates =
                realloc(parkingLot->plates,
                        (parkingLot->numPlates - 1) * sizeof(char *));

            // Check for successful array resizing
            if (parkingLot->plates == NULL && parkingLot->numPlates > 1) {
                // Handle memory reallocation failure
                printf("Error: Failed to realloc memory for plates array.\n");
                return;
            }

            // Update the number of plates
            parkingLot->numPlates--;

            // Increment availableSpots
            if (parkingLot->availableSpots < parkingLot->capacity) {
                parkingLot->availableSpots++;
            }

            // Exit the function after removing the plate
            return;
        }
    }

    // Plate not found
    printf("Error: License plate not found in the parking lot.\n");
}

/**
 * @brief function to free the memory allocated for the license plates array
 *
 * @param parkingLot
 */
void freePlatesArray(ParkingLot *parkingLot) {
    for (int i = 0; i < parkingLot->numPlates; i++) {
        free(parkingLot->plates[i]);
    }
    free(parkingLot->plates);
}

/**
 * @brief check if given plate is in any park
 *
 * @param plate
 * @param parkingLots
 * @param numParkingLots
 * @return int
 */
int isVehicleInAnyPark(const char *plate,
                       ParkingLot *parkingLots, int numParkingLots) {

    // Iterate through all parking lots
    for (int i = 0; i < numParkingLots; i++) {
        // Check if the given plate is in the current parking lot
        if (isVehicleInPark(plate, parkingLots[i].name,
                            parkingLots, numParkingLots)) {
            // Plate is in current park
            return 1;
        }
    }

    // Plate is not in any park
    return 0;
}

/**
 * @brief check if given plate is in given parkingLot
 *
 * @param plate
 * @param name
 * @param parkingLots
 * @param numParkingLots
 * @return int
 */
int isVehicleInPark(const char *plate, const char *name,
                    ParkingLot *parkingLots, int numParkingLots) {
    // Get parkingLot
    ParkingLot *parkingLot =
        getParkingLotByName(parkingLots, numParkingLots, name);

    // Check if given park exists
    if (parkingLot != NULL) {
        // Check if the given plate is in the list of plates for the given park
        for (int i = 0; i < parkingLot->numPlates; i++) {
            if (strcmp(parkingLot->plates[i], plate) == 0) {
                // Plate is in the specified park
                return 1;
            }
        }
    }

    // Plate is not in the specified park or the park doesn't exist
    return 0;
}

/**
 * @brief remove a parking lot and all its associated events
 *
 * @param parkingLots
 * @param numParkingLots
 * @param events
 * @param numEvents
 * @param name
 * @param parkIndexToRemove
 */
void removeParkingLot(ParkingLot *parkingLots, int *numParkingLots,
                      EntryExitEvent **events, int *numEvents,
                      char *name, int parkIndexToRemove) {

    // Remove all events associated with the parking lot
    for (int i = 0; i < *numEvents;) {
        if (strcmp(events[i]->parkingLotName, name) == 0) {
            // Free memory for the event
            free(events[i]->date);
            free(events[i]->time);
            free(events[i]->licensePlate);
            free(events[i]->parkingLotName);
            free(events[i]);
            
            // Remove this event by shifting the subsequent events
            for (int j = i; j < *numEvents - 1; j++) {
                events[j] = events[j + 1];
            }
            (*numEvents)--;
        } else {
            i++;
        }
    }


    // Free memory for the parking lot's plates array
    freePlatesArray(&parkingLots[parkIndexToRemove]);
    
    // Free memory for the parking lot being removed
    free(parkingLots[parkIndexToRemove].name);

    // Shift remaining parking lots to fill the gap
    for (int i = parkIndexToRemove; i < *numParkingLots - 1; i++) {
        parkingLots[i] = parkingLots[i + 1];
    }

    (*numParkingLots)--;
}

// Event (Entry and Exit) related functions

/**
 * @brief function to print all events
 *
 * @param events
 * @param numEvents
 */
void printAllEvents(EntryExitEvent **events, int numEvents) {
    for (int i = 0; i < numEvents; i++) {
        if (events[i] != NULL) {
            printf("Event %d :\n", i + 1);
            printf("  License Plate : %s\n", events[i]->licensePlate);
            printf("  Parking Lot Name : %s\n", events[i]->parkingLotName);
            printf("  Date : %s\n", events[i]->date);
            printf("  Time : %s\n", events[i]->time);
            printf("  Is Entry : %d\n", events[i]->isEntry);
        }
    }
}

/**
 * @brief function to compare EntryExitEvent structures for bubble sorting
 *
 * @param a
 * @param b
 * @return int
 */
int compareEvents(const EntryExitEvent *a, const EntryExitEvent *b) {
    return strcmp(a->parkingLotName, b->parkingLotName);
}

/**
 * @brief function to create an entry/exit event
 *
 * @param events
 * @param numEvents
 * @param date
 * @param time
 * @param licensePlate
 * @param parkingLotName
 * @param isEntry
 * @return EntryExitEvent**
 */
EntryExitEvent **logEntryExitEvent(EntryExitEvent **events, int *numEvents,
                                   const char *date, const char *time,
                                   const char *licensePlate,
                                   const char *parkingLotName, int isEntry) {

    // Create new EntryExitEvent
    EntryExitEvent *event = (EntryExitEvent *)malloc(sizeof(EntryExitEvent));

    event->date = strdup(date);
    event->time = strdup(time);
    event->licensePlate = strdup(licensePlate);
    event->parkingLotName = strdup(parkingLotName);
    event->isEntry = isEntry;

    // Resize the array and add the new event
    events =
        (EntryExitEvent **)realloc(events,
                                   (*numEvents + 1) * sizeof(EntryExitEvent *));

    events[*numEvents] = event;
    (*numEvents)++;

    return events;
}

/**
 * @brief get the given vehicle's entries and exits
 *
 * @param plate
 * @param events
 * @param numEvents
 * @param numResults
 * @return EntryExitEvent*
 */
EntryExitEvent *getVehiclesEntriesAndExits(const char *plate,
                                           EntryExitEvent **events,
                                           int numEvents, int *numResults) {

    // Count the number of events of given vehicle
    int count = 0;
    for (int i = 0; i < numEvents; i++) {
        if (strcmp(events[i]->licensePlate, plate) == 0) {
            count++;
        }
    }

    // Allocate memory for the results
    EntryExitEvent *results = malloc(count * sizeof(EntryExitEvent));
    if (results == NULL) {
        // Handle memory allocation failure
        *numResults = 0;
        return NULL;
    }

    // Copy events of given vehicle to the results array
    int index = 0;
    for (int i = 0; i < numEvents; i++) {
        if (strcmp(events[i]->licensePlate, plate) == 0) {
            results[index++] = *events[i];
        }
    }

    *numResults = count;
    return results;
}

/**
 * @brief get the last entry in the 'events' array
 *
 * @param events
 * @param numEvents
 * @return EntryExitEvent*
 */
EntryExitEvent *getLastEntry(EntryExitEvent **events, int numEvents) {
    EntryExitEvent *lastEntry = NULL;

    if (events != NULL) {
        // Iterate through events from end to start
        for (int i = numEvents - 1; i >= 0; i--) {
            if (events[i]->isEntry == 1) {
                // If it is entry, return it
                lastEntry = events[i];
                break;
            }
        }
    }
    return lastEntry;
}

/**
 * @brief find an exit's corresponding entry index in the 'events' array
 *
 * @param exitIndex
 * @param events
 * @return int
 */
int findCorrespondingEntryIndex(int exitIndex, EntryExitEvent **events) {
    for (int i = exitIndex - 1; i >= 0; i--) {
        // If event is entry and plate matches, return 1
        if (events[i]->isEntry == 1 &&
            strcmp(events[i]->licensePlate,
                   events[exitIndex]->licensePlate) == 0) {
            return i;
        }
    }
    // No corresponding entry found
    return -1;
}

/**
 * @brief find and print entry and exit information of an exit
 *
 * @param park
 * @param events
 * @param numEvents
 * @param numResults
 * @param plate
 * @param date
 * @param hour
 */
void findCorrespondingEntry(ParkingLot *park, EntryExitEvent **events,
                            int *numEvents, int numResults, char *plate,
                            char *date, char *hour) {
    // Find the last entry for the given plate
    EntryExitEvent *results =
        getVehiclesEntriesAndExits(plate, events,
                                   *numEvents, &numResults);
    EntryExitEvent *lastEntry = NULL;

    if (results != NULL && numResults > 0) {
        // Assign the address of the last entry,
        // skipping the exit that's being registereed
        lastEntry = &results[numResults - 2];
    }

    // Check if lastEntry is not NULL before accessing its members
    if (lastEntry != NULL) {
        const char *entryDate = lastEntry->date, *entryHour = lastEntry->time;

        float amountPaid = getAmountPaid(park, entryDate, entryHour,
                                         date, hour);

        // Extract time components for entry hour
        int entryHourValue, entryMinuteValue, hourValue, minuteValue;
        extractTimeComponents(entryHour, &entryHourValue, &entryMinuteValue);

        // Extract time components for current hour
        extractTimeComponents(hour, &hourValue, &minuteValue);

        // Print formatted output
        printf("%s %s %02d:%02d %s %02d:%02d %.2f\n", plate, entryDate,
               entryHourValue, entryMinuteValue, date, hourValue,
               minuteValue, amountPaid);
    }

    free(results);
}

/**
 * @brief findCorrespondingExit() aux funct to handle case -> exit found
 *
 * @param results
 * @param numResults
 * @param i
 * @param j
 * @param numStrings
 * @param entryExitStrings
 */
void handleFoundExit(EntryExitEvent *results, int i, int j,
                     int *numStrings, char **entryExitStrings) {
    // Extract time components
    int entryHour, entryMinute, exitHour, exitMinute;
    extractTimeComponents(results[i].time, &entryHour,
                          &entryMinute);
    extractTimeComponents(results[j].time, &exitHour,
                          &exitMinute);

    // Add entry and exit information string to string list
    char *entryExitString = malloc(100 * sizeof(char));
    sprintf(entryExitString, "%s %s %02d:%02d %s %02d:%02d",
            results[i].parkingLotName, results[i].date,
            entryHour, entryMinute, results[j].date,
            exitHour, exitMinute);
    entryExitStrings[(*numStrings)++] = entryExitString;
}

/**
 * @brief findCorrespondingExit() aux funct to handle case -> exit not found
 *
 * @param results
 * @param numResults
 * @param i
 * @param numStrings
 * @param entryExitStrings
 */
void handleNotFoundExit(EntryExitEvent *results, int i, int *numStrings,
                        char **entryExitStrings) {
    int entryHour, entryMinute;
    extractTimeComponents(results[i].time, &entryHour,
                          &entryMinute);

    char *entryExitString = malloc(100 * sizeof(char));
    sprintf(entryExitString, "%s %s %02d:%02d",
            results[i].parkingLotName, results[i].date,
            entryHour, entryMinute);
    entryExitStrings[(*numStrings)++] = entryExitString;
}

/**
 * @brief find an entry's corresponding exit and update entryExitStrings array
 *
 * @param results
 * @param numResults
 * @param i
 * @param numStrings
 * @param entryExitStrings
 */
void findCorrespondingExit(EntryExitEvent *results, int numResults, int i,
                           int *numStrings, char **entryExitStrings) {
    int foundExit = 0;
    for (int j = i + 1; j < numResults; j++) {
        if (strcmp(results[i].licensePlate,
                   results[j].licensePlate) == 0 &&
            results[j].isEntry == 0) {
            handleFoundExit(results, i, j, numStrings, entryExitStrings);
            foundExit = 1;
            break;
        }
    }

    if (!foundExit) {
        // No corresponding exit found
        handleNotFoundExit(results, i, numStrings, entryExitStrings);
    }
}

/**
 * @brief print sorted vehicle events according to project's sorting rules
 *
 * @param results
 * @param numResults
 */
void printSortedVehicleEvents(EntryExitEvent *results, int numResults) {
    // Create an array to store the formatted entry and exit information
    char *entryExitStrings[numResults];
    int numStrings = 0;

    // Traverse through results array and format entry and exit information
    for (int i = 0; i < numResults && numStrings < numResults; i++) {
        if (results[i].isEntry == 1) {
            findCorrespondingExit(results, numResults, i, &numStrings,
                                  entryExitStrings);
        }
    }

    // Sort the array of strings by park name using bubble sort
    bubbleSort(entryExitStrings, numStrings);

    // Print the sorted entry and exit information
    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", entryExitStrings[i]);
        free(entryExitStrings[i]); // Free memory for each string
    }

    // free entryExitStrings
}

// Billing related functions

/**
 * @brief get amount paid for given entry and exit
 *
 * @param park
 * @param entryDate
 * @param entryHour
 * @param exitDate
 * @param exitHour
 * @return float
 */
float getAmountPaid(ParkingLot *park, const char *entryDate,
                    const char *entryHour, const char *exitDate,
                    const char *exitHour) {

    // Assume entryDate and entryHour are valid and
    // earlier than or equal to exitDate and exitHour
    // This is validated in other functions

    int day1, month1, year1, hour1, min1, day2, month2, year2, hour2, min2;

    int daysInThisMonth, entryDayMinutes, exitDayMinutes;
    int fullDays = 0;
    int fifteenMinPeriods = 0;

    float fullDaysPrice, totalCost;

    // Extract components of entryDate
    extractDateComponents(entryDate, &day1, &month1, &year1);

    // Extract components of exitDate
    extractDateComponents(exitDate, &day2, &month2, &year2);

    // Extract components of entryHour
    extractTimeComponents(entryHour, &hour1, &min1);

    // Extract components of exitHour
    extractTimeComponents(exitHour, &hour2, &min2);

    if (year1 != year2) {
        // Iterate through years between the two dates
        for (int year = year1 + 1; year < year2; year++) {
            fullDays += daysInYear(year);
        }

        // Add days for entry year
        for (int month = month1; month <= 12; month++) {
            daysInThisMonth = daysInMonth(month);
            if (month == month1)
                fullDays += daysInThisMonth - day1;
            else
                fullDays += daysInThisMonth;
        }

        // Add days for exit year
        for (int month = 1; month <= month2; month++) {
            daysInThisMonth = daysInMonth(month);
            if (month == month2)
                fullDays += day2 - 1;
            else
                fullDays += daysInThisMonth;
        }
        // Same year
    } else {
        // Different months
        if (month1 != month2) {
            for (int month = month1; month <= month2; month++) {
                daysInThisMonth = daysInMonth(month);

                // Add full days
                if (month == month1)
                    fullDays += daysInThisMonth - day1;
                else if (month == month2)
                    fullDays += day2 - 1;
                else
                    fullDays += daysInThisMonth;
            }
            // Same months
        } else {
            fullDays += day2 - day1 - 1;
        }
    }

    entryDayMinutes = 0;
    // Minutes passed since 00:00 until hour2:minute2
    exitDayMinutes = (hour2 * 60) + min2;

    // Check if entry and exit are in the same day
    if (compareDate(entryDate, exitDate) == 0) {
        // If they are, entryDayMinutes stays equal to 0
        // and exitDayMinutes equals exitDayMinutes minus
        // minutes passed since 00:00 until hour1:minute1
        exitDayMinutes -= ((hour1 * 60) + min1);
    } else {
        // If not, entryDayMinutes equals
        // minutes passed since hour1:minute1 until 00:00
        entryDayMinutes = ((24 - hour1 - 1) * 60 + (60 - min1));
    }

    int totalMinutes = entryDayMinutes + exitDayMinutes;

    if (totalMinutes >= 1440) {
        // Add the 24h periods to fullDays
        fullDays += totalMinutes / 1440;

        // Remove 24h periods from totalMinutes
        totalMinutes %= 1440;
    }

    // Calculate amount of fifteen minute periods
    if (totalMinutes % 15 == 0) {
        // If there is no remainder
        fifteenMinPeriods = totalMinutes / 15;
    } else {
        // If there is remainder, add another period
        fifteenMinPeriods = totalMinutes / 15 + 1;
    }

    // Calculate price of full days
    fullDaysPrice = 0.0;
    if (fullDays > 0) {
        fullDaysPrice = roundToTwoDecimals(park->maxDailyCost * fullDays);
    }

    // Calculate total cost
    if (fifteenMinPeriods <= 4) {
        // If there are 4 or less periods, their prices are all the same
        totalCost = (fifteenMinPeriods * park->cost15) + fullDaysPrice;
    } else {
        // If there are more than 4 periods, first 4 periods' prices equal
        // cost15, while the rest equal cost15After1Hour
        float fifteenMinPeriodsCost =
            4 * park->cost15 + (fifteenMinPeriods - 4) * park->cost15After1Hour;

        // Check if periods' cost is greater than max daily allowed cost
        // If it is, replace it by maxDailyCost
        if (fifteenMinPeriodsCost < park->maxDailyCost) {
            totalCost = fifteenMinPeriodsCost + fullDaysPrice;
        } else {
            totalCost = park->maxDailyCost + fullDaysPrice;
        }
    }
    return totalCost;
}

/**
 * @brief check if a day's billing is already in the dailyBillings' array
 *
 * @param dailyBillings
 * @param numDailyBillings
 * @param date
 * @return int
 */
int findDailyBillingIndex(DailyBilling *dailyBillings,
                          int numDailyBillings, const char *date) {
    for (int i = 0; i < numDailyBillings; i++) {
        if (strcmp(date, dailyBillings[i].date) == 0) {
            // Date found, return index
            return i;
        }
    }
    // Date not found
    return -1;
}

/**
 * @brief add (or update if it already exists) a billing to dailyBillings array
 *
 * @param dailyBillingsPtr
 * @param numDailyBillingsPtr
 * @param date
 * @param billing
 */
void updateOrAddBilling(DailyBilling **dailyBillingsPtr,
                        int *numDailyBillingsPtr,
                        const char *date, float billing) {
    int existingIndex =
        findDailyBillingIndex(*dailyBillingsPtr, *numDailyBillingsPtr, date);

    if (existingIndex != -1) {
        // Update billing for existing date
        (*dailyBillingsPtr)[existingIndex].totalBilling += billing;
    } else {
        // Add new entry for the date
        *dailyBillingsPtr =
            realloc(*dailyBillingsPtr,
                    (*numDailyBillingsPtr + 1) * sizeof(DailyBilling));
        (*dailyBillingsPtr)[*numDailyBillingsPtr].date = strdup(date);
        (*dailyBillingsPtr)[*numDailyBillingsPtr].totalBilling = billing;
        (*numDailyBillingsPtr)++;
    }
}

/**
 * @brief command for handleT
 * 
 * @param events 
 * @param numEvents 
 * @param name 
 * @param park 
 */
void printBillings(EntryExitEvent **events, int numEvents,
                         const char *name, ParkingLot *park) {
    // Create an array to store daily billings
    DailyBilling *dailyBillings = NULL;
    int numDailyBillings = 0;
    float totalBilling = 0.0;

    // Iterate through the exit events
    for (int i = 0; i < numEvents; i++) {
        // Check if the event is an exit and
        // if it belongs to the specified parking lot
        if (events[i]->isEntry == 0 &&
            strcmp(events[i]->parkingLotName, name) == 0) {
            int correspondingEntryIndex =
                findCorrespondingEntryIndex(i, events);

            // Calculate the billing using the getAmountPaid function
            float billing = getAmountPaid(park,
                                          events[correspondingEntryIndex]->date,
                                          events[correspondingEntryIndex]->time,
                                          events[i]->date, events[i]->time);

            // Update or add the billing for the date
            updateOrAddBilling(&dailyBillings, &numDailyBillings,
                               events[i]->date, billing);
        }
    }

    // Print the accumulated billing for each date
    for (int i = 0; i < numDailyBillings; i++) {
        totalBilling += dailyBillings[i].totalBilling;
    }

    printf("%.2f\n", totalBilling);

    // Free the allocated memory
    for (int i = 0; i < numDailyBillings; i++) {
        free(dailyBillings[i].date);
    }
    free(dailyBillings);
}

/**
 * @brief print a park's billings by date
 *
 * @param events
 * @param numEvents
 * @param name
 * @param park
 */
void printBillingsByDate(EntryExitEvent **events, int numEvents,
                         const char *name, ParkingLot *park) {
    // Create an array to store daily billings
    DailyBilling *dailyBillings = NULL;
    int numDailyBillings = 0;

    // Iterate through the exit events
    for (int i = 0; i < numEvents; i++) {
        // Check if the event is an exit and
        // if it belongs to the specified parking lot
        if (events[i]->isEntry == 0 &&
            strcmp(events[i]->parkingLotName, name) == 0) {
            int correspondingEntryIndex =
                findCorrespondingEntryIndex(i, events);

            // Calculate the billing using the getAmountPaid function
            float billing = getAmountPaid(park,
                                          events[correspondingEntryIndex]->date,
                                          events[correspondingEntryIndex]->time,
                                          events[i]->date, events[i]->time);

            // Update or add the billing for the date
            updateOrAddBilling(&dailyBillings, &numDailyBillings,
                               events[i]->date, billing);
        }
    }

    // Print the accumulated billing for each date
    for (int i = 0; i < numDailyBillings; i++) {
        printf("%s %.2f\n", dailyBillings[i].date,
               dailyBillings[i].totalBilling);
    }

    // Free the allocated memory
    for (int i = 0; i < numDailyBillings; i++) {
        free(dailyBillings[i].date);
    }
    free(dailyBillings);
}

/**
 * @brief print a park's billings of a specific date
 *
 * @param events
 * @param numEvents
 * @param name
 * @param park
 * @param date
 */
void printBillingsOfDate(EntryExitEvent **events, int numEvents,
                         const char *name, ParkingLot *park, const char *date) {
    // Iterate through the exit events
    for (int i = 0; i < numEvents; i++) {

        // Check if the event is an exit,
        // belongs to the specified parking lot,
        // and matches the specified date
        if (events[i]->isEntry == 0 &&
            strcmp(events[i]->parkingLotName, name) == 0 &&
            strcmp(events[i]->date, date) == 0) {
            int correspondingEntryIndex =
                findCorrespondingEntryIndex(i, events);

            // Calculate the billing
            float billing =
                getAmountPaid(park,
                              events[correspondingEntryIndex]->date,
                              events[correspondingEntryIndex]->time,
                              events[i]->date, events[i]->time);

            int hour, minute;
            extractTimeComponents(events[i]->time, &hour, &minute);

            // Print the individual billing information
            printf("%s %02d:%02d %.2f\n", events[i]->licensePlate,
                   hour, minute, billing);
        }
    }
}