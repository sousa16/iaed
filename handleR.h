/**
 * @file handleR.h
 * @author João Sousa
 * @brief header file for handleR.c
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HANDLE_R_H
#define HANDLE_R_H

#include "aux.h"

int rParser(char *input,
            ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
            char *command, char *name);
EntryExitEvent **handleR(char *input,
                         ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
                         EntryExitEvent **events, int *numEvents);

#endif /* HANDLE_R_H */
