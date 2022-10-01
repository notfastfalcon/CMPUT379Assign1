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

//add to active tracked pids
void addToActiveCommand(int pidToAdd, string args) {
	processTable[pidToAdd].push_back(args);
	//process is running
	processTable[pidToAdd].push_back("R");
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
	if (kill(((pid_t)pidToCheck), 0) < 0) {
		// if not remove from active commands map
		removeActiveCommand(pidToCheck);
		return false;
	}
	else 
		return true;
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

//clear every map
void clearMemory() {
	processTable.clear();
}