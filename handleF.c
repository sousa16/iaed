/**
 * @file handleF.c
 * @author João Sousa
 * @brief file dedicated to the handleF function
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "proj1.h"
#include "handleF.h"

/**
 * @brief used to parse input for f command
 *
 * @param input
 * @param parkingLots
 * @param numParkingLots
 * @param events
 * @param numEvents
 * @param command
 * @param name
 * @param date
 * @return int
 */
int fParser(char *input,
            EntryExitEvent **events, int numEvents,
            ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
            char *command, char *name, char *date) {
    int result = sscanf(input, " %c \"%[^\"]\" %s",
                        command, name, date);

    // If the input doesn't have double quotes, retry with %s
    if (result == 1 || name[0] == '\0') {
        result = sscanf(input, " %c %s %s",
                        command, name, date);
    }

    if (result >= 2 && *command == 'f') {
        if (!(parkingExists(parkingLots, *numParkingLots, name))) {
            printf("%s: no such parking.\n", name);
        } else if (result == 3 && (!(isValidFDate(date, events, numEvents)))) {
            printf("invalid date.\n");
        } else {
            return result;
        }
    }

    return 0;
}

/**
 * @brief handle the 'f' user command (print park billing)
 *
 * @param input
 * @param parkingLots
 * @param numParkingLots
 * @param events
 * @param numEvents
 */
void handleF(char *input, ParkingLot parkingLots[MAX_PARKS],
             int *numParkingLots, EntryExitEvent **events, int *numEvents) {
    char command;
    char *name = NULL, *date = NULL;

    // Allocate memory based on the length of the name in the input
    name = (char *)malloc((strlen(input) + 1) * sizeof(char));
    date = (char *)malloc((strlen(input) + 2) * sizeof(char));

    int result = fParser(input, events, *numEvents, parkingLots, numParkingLots,
                         &command, name, date);

    ParkingLot *park =
        getParkingLotByName(parkingLots, *numParkingLots, name);

    if (result == 2) {
        // Case: "f" command with 1 additional argument
        // print billings of every day, ordered by date
        printBillingsByDate(events, *numEvents, name, park);

    } else if (result == 3) {
        // Case: "f" command with 2 additional arguments
        // print billings of specific day
        printBillingsOfDate(events, *numEvents, name, park, date);
    }

    // Free memory dinamically allocated to name
    free(name);
    free(date);
}
