#ifndef _UTIL_H_
#define _UTIL_H_

#include "stdlib.h"
#include "string.h"
#include "vector"
using namespace std;

void addToActiveCommand(int, string);
int removeCommand(int);
vector<int> getActiveProcesses(void);
bool getExistence (int);
float sysDuration(struct, struct);
float userDuration(struct, struct);
int getNumberOfParams(string);
int checkSpecialCmd(string);

#endif