/**
 * @file handleV.h
 * @author João Sousa
 * @brief header file for handleV.c
 * @version 0.1
 * @date 2024-03-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HANDLEV_H
#define HANDLEV_H

#include "aux.h"

int vParser(char *input, EntryExitEvent **events, int *numEvents,
            char *command, char *plate);
void handleV(char *input, EntryExitEvent **events, int *numEvents);

#endif /* HANDLEV_H */
