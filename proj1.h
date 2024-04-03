/**
 * @file proj1.h
 * @author João Sousa
 * @brief header file for proj1.c
 * @version 0.1
 * @date 2024-03-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of parks as specified in project statement
#define MAX_PARKS 20
#define PLATE_LEN 8

// Data Structure used to represent a Parking Lot
typedef struct
{
    char *name;
    int capacity;
    int availableSpots;
    float cost15;
    float cost15After1Hour;
    float maxDailyCost;
    char **plates; // Dynamic array to store license plates
    int numPlates; // Number of license plates in the array
} ParkingLot;

// Data Structure used to represent an Event (entry or exit)
typedef struct
{
    char *date;
    char *time;
    char *licensePlate;
    char *parkingLotName;
    int isEntry; // 1 for entry, 0 for exit
} EntryExitEvent;

// Data Structure used to represent a park billing of a given day
typedef struct
{
    char *date;
    float totalBilling;
} DailyBilling;

#include "handleE.h"
#include "handleF.h"
#include "handleP.h"
#include "handleR.h"
#include "handleS.h"
#include "handleV.h"
#include "handleT.h"