#include "stdlib.h"
#include "errno.h"
#include "stdio.h"
#include "unistd.h"
#include "iostream"
#include "string.h"
#include "map"
#include "mainActivity.h"
#include "commandHandler.h"
#include "utility.h"
using namespace std;

//returns the type of command entered
int getCommandType(string rawInput) {
	map<string, int> commands = {
	{"exit", 1},
	{"jobs", 2},
	{"kill", 3},
	{"resume", 4},
	{"sleep", 5},
	{"suspend", 6},
	{"wait", 7},
	{"cd", 8},
	{"\n", -1}
	};

	size_t position = rawInput.find(" ");
	string cmd = "";
	//if spaces exist
	if (position < rawInput.length()) {
		cmd = rawInput.substr(0, position);
	}
	//if no spaces
	else {
		cmd = rawInput;
	}
	auto key = commands.find(cmd);
	
	if (key != commands.end())
		return commands[cmd];

	else
		return 0;
}

//get input from command line
string getInput() {
	string cmdArgument;
	cout << "SHELL379: ";
	getline(cin, cmdArgument);
	return cmdArgument;
}

//main shell executions
void shell() {
	//keep running unless exited
	bool runShell = true;
	while (runShell) {
		string rawInput = getInput();
		int commandType = getCommandType(rawInput);
		runShell = shellProcess(rawInput, commandType);
	}
	//just to tell OS successful Completion
	shellQuit();
}

//exit with success after shell is exitted
void shellQuit(){
	clearMemory();
	_exit(0);
}

int main (int argc, char *argv[]) {
	shell();
	return 0;
}
