#ifndef _UTIL_H_
#define _UTIL_H_

#include "stdlib.h"
#include "string.h"
#include "vector"
#include "sys/resource.h"
using namespace std;
struct rusage;

void addToActiveCommand(int, string);
void updateActiveStatus(int, string);
int removeActiveCommand(int);
vector<int> getActiveProcesses(void);
bool getActiveExistence (int);
string getStatus(int);
string getArgs(int);
int getTime(int);
int getNumberOfParams(string);
int getUserTime(void);
int getSysTime(void);
void directOutFile(string);
void directInFile(string);
void clearMemory(void);

#endif