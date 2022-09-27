#include "stdlib.h"
#include "string.h"
#include "iostream"
#include "vector"
#include "algorithm"
#include "utility.h"
using namespace std;

vector<int> commandPid;

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