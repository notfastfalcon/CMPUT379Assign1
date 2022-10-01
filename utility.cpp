#include "stdlib.h"
#include "string.h"
#include "bits/stdc++.h"
#include "iostream"
#include "vector"
#include "map"
#include "algorithm"
#include "utility.h"
using namespace std;

map <int, vector<string>> processTable;
struct rusage ru_utime, ru_stime;


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
	//check if running
	if (kill(((pid_t)pidToCheck), SIGCONT) < 0) {
		// if not remove from active commands map
		removeActiveCommand(pidToCheck);
		return false;
	}
	else 
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

//prints exectime of the process with given pid
void getTime(int pid) {
	string pid_s = to_string(pid);
	string command = "ps -p " + pid_s +" -o etimes";
	FILE* infile = popen(command.c_str(), "r");
	if (infile < 0) {
		perror("Pipe Error");
		exit(1);
	}
	else{
		ostringstream out;
		char buf[100];
		int count = 0;
		while(fgets(buf, 100, infile) ! NULL) {
			if (count > 0) {
				out << buf << "\t";
				break;
			}
			else{
				count++;
			}
		}	
		cout << out;
		pclose(infile);
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
	return getrusage(RUSAGE_CHILDREN, &ru_utime);
}

//returns System CPU time used
int getSysTime() {
	return getrusage(RUSAGE_CHILDREN, &ru_stime);
}

//clear every map
void clearMemory() {
	processTable.clear();
}