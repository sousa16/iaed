/**
 * @file handleF.h
 * @author João Sousa
 * @brief header file for handleF.c
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HANDLE_F_H
#define HANDLE_F_H

#include "aux.h"

int fParser(char *input,
            EntryExitEvent **events, int numEvents,
            ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
            char *command, char *name, char *date);
void handleF(char *input, ParkingLot parkingLots[MAX_PARKS],
             int *numParkingLots, EntryExitEvent **events, int *numEvents);

#endif /* HANDLE_F_H */
