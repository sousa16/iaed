/**
 * @file handleP.h
 * @author João Sousa
 * @brief header file for handleP.c
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HANDLE_P_H
#define HANDLE_P_H

#include "aux.h"

int pParserErrorCatcher(ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
                        const char *name, int *capacity, float *cost15,
                        float *cost15After1Hour, float *maxDailyCost);
int pParser(char *input,
            ParkingLot parkingLots[MAX_PARKS], int *numParkingLots,
            char *command, char *name, int *capacity,
            float *cost15, float *cost15After1Hour, float *maxDailyCost);
void handleP(char *input,
             ParkingLot parkingLots[MAX_PARKS], int *numParkingLots);

#endif /* HANDLE_P_H */
