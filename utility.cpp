#include "stdlib.h"
#include "string.h"
#include "iostream"
#include "vector"
#include "map"
#include "algorithm"
#include "utility.h"
using namespace std;

//TODO: edit the two lines below after functionality implemented
vector<int> commandPid;
map <int, vector<string>> commands;

void addToActiveCommand(int pidToAdd) {
	commandPid.push_back(pidToAdd);
}

int removeCommand(int pidToRemove) {
	auto iterator = find(commandPid.begin(), commandPid.end(), pidToRemove);
	if (iterator != commandPid.end()) {
		commandPid.erase(iterator);
		return 0;
	}
	else {
		return -1;
	}
}

vector<int> getActiveProcesses() {
	return commandPid;
}

bool getExistence(int pidToCheck) {
	return find(commandPid.begin(), commandPid.end(), pidToCheck) != commandPid.end();
}

string getError() {
	cout << "No active process with given PID found!\n";
}

clock_t startTimer() {
	clock_t startTime = clock();
	return startTime;
}

clock_t endTimer() {
	clock_t endTime = clock();
	return endTime;
}

clock_t duration(clock_t startTime, clock_t endTime) {
	clock_t duration = endTime - startTime;
	duration = duration/CLOCKS_PER_SEC; //to get time in s instead of ms
	return duration;
}

int getNumberOfParams(string raw_input) {
	int count = 1;
	for (int i = 0; i < raw_input.length(); i++)
		if(raw_input[i] == ' ' && raw_input[i+1] != ' ' &&  i+1 != raw_input.length()) {
			count++;
	}
	return count;
}

char* getCharEquivalent(string raw_input) {
	//code inspired from Lab2 examples
	int size = getNumberOfParams(raw_input);
	char *args[size + 1]; //size + 1 to accomodate NULL
    args[-1] = NULL; //last character should always be null

    size_t position = 0;
    int startSubString = 0;
    for (int i = 0; i < size; i++) {
    	position = raw_input.find(" ", startSubString);
    	string interimString = raw_input.substr(startSubString, position);
    	args[i] = strdup(interimString);
    	startSubString = position + 1;
    }
    return args;
}