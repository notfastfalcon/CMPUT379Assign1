#ifndef _UTIL_H_
#define _UTIL_H_

#include "stdlib.h"
#include "string.h"
#include "vector"
using namespace std;

void addToActiveCommand(pid_t, clock_t);
int removeCommand(int);
vector<int> getActiveProcesses(void);
bool getExistence (int);
clock_t startTimer(void);
clock_t endTimer(void);
clock_t duration(clock_t, clock_t);
int getNumberOfParams(string);
int checkSpecialCmd(string);

#endif