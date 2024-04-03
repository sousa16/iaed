/**
 * @file proj1.c
 * @author João Sousa
 * @brief main project file, handles stdinputs
 * @version 0.1
 * @date 2024-03-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "proj1.h"

int main() {
    // Initialize input string
    char *input = NULL;
    size_t input_size = 0;

    // Initialize parkingLots vector with size MAX_PARKS
    ParkingLot parkingLots[MAX_PARKS];

    // Initialize events vector and dynamically allocate memory
    EntryExitEvent **events = NULL;

    int numParkingLots = 0, numEvents = 0;

    // Initialize variable to know when to quit program (q command)
    char on = 1;
    while (on) {

        // Save input string in input and string size in input_size
        getline(&input, &input_size, stdin);

        // Switch to handle different commands by reading first character
        // of input
        switch (input[0]) {
        case 'q':
            // Cleanup and exit
            on = 0;
            break;
        case 'p':
            handleP(input, parkingLots, &numParkingLots);
            break;
        case 'e':
            events = handleE(input, parkingLots,
                             &numParkingLots, events, &numEvents);
            break;
        case 's':
            events = handleS(input, parkingLots,
                             &numParkingLots, events, &numEvents);
            break;
        case 'v':
            handleV(input, events, &numEvents);
            break;
        case 'f':
            handleF(input, parkingLots,
                    &numParkingLots, events, &numEvents);
            break;
        case 'r':
            events = handleR(input, parkingLots,
                             &numParkingLots, events, &numEvents);
            break;
        case 't':
            handleT(input, parkingLots,
                    &numParkingLots, events, &numEvents);
            break;
        default:
            printf("First character doesn't match anything\n");
        }
    }

    // Free allocated memory
    free(input);

    for (int i = 0; i < numEvents; i++) {
        free(events[i]->date);
        free(events[i]->time);
        free(events[i]->licensePlate);
        free(events[i]->parkingLotName);
        free(events[i]);
    }
    free(events);

    for (int i = 0; i < numParkingLots; i++) {

        // Check if the name is not NULL
        // (to avoid attempting to free NULL pointers)
        if (parkingLots[i].name != NULL) {
            free(parkingLots[i].name);
            freePlatesArray(&parkingLots[i]);
            parkingLots[i].name = NULL;
        }
    }

    return 0;
}