#include "stdlib.h"
#include "string.h"
#include "bits/stdc++.h"
#include "iostream"
#include "sys/wait.h"
#include "vector"
#include "map"
#include "fcntl.h"
#include "unistd.h"
#include "algorithm"
#include "utility.h"
using namespace std;

map <int, vector<string>> processTable;
struct rusage usage;


//add to active tracked pids
void addToActiveCommand(int pidToAdd, string args) {
	//process is running by default
	processTable[pidToAdd].push_back("R");
	//the default args
	processTable[pidToAdd].push_back(args);
}

//used to edit status of the process
void updateActiveStatus(int pid, string newStatus) {
	//updated status
	processTable[pid].at(0) = newStatus;
}

//remove from tracked pids
int removeActiveCommand(int pidToRemove) {
	processTable.erase(pidToRemove);	
}

//return all the active pids
vector<int> getActiveProcesses() {
	vector<int> commandPid;
	for (auto iterator: processTable) {
		if (getActiveExistence(iterator.first)) {
			commandPid.push_back(iterator.first);
		}
	}
	return commandPid;
}

//check if given pid exists
bool getActiveExistence(int pidToCheck) {
	int status;
	//check if running by sending wait WNOHANG signal 
	if (waitpid((pid_t) pidToCheck, &status, WNOHANG) != 0) {
		// if not active remove from active commands map
		removeActiveCommand(pidToCheck);
		//return not active
		return false;
	}
	else 
		//return active
		return true;
}

//get status of the process with given pid
string getStatus(int pid) {
	return processTable[pid].at(0);
}

//get args of the process with given pid
string getArgs(int pid) {
	return processTable[pid].at(1);
}

//return exectime of the process with given pid
//heavily inspired from Lab3
int getTime(int pid) {
	string pid_s = to_string(pid);
	string command = "ps -p " + pid_s +" -o time";
	FILE* infile = popen(command.c_str(), "r");
	if (infile < 0) {
		return 0;
	}
	else{
		char buf[100];
		int count = 0;
		while(fgets(buf, 100, infile) != NULL) {
			if (count > 0) {
				break;
			}
			else{
				count++;
			}
		}
		// return time	
		int time = atoi(buf);
		return time;
	}
}

// get number of input parameters from command line
int getNumberOfParams(string rawInput) {
	int count = 1;
	for (int i = 0; i < rawInput.length(); i++)
		if(rawInput[i] == ' ' && rawInput[i+1] != ' ' &&  i+1 != rawInput.length()) {
			count++;
	}
	return count;
}

// returns user CPU time used
int getUserTime() {
	getrusage(RUSAGE_CHILDREN, &usage);
	return usage.ru_utime.tv_sec;
}

//returns System CPU time used
int getSysTime() {
	getrusage(RUSAGE_CHILDREN, &usage);
	return usage.ru_stime.tv_sec;
}

//write to output file
void directOutFile(string filename) {
	int ofd;
	if (!filename.empty()) {
		if((ofd = open(filename.c_str(), O_CREAT | O_WRONLY)) < 0) {
        	perror("Open ofd failed!");
		}
		dup2(ofd, STDOUT_FILENO);
		close(ofd);
	}
}

//take input from input file
void directInFile(string filename) {
	int ifd;
	if (!filename.empty()) {
		if((ifd = open(filename.c_str(), O_CREAT | O_RDONLY)) < 0) {
        	perror("Open ifd failed!");
		}
		dup2(ifd, STDIN_FILENO);
		close(ifd);
	}
}

//clear every map
void clearMemory() {
	processTable.clear();
}
