#include "stdlib.h"
#include "string.h"
#include "bits/stdc++.h"
#include "iostream"
#include "vector"
#include "map"
#include "algorithm"
#include "utility.h"
using namespace std;

//TODO: edit the two lines below after functionality implemented
map <pid_t, vector<clock_t>> commands;

//add to tracked pids
void addToActiveCommand(pid_t pidToAdd, clock_t time) {
	commands[pidToAdd].push_back(time);
}

//remove from tracked pids
int removeCommand(int pidToRemove) {
	commands.erase((pid_t) pidToRemove);	
}

//return all the active pids
vector<int> getActiveProcesses() {
	vector<int> commandPid;
	for (auto iterator: commands) {
		commandPid.push_back((int)iterator.first);
	}
	return commandPid;
}

//check if given pid exists
bool getExistence(int pidToCheck) {
	return commands.find((pid_t)pidToCheck) != commands.end();
}

clock_t startTimer() {
	clock_t startTime = clock();
	return startTime;
}

clock_t endTimer() {
	clock_t endTime = clock();
	return endTime;
}

//get the duration of time between startTime and endTime
clock_t duration(clock_t startTime, clock_t endTime) {
	clock_t duration = endTime - startTime;
	duration = duration/CLOCKS_PER_SEC; //to get time in s instead of ms
	return duration;
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