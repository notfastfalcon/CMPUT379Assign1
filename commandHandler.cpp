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

bool shellExit() {
	//exit here
	for (auto activePID: getActiveProcesses()) {
		waitForProcess(activePID);
	}
	shellJobs();
	return false;
}

void shellJobs() {
	//print all jobs here
}

void killProcess(int processPid) {
	//Check if Pid is active
	if(getExistence(processPid))
		// kill process with given pid
		kill((pid_t)processPid, SIGKILL);
	else
		perror("No PID Found");
}

void resumeProcess(int processPid) {
	//Check if Pid is active
	if(getExistence(processPid))	
		//resume the process with given pid
		kill((pid_t)processPid, SIGCONT);
	else
		perror("No PID Found");
}

void shellSleep(int time) {
	//sleep for time
	sleep(time);
}

void suspendProcess(int processPid) {
	//Check if Pid is active
	if(getExistence(processPid))
		//suspend process with given pid
		kill((pid_t)processPid, SIGSTOP);
	else
		perror("No PID Found");

}

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
	char *args[size+1]; // size+1 to get NULL in the end
	args[-1] = NULL;
	char *env[] = {NULL};

	//convert string to char*[]
	size_t position = 0;
    int startSubString = 0;
    for (int i = 0; i < size; i++) {
    	position = raw_input.find(" ", startSubString);
    	string interimString = raw_input.substr(startSubString, position-startSubString);
    	//add path to first command argument
    	if (i == 0) 
    		interimString = "/usr/bin/" + interimString;
    	args[i] = strdup(interimString.c_str());
    	cout << args[i] << "\n";
    	startSubString = position + 1;
    }

	//create new process using fork
	pid_t childPid = fork();
	if(childPid == 0) {
		if(execve(args[0], args, env) < 0) {
			perror("Execve Error");
			_exit(1);
		}
	}
	else if(childPid == -1) {
		perror("Fork Error");
		_exit(1);
	}
	
	else
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
				shellJobs();
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