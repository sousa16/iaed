/**
 * @file aux.h
 * @author João Sousa
 * @brief header file for aux.c
 * @version 0.1
 * @date 2024-03-29
 *
 * @copyright Copyright (c) 2024
 *
 */

// AUXILIARY FUNCTIONS

// Miscellaneous functions
float roundToTwoDecimals(float num);
void bubbleSort(char **strings, int numStrings);

// Date and Time related functions
int daysInMonth(int month);
int daysInYear(int year);

void extractDateComponents(const char *date_str, int *day,
                           int *month, int *year);
void extractTimeComponents(const char *time_str, int *hour, int *minute);

int compareDate(const char *date1, const char *date2);
int compareTime(const char *time1, const char *time2);
int compareDateTime(const char *date1, const char *time1,
                    const char *date2, const char *time2);

int isValidDate(const char *date);
int isValidFDate(const char *date, EntryExitEvent **events, int numEvents);
int isValidTime(const char *hour);
int isValidDateTime(const char *date, const char *hour,
                    EntryExitEvent *lastEntry);
int isValidExitDateTime(const char *plate, const char *date,
                        const char *hour, EntryExitEvent **events,
                        int numEvents);

// Parking Lot and Vehicle related functions
int parkingExists(const ParkingLot *parkingLots,
                  int numParkingLots, const char *name);
ParkingLot *getParkingLotByName(ParkingLot *parkingLots,
                                int numParkingLots, const char *name);

int isValidLicensePlate(const char *plate);
void addPlateToLot(ParkingLot *parkingLot, const char *plate);
void removePlateFromLot(ParkingLot *parkingLot, const char *plate);
void freePlatesArray(ParkingLot *parkingLot);

int isVehicleInAnyPark(const char *plate,
                       ParkingLot *parkingLots, int numParkingLots);
int isVehicleInPark(const char *plate, const char *name,
                    ParkingLot *parkingLots, int numParkingLots);

// Event (Entry and Exit) related functions
void printAllEvents(EntryExitEvent **events, int numEvents);
int compareEvents(const EntryExitEvent *a, const EntryExitEvent *b);

EntryExitEvent **logEntryExitEvent(EntryExitEvent **events,
                                   int *numEvents, const char *date,
                                   const char *time, const char *licensePlate,
                                   const char *parkingLotName, int isEntry);
EntryExitEvent *getVehiclesEntriesAndExits(const char *plate,
                                           EntryExitEvent **events,
                                           int numEvents, int *numResults);
EntryExitEvent *getLastEntry(EntryExitEvent **events, int numEvents);
int findCorrespondingEntryIndex(int exitIndex, EntryExitEvent **events);
void findCorrespondingEntry(ParkingLot *park, EntryExitEvent **events,
                            int *numEvents, int numResults, char *plate,
                            char *date, char *hour);

void handleFoundExit(EntryExitEvent *results, int i, int j,
                     int *numStrings, char **entryExitStrings);
void handleNotFoundExit(EntryExitEvent *results, int i, int *numStrings,
                        char **entryExitStrings);

void findCorrespondingExit(EntryExitEvent *results, int numResults, int i,
                           int *numStrings, char **entryExitStrings);

void printSortedVehicleEvents(EntryExitEvent *results, int numResults);

void removeParkingLot(ParkingLot *parkingLots, int *numParkingLots,
                      EntryExitEvent **events, int *numEvents,
                      char *name, int parkIndexToRemove);

// Billing related functions
float getAmountPaid(ParkingLot *park, const char *entryDate,
                    const char *entryHour, const char *exitDate,
                    const char *exitHour);

int findDailyBillingIndex(DailyBilling *dailyBillings, int numDailyBillings,
                          const char *date);
void updateOrAddBilling(DailyBilling **dailyBillingsPtr,
                        int *numDailyBillingsPtr,
                        const char *date, float billing);

void printBillings(EntryExitEvent **events, int numEvents,
                         const char *name, ParkingLot *park);

void printBillingsByDate(EntryExitEvent **events, int numEvents,
                         const char *name, ParkingLot *park);
void printBillingsOfDate(EntryExitEvent **events, int numEvents,
                         const char *name, ParkingLot *park, const char *date);
