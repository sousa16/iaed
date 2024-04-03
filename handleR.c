/**
 * @file handleR.c
 * @author João Sousa
 * @brief file dedicated to the handleR function
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "proj1.h"
#include "handleR.h"

/**
 * @brief used to parse input for 'r' command
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
int rParser(char *input,
            ParkingLot parkingLots[20], int *numParkingLots,
            char *command, char *name) {
    int result = sscanf(input, " %c \"%[^\"]\"", command, name);

    // If the input doesn't have double quotes, retry with %s
    if (result == 1 || name[0] == '\0') {
        result = sscanf(input, " %c %s", command, name);
    }

    int parkIndexToRemove = -1;

    // Check if park exists and get its index
    for (int i = 0; i < *numParkingLots; i++) {
        if (strcmp(parkingLots[i].name, name) == 0) {
            parkIndexToRemove = i;
            break;
        }
    }

    if (parkIndexToRemove == -1) {
        printf("%s: no such parking.\n", name);
    }

    return parkIndexToRemove;
}

/**
 * @brief handle the user 'r' command (remove parking lot)
 *
 * @param input
 * @param parkingLots
 * @param numParkingLots
 * @param events
 * @param numEvents
 * @return EntryExitEvent**
 */
EntryExitEvent **handleR(char *input, ParkingLot parkingLots[MAX_PARKS],
                         int *numParkingLots, EntryExitEvent **events,
                         int *numEvents) {

    char command;
    char *name = NULL;

    // Allocate memory based on the length of the name in the input
    name = (char *)malloc((strlen(input) + 1) * sizeof(char));

    int parkIndexToRemove = rParser(input, parkingLots, numParkingLots,
                                    &command, name);

    // Remove park if park exists
    if (parkIndexToRemove != -1) {
        removeParkingLot(parkingLots, numParkingLots, events, numEvents,
                         name, parkIndexToRemove);

        // Print information about existing parking lots
        // after removing parking lot
        for (int i = 0; i < *numParkingLots; i++) {
            printf("%s\n", parkingLots[i].name);
        }
    }

    // Free memory dynamically allocated to name
    free(name);

    return events;
}
