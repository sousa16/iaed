/**
 * @file handleE.c
 * @author João Sousa
 * @brief file dedicated to the handleE function
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "proj1.h"
#include "handleE.h"

/**
 * @brief used to parse input for e command
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
int eParser(char *input,
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

    // Catch errors in input
    if (!(parkingExists(parkingLots, *numParkingLots, name))) {
        printf("%s: no such parking.\n", name);
    } else if (getParkingLotByName(parkingLots, *numParkingLots, name)
                   ->availableSpots == 0) {
        printf("%s: parking is full.\n", name);
    } else if (!(isValidLicensePlate(plate))) {
        printf("%s: invalid licence plate.\n", plate);
    } else if ((isVehicleInAnyPark(plate, parkingLots, *numParkingLots))) {
        printf("%s: invalid vehicle entry.\n", plate);
    } else if (!(isValidDateTime(date, hour,
                                 getLastEntry(events, *numEvents)))) {
        printf("invalid date.\n");
    } else {
        return 1;
    }

    return 0;
}

/**
 * @brief handle the user 'e' command (vehicle entry)
 *
 * @param input
 * @param parkingLots
 * @param numParkingLots
 * @param events
 * @param numEvents
 * @return EntryExitEvent**
 */
EntryExitEvent **handleE(char *input, ParkingLot parkingLots[MAX_PARKS],
                         int *numParkingLots, EntryExitEvent **events,
                         int *numEvents) {

    char command;
    char *name = NULL, *plate = NULL, *date = NULL, *hour = NULL;

    // Allocate memory based on the length of parts of input
    name = (char *)malloc((strlen(input) + 1) * sizeof(char));
    plate = (char *)malloc((strlen(input) + 2) * sizeof(char));
    date = (char *)malloc((strlen(input) + 3) * sizeof(char));
    hour = (char *)malloc((strlen(input) + 4) * sizeof(char));

    // Call eParser to parse the input
    if (eParser(input, parkingLots, numParkingLots, events, numEvents,
                &command, name, plate, date, hour)) {
        ParkingLot *park = getParkingLotByName(parkingLots, *numParkingLots,
                                               name);

        // Register entry of the vehicle on the parking lots list
        addPlateToLot(park, plate);

        // Register entry on the entry/exit events
        events = logEntryExitEvent(events, numEvents, date, hour, plate,
                                   name, 1);

        printf("%s %d\n", park->name, park->availableSpots);
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
