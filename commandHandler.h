#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

#include "string.h"
#include "utility.h"
using namespace std;

bool shellExit(void);
void shellJobs(void);
void killProcess(int);
void resumeProcess(int);
void shellSleep(int);
void suspendProcess(int);
void waitForProcess(int);
void executeCommand(string);
bool shellProcess(string, int);

#endif