/**
 * @file handleS.h
 * @author João Sousa
 * @brief header file for handleS.c
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HANDLES_H
#define HANDLES_H

#include "aux.h"

int sParser(char *input,
            ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
            EntryExitEvent **events, int *numEvents,
            char *command, char *name, char *plate,
            char *date, char *hour);
EntryExitEvent **handleS(char *input,
                         ParkingLot parkingLots[MAX_PARKS],
                         int *numParkingLots,
                         EntryExitEvent **events, int *numEvents);

#endif /* HANDLES_H */
