#include "stdlib.h"
#include "string.h"
#include "bits/stdc++.h"
#include "iostream"
#include "vector"
#include "map"
#include "algorithm"
#include "sys/resource.h"
#include "utility.h"
using namespace std;

map <int, vector<string>> processTable;

//add to tracked pids
void addToActiveCommand(int pidToAdd, string args) {
	processTable[pidToAdd].push_back(args);
	//process is running
	processTable[pidToAdd].push_back("R");
}

//remove from tracked pids
int removeCommand(int pidToRemove) {
	processTable.erase(pidToRemove);	
}

//return all the active pids
vector<int> getActiveProcesses() {
	vector<int> commandPid;
	for (auto iterator: processTable) {
		commandPid.push_back(iterator.first);
	}
	return commandPid;
}

//check if given pid exists
bool getExistence(int pidToCheck) {
	return processTable.find(pidToCheck) != processTable.end();
}

//get the system time used by the process
//this code is highly inspired from a DelftStack post. Link in README
float sysDuration(struct rusage *start, struct rusage *end) {
	return(end->ru_stime.tv_sec - start->ru_stime.tv_sec);
}

//get the user time used by the process
//this code is highly inspired from a DelftStack post. Link in README
float userDuration(struct rusage *start, struct rusage *end) {
	return(end->ru_utime.tv_sec - start->ru_utime.tv_sec);
}

// get number of input parameters from command line
int getNumberOfParams(string raw_input) {
	int count = 1;
	for (int i = 0; i < raw_input.length(); i++)
		if(raw_input[i] == ' ' && raw_input[i+1] != ' ' &&  i+1 != raw_input.length()) {
			count++;
	}
	return count;
}

// check if any of the special arguments (&, <fname, >fname) exist
int checkSpecialCmd(string raw_input) {
	//& should only be the last argument
	if (raw_input.back() == '&')
		return 1;

}