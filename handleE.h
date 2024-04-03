/**
 * @file handleE.h
 * @author João Sousa
 * @brief header file for handleE.c
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HANDLE_E_H
#define HANDLE_E_H

#include "aux.h"

int eParser(char *input,
            ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
            EntryExitEvent **events, int *numEvents,
            char *command, char *name, char *plate,
            char *date, char *hour);
EntryExitEvent **handleE(char *input, ParkingLot parkingLots[MAX_PARKS],
                         int *numParkingLots,
                         EntryExitEvent **events, int *numEvents);

#endif /* HANDLE_E_H */
