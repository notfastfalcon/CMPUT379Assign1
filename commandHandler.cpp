#include "stdlib.h"
#include "string.h"
#include "iostream"
#include "commandHandler"
using namespace std;

bool shellExit() {
	exit(0);
	return false;
}

void shellJobs() {
	//print all jobs here
}

void killProcess(string processPid) {
	// kill process with given pid
}

void resumeProcess(string processPid) {
	//resume the process with given pid
}

void shellSleep(int time) {
	//sleep for time
}

void suspendProcess(string processPid) {
	//suspend process with given pid
}

void waitForProcess(string processPid) {
	//wait for process with given pid to complete
}

void specialCommand(string raw_input) {
	//process these special commands
}

bool shellProcess(string raw_input, int commandType) {
	bool runShell = true;
	switch (commandType) {
		case 0:
			specialCommand(raw_input);
			break;
		case 1:
			runShell = shellExit();
			break;
		case 2:
			shellJobs();
			break;
		case 3:
			killProcess(raw_input.substr(5));
			break;
		case 4:
			resumeProcess(raw_input.substr(7));
			break;
		case 5:
			shellSleep(stoi(raw_input.substr(6)));
			break;
		case 6:
			suspendProcess(raw_input.substr(8));
			break;
		case 7:
			waitForProcess(raw_input.substr(5));
		case -1:
			break;
	}
	return runShell;
}