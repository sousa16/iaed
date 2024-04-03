/**
 * @file handleT.c
 * @author João Sousa
 * @brief file dedicated to the handleT function
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "proj1.h"
#include "handleT.h"

/**
 * @brief handle parsing for t command
 * 
 * @param input 
 * @param events 
 * @param numEvents 
 * @param parkingLots 
 * @param numParkingLots 
 * @param command 
 * @param name 
 * @param date 
 * @return int 
 */
int tParser(char *input,
            ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
            char *command, char *name, char *date) {
    int result = sscanf(input, " %c \"%[^\"]\" %s",
                        command, name, date);

    // If the input doesn't have double quotes, retry with %s
    if (result == 1 || name[0] == '\0') {
        result = sscanf(input, " %c %s %s",
                        command, name, date);
    }

    if (result == 2 && *command == 't') {
        if (!(parkingExists(parkingLots, *numParkingLots, name))) {
            printf("%s: no such parking.\n", name);
        } else {
            return result;
        }
    }

    return 0;
}

/**
 * @brief handle the 't' user command (print park billing)
 *
 * @param input
 * @param parkingLots
 * @param numParkingLots
 * @param events
 * @param numEvents
 */
void handleT(char *input, ParkingLot parkingLots[MAX_PARKS],
             int *numParkingLots, EntryExitEvent **events, int *numEvents) {
    char command;
    char *name = NULL, *date = NULL;

    // Allocate memory based on the length of the name in the input
    name = (char *)malloc((strlen(input) + 1) * sizeof(char));
    date = (char *)malloc((strlen(input) + 2) * sizeof(char));

    int result = tParser(input, parkingLots, numParkingLots,
                         &command, name, date);

    ParkingLot *park =
        getParkingLotByName(parkingLots, *numParkingLots, name);

    if (result == 2) {
        // Case: "f" command with 1 additional argument
        // print billings of every day, ordered by date
        printBillings(events, *numEvents, name, park);

    // Free memory dinamically allocated to name
    free(name);
    free(date);
    }
}