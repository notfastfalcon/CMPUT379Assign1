#include "stdlib.h"
#include "string.h"
#include "bits/stdc++.h"
#include "signal.h"
#include "iostream"
#include "unistd.h"
#include "sys/wait.h"
#include "commandHandler.h"
#include "utility.h"
using namespace std;

struct rusage start, end;

//exit here
bool shellExit() {
	for (auto activePID: getActiveProcesses()) {
		killProcess(activePID);
	}
	return false;
}

//print all jobs here
void shellJobs() {
	for (auto activePID: getActiveProcesses()) {
		cout << activePID <<"\t"<< sysDuration(&start, &end) <<"\t"<< userDuration(&start, &end);
		cout <<"\n";
	}
}

//kill specified process
void killProcess(int processPid) {
	//Check if Pid is active
	if(getExistence(processPid)) {
		// kill process with given pid
		kill((pid_t)processPid, SIGKILL);
		getrusage(RUSAGE_CHILDREN, &end);
	}
	else
		perror("No PID Found");
}

//resume specified process
void resumeProcess(int processPid) {
	//Check if Pid is active
	if(getExistence(processPid))	
		//resume the process with given pid
		kill((pid_t)processPid, SIGCONT);
	else
		perror("No PID Found");
}

//shell sleeps for specified seconds
void shellSleep(int time) {
	//sleep for time
	sleep(time);
}

//suspend specified process
void suspendProcess(int processPid) {
	//Check if Pid is active
	if(getExistence(processPid))
		//suspend process with given pid
		kill((pid_t)processPid, SIGSTOP);
	else
		perror("No PID Found");

}

//wait for specified process to complete
void waitForProcess(int processPid) {
	//Check if Pid is active
	if(getExistence(processPid)) {
		//wait for process with given pid to complete

	}
	else
		perror("No PID Found");
}

void executeCommand(string raw_input) {
	//process these special commands
	pid_t childPid = newProcess(raw_input);
}

pid_t newProcess(string raw_input) {
	//convert string to character array
	int size = getNumberOfParams(raw_input);
	char *args[size+1];
	args[size] = NULL; // should always be NULL terminated
	//convert string to char*[]
	size_t position = 0;
    int startSubString = 0;
    for (int i = 0; i < size; i++) {
    	position = raw_input.find(" ", startSubString);
    	string interimString = raw_input.substr(startSubString, position-startSubString);
    	startSubString = position + 1;
    	args[i] = strdup(interimString.c_str());
    }

	//create new process using fork
	getrusage(RUSAGE_CHILDREN, &start);
	pid_t childPid = fork();
	if(childPid == 0) {
		if(execvp(args[0], args) < 0) {
			perror("Execve Error");
			_exit(1);
		}
	}
	else if(childPid == -1) {
		perror("Fork Error");
		_exit(1);
	}
	
	else
		//wait for execvp to terminate
		wait(NULL);
		return childPid;
}

void changeDirectory(string path) {
	char pathDir [path.length() + 1] = {};
	strcpy(pathDir, path.c_str());
	if(chdir(pathDir) < 0) {
		perror("Check directory");
	}
}

bool shellProcess(string raw_input, int commandType) {
	bool runShell = true;
	try {
		switch (commandType) {
			case 0:
				executeCommand(raw_input);
				break;
			case 1:
				runShell = shellExit();
				break;
			case 2:
				executeCommand(raw_input);
				//shellJobs();
				break;
			case 3:
				killProcess(stoi(raw_input.substr(5)));
				break;
			case 4:
				resumeProcess(stoi(raw_input.substr(7)));
				break;
			case 5:
				shellSleep(stoi(raw_input.substr(6)));
				break;
			case 6:
				suspendProcess(stoi(raw_input.substr(8)));
				break;
			case 7:
				waitForProcess(stoi(raw_input.substr(5)));
				break;
			case 8:
				changeDirectory(raw_input.substr(3));
			case -1:
				//do nothing and ask for output again if someone hits enter
				break;
		}
	}
	// catch all kinds of exceptions
	catch(...) {
		perror("Invalid arguments");
		runShell = true;
	}
	return runShell;
}