#ifndef _MAIN_H_
#define _MAIN_H_

#include "string.h"
#include "commandHandler.h"
using namespace std;

int getCommandType(string);
string getInput(void);
void shell(void);
void shellQuit(void);

#endif
