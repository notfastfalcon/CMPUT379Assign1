#ifndef _UTIL_H_
#define _UTIL_H_

#include "stdlib.h"
#include "string.h"
using namespace std;

void addToActiveCommand(int);
int removeCommand(int);
bool getExistence (int);
string getError(void);
clock_t startTimer(void);
clock_t endTimer(void);
clock_t duration(clock_t, clock_t);

#endif