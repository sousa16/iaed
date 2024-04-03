/**
 * @file handleS.c
 * @author João Sousa
 * @brief file dedicated to the handleS function
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "proj1.h"
#include "handleS.h"

/**
 * @brief parse input for 's' command
 *
 * @param input
 * @param parkingLots
 * @param numParkingLots
 * @param events
 * @param numEvents
 * @param command
 * @param name
 * @param plate
 * @param date
 * @param hour
 * @return int
 */
int sParser(char *input,
            ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
            EntryExitEvent **events, int *numEvents,
            char *command, char *name, char *plate,
            char *date, char *hour) {
    int result = sscanf(input, " %c \"%[^\"]\" %s %s %s",
                        command, name, plate, date, hour);

    // If the input doesn't have double quotes, retry with %s
    if (result == 1 || name[0] == '\0') {
        result = sscanf(input, " %c %s %s %s %s",
                        command, name, plate, date, hour);
    }

    if (!(parkingExists(parkingLots, *numParkingLots, name))) {
        printf("%s: no such parking.\n", name);
    } else if (!(isValidLicensePlate(plate))) {
        printf("%s: invalid licence plate.\n", plate);
    } else if (!(isVehicleInPark(plate, name, parkingLots, *numParkingLots))) {
        printf("%s: invalid vehicle exit.\n", plate);
    } else if (!(isValidExitDateTime(plate, date, hour, events, *numEvents))) {
        printf("invalid date.\n");
    } else {
        return 1;
    }
    return 0;
}

/**
 * @brief handle the user 's' command (vehicle exit)
 *
 * @param input
 * @param parkingLots
 * @param numParkingLots
 * @param events
 * @param numEvents
 * @return EntryExitEvent**
 */
EntryExitEvent **handleS(char *input, ParkingLot parkingLots[MAX_PARKS],
                         int *numParkingLots, EntryExitEvent **events,
                         int *numEvents) {
    char command;
    char *name = NULL, *plate = NULL, *date = NULL, *hour = NULL;

    // Allocate memory based on the length of parts of input
    name = (char *)malloc((strlen(input) + 1) * sizeof(char));
    plate = (char *)malloc((strlen(input) + 2) * sizeof(char));
    date = (char *)malloc((strlen(input) + 3) * sizeof(char));
    hour = (char *)malloc((strlen(input) + 4) * sizeof(char));

    // Call sParser to parse the input
    if (sParser(input, parkingLots, numParkingLots, events, numEvents,
                &command, name, plate, date, hour)) {
        int numResults = 0;

        ParkingLot *park =
            getParkingLotByName(parkingLots, *numParkingLots, name);

        // Register exit of the vehicle on the parking lots list
        removePlateFromLot(park, plate);

        // Register exit on the entry/exit events
        events = logEntryExitEvent(events, numEvents, date, hour,
                                   plate, name, 0);
        findCorrespondingEntry(park, events, numEvents, numResults, plate,
                               date, hour);
    }
    // Free allocated memory
    if (name)
        free(name);
    if (plate)
        free(plate);
    if (date)
        free(date);
    if (hour)
        free(hour);

    return events;
}