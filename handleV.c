/**
 * @file handleV.c
 * @author João Sousa
 * @brief file dedicated to the handleV function
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "proj1.h"
#include "handleV.h"

/**
 * @brief parse input for 'v' command
 *
 * @param input
 * @param events
 * @param numEvents
 * @param command
 * @param name
 * @param plate
 * @return int
 */
int vParser(char *input, EntryExitEvent **events, int *numEvents,
            char *command, char *plate) {
    int numResults = 0;
    sscanf(input, " %c %s", command, plate);

    if (!(isValidLicensePlate(plate))) {
        printf("%s: invalid licence plate.\n", plate);
    } else if (getVehiclesEntriesAndExits(plate, events,
                                          *numEvents, &numResults) == NULL ||
               numResults == 0) {
        printf("%s: no entries found in any parking.\n", plate);
    } else {
        return 1;
    }
    return 0;
}

/**
 * @brief handle the 'v' user command (print vehicle activity)
 *
 * @param input
 * @param events
 * @param numEvents
 */
void handleV(char *input, EntryExitEvent **events, int *numEvents) {
    char command;
    char *plate = NULL;
    int numResults;

    // Allocate memory based on the length of parts of input
    plate = (char *)malloc((strlen(input) + 2) * sizeof(char));

    if (vParser(input, events, numEvents, &command, plate)) {
        EntryExitEvent *results =
            getVehiclesEntriesAndExits(plate, events, *numEvents, &numResults);

        printSortedVehicleEvents(results, numResults);

        free(results);
    }
    free(plate);
}
