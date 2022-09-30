#include "stdlib.h"
#include "errno.h"
#include "stdio.h"
#include "unistd.h"
#include "iostream"
#include "string.h"
#include "map"
#include "mainActivity.h"
#include "commandHandler.h"
using namespace std;

int getCommandType(string raw_input) {
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
	for(auto cmd: commands) {
		//if we find any of the command in the first position, return int value
		if (raw_input.find(cmd.first) == 0) {
			return cmd.second;
		}
	}
	return 0;
}

string getInput() {
	string cmdArgument;
	cout << "SHELL379: ";
	getline(cin, cmdArgument);
	return cmdArgument;
}

void shellInit() {
	system("clear");
	cout << "Welcome to CMPUT 379 Shell!\n";
}

void shell() {
	bool runShell = true;
	shellInit();
	while (runShell) {
		string raw_input = getInput();
		int commandType = getCommandType(raw_input);
		runShell = shellProcess(raw_input, commandType);
	}
	//just to tell OS successful Completion
	shellQuit();
}

void shellQuit(){
	cout<<"Goodbye!\n";
	_exit(0);
}

int main (int argc, char *argv[]) {
	shell();
}