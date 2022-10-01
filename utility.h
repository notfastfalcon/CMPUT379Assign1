#ifndef _UTIL_H_
#define _UTIL_H_

#include "stdlib.h"
#include "string.h"
#include "vector"
#include "sys/resource.h"
using namespace std;


void addToActiveCommand(int, string);
int removeActiveCommand(int);
vector<int> getActiveProcesses(void);
bool getActiveExistence (int);
int getNumberOfParams(string);
void clearMemory(void);

#endif