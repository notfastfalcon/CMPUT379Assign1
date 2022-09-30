#ifndef _UTIL_H_
#define _UTIL_H_

#include "stdlib.h"
#include "string.h"
#include "vector"
#include "sys/resource.h"
using namespace std;

struct rusage;

void addToActiveCommand(int, string);
int removeCommand(int);
vector<int> getActiveProcesses(void);
bool getExistence (int);
float sysDuration(struct rusage *start, struct rusage *end);
float userDuration(struct rusage *start, struct rusage *end);
int getNumberOfParams(string);
int checkSpecialCmd(string);

#endif