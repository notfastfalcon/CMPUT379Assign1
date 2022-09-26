#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

#include "string.h"
using namespace std;

bool shellExit(void);
void shellJobs(void);
void killProcess(string);
void resumeProcess(string);
void shellSleep(int);
void suspendProcess(string);
void waitForProcess(string);
void specialCommand(string);
bool shellProcess(string, int);

#endif